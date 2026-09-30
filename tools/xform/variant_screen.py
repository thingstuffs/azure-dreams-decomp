#!/usr/bin/env python3
"""Variant screen: C spellings of one row compared with retail's order through the cc1 listing, in ~15 ms each.

    python3 tools/xform/variant_screen.py <row_id> <variants.json> [--cfgs 2.7.2-cdk-G0,2.8.1-G0] [--dump NAME]
                                          [--verify] [--base erased|pinned] [--context N]

`variants.json` maps a variant name to a list of textual replacements `[[old, new], ...]` applied in order to the
base text (the row's current text with every pin erased, or the pinned text with `--base pinned`, or per variant
when the name starts with `@`).  The target listing is the PINNED text's listing, which is retail's instruction
order whenever the row is byte-exact.  Distance = changed listing lines (unified diff, no context).  Distance 0 is
listing-exact and nearly always byte-exact; `--verify` runs the byte scorer on the distance-0 variants.  `--dump NAME`
writes that variant's text to `<scratch>/variant_<NAME>.c` (or the current directory when no scratchpad is set).

Python API (for generators and lanes):
    from variant_screen import Screen
    sc = Screen(row)                         # row dict from common.rows()
    sc.distance(text)                        # int or None (does not build); sc.diff(text) -> list of +/- lines
    sc.exact(text)                           # byte scorer verdict dict (tools/verify.py)

Round 57 built this as a scratchpad probe to find the sched tie-rule mechanism (the statements-after-call
variant of dungeon/func_818B1334 at distance 0 against thirteen spellings at 2 to 62); round 58 promotes it so the
model lanes and the generators screen the same way.
"""
import argparse, difflib, json, os, sys, tempfile
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/xform")); sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import rows, clean_path                                     # noqa: E402
from pin_census import sites_of                                        # noqa: E402
from pin_sites import erase_many                                       # noqa: E402
import screen                                                          # noqa: E402
from slus_module_context import compilation_source, fingerprint, require_individual_recipe  # noqa: E402
import slus_module_context                                             # noqa: E402


def recipe_cfg(recipe):
    """A physical unit's recipe (`{"ccver", "ccflags"}`) as a cfg label `common.parse_cfg` reads."""
    return (recipe["ccver"] + " " + (recipe.get("ccflags") or "")).strip()


def partitioned(row):
    """True for a slus row inside a partition context (tools/build/slus_partitions.py): its functions are
    compiled in one or more physical streams (a module owner and/or a parent's remainder), never alone."""
    return row.get("kind") == "slus" and bool(slus_module_context.partition_context(row)[0])


def screen_sources(row, candidate, outdir):
    """[(physical source path, cfg)] that `candidate` (the row's text, a file) is compiled in for a listing or a
    `-da` dump.  An ordinary or module slus row: one source (`compilation_source`, the module with its siblings)
    at the row's cfg.  A PARTITIONED slus row: `compilation_sources` - the plural context `tools/verify.py`
    builds for it - one source per physical unit that holds the row's functions, each at the unit's own recipe
    (r81_opus_kitgap: `compilation_source` raised `PartitionError: ... requires plural compilation` and lab.py /
    diff.py / why.py could not screen slus/w_8004DF8C, w_8003E758, w_8003F368)."""
    if partitioned(row):
        units = slus_module_context.compilation_sources(row, candidate, outdir)
        out = [(Path(u["cfile"]), recipe_cfg(u["recipe"])) for u in units if u.get("functions")]
        if not out:
            raise RuntimeError("%s: partition context has no unit holding the row's functions" % row["id"])
        return out
    return [(Path(compilation_source(row, candidate, outdir)), row["cfg"])]


def context_listing(row, text):
    """The normalised listing of `text` compiled as a slus MODULE or PARTITIONED row: in its physical source(s)
    (`screen_sources`), each unit's listing concatenated in unit order.  None if a unit does not build."""
    with tempfile.TemporaryDirectory(prefix="module_screen_") as td:
        candidate = Path(td) / Path(row["c_path"]).name
        candidate.write_text(text)
        listing = []
        for source, cfg in screen_sources(row, candidate, td):
            part = screen.compile_s(dict(row, cfg=cfg), source.read_text())
            if part is None:
                return None
            listing.extend(part)
        return listing


def row_listing(row, text):
    """`screen.compile_s` for any row: an ordinary row compiles alone, a slus module / partitioned row in its
    context (diff.py compiled every slus row alone: the -G32 cd_command_state members did not build at all)."""
    if row.get("kind") == "slus" and fingerprint(row) is not None:
        return context_listing(row, text)
    return screen.compile_s(row, text)


class Screen:
    def __init__(self, row, target_text=None, cfg=None):
        if cfg and cfg != row["cfg"]:
            if partitioned(row):
                raise ValueError("%s: partitioned slus row - per-row recipe trials are not supported "
                                 "(its recipe is the partition unit's; change it in config/ and gate the image)" % row["id"])
            require_individual_recipe(row)
        self.row = dict(row, cfg=cfg) if cfg else dict(row)
        self.pinned = target_text if target_text is not None else clean_path(row).read_text(errors="replace")
        self.context_fingerprint = fingerprint(self.row) if self.row.get("kind") == "slus" else None
        self.target = self._listing(self.pinned)
        self.n = 0

    def _listing(self, text):
        if self.context_fingerprint is None:
            return screen.compile_s(self.row, text)
        if fingerprint(self.row) != self.context_fingerprint:
            raise RuntimeError("module context changed during listing screen; rebuild the target")
        listing = context_listing(self.row, text)
        if fingerprint(self.row) != self.context_fingerprint:
            raise RuntimeError("module context changed during listing screen; rebuild the target")
        return listing

    def listing(self, text):
        self.n += 1
        return self._listing(text)

    def diff(self, text, context=0):
        l = self.listing(text)
        if l is None or self.target is None:
            return None
        return [y for y in difflib.unified_diff(self.target, l, lineterm="", n=context) if not y.startswith(("---", "+++"))]

    def distance(self, text):
        d = self.diff(text)
        return None if d is None else sum(1 for y in d if y[:1] in "+-")

    def exact(self, text):
        from verify import verify
        if self.context_fingerprint is not None and fingerprint(self.row) != self.context_fingerprint:
            raise RuntimeError("module context changed during listing screen; remeasure before scoring")
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / Path(self.row["c_path"]).name
            p.write_text(text)
            result = verify(self.row, p, include_root=ROOT / "include")
            if self.context_fingerprint is not None and fingerprint(self.row) != self.context_fingerprint:
                raise RuntimeError("module context changed during listing screen; remeasure before scoring")
            return result


def apply(base, reps):
    x = base
    for old, new in reps:
        if old not in x:
            return None, old
        x = x.replace(old, new, 1)
    return x, None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id"); ap.add_argument("variants")
    ap.add_argument("--cfgs"); ap.add_argument("--dump"); ap.add_argument("--verify", action="store_true")
    ap.add_argument("--base", choices=("erased", "pinned"), default="erased"); ap.add_argument("--context", type=int, default=0)
    a = ap.parse_args()
    row = next(r for r in rows() if r["id"] == a.row_id)
    pinned = clean_path(row).read_text(errors="replace")
    erased = erase_many(pinned, sites_of(pinned), clean_notes=True)
    V = json.load(open(a.variants))
    scratch = os.environ.get("CLAUDE_SCRATCHPAD") or "."
    for cfg in (a.cfgs.split(",") if a.cfgs else [row["cfg"]]):
        sc = Screen(row, pinned, cfg)
        print(f"== cfg {cfg}  pinned listing {len(sc.target) if sc.target else None} lines")
        items = [("erased", [])] + list(V.items())
        for name, reps in items:
            base = pinned if (name.startswith("@") or a.base == "pinned") else erased
            x, missing = apply(base, reps)
            if x is None:
                print(f"{name:28s} SKIP (pattern missing: {missing[:50]!r})"); continue
            d = sc.diff(x, a.context)
            if d is None:
                print(f"{name:28s} no build"); continue
            dist = sum(1 for y in d if y[:1] in "+-")
            extra = ""
            if a.verify and dist == 0 and name != "erased":
                v = sc.exact(x); extra = f"  scorer exact={v.get('exact')} total={v.get('total')}"
            print(f"{name:28s} dist {dist:3d}  {' | '.join(y for y in d if y[:1] in '+-')[:140]}{extra}")
            if a.dump and name.lstrip("@") == a.dump:
                out = Path(scratch) / f"variant_{a.dump}.c"; out.write_text(x); print(f"   wrote {out}")


if __name__ == "__main__":
    main()
