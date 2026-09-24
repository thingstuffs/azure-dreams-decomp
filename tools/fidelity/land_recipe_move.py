#!/usr/bin/env python3
"""Recipe-move lander (fidelity step 4): move rows to the recipe their RETAIL BYTES prove, each with a text that
is byte-exact there, for overlay AND slus rows.  Charter clause 4b as amended by "Rulings 2026-09-24 (later)"
item 1 (coherence toward the retail-proven recipe); modelled on tools/lanes/land_coherence.sh.

    python3 tools/fidelity/land_recipe_move.py <tag> <lane_dir>            # DRY RUN (default): verify + plan
    python3 tools/fidelity/land_recipe_move.py <tag> <lane_dir> --apply    # verify, switch, apply, gate, record

<lane_dir> holds the lane kit's staging: out/<container>/<file>.c (+ .c.base_sha = sha256 of the src text the
candidate was cut from) and cells.jsonl lines {"id", "to", "coherence", ...} (tools/fidelity/step4_measure.py
writes them; `rule2`, `evidence`, `pins_before/after` are carried into the trade when present).  A candidate
identical to the current text is a pure recipe switch.

Per run (one landing at a time: the build_ovl/work/land.lock every lander takes):
 1. VERIFY FIRST, nothing written: stale (.base_sha) and same-recipe entries are skipped; the target must be a
    stock recipe that splits addresses (the class this lander exists for); the candidate must be byte-exact at
    the target - overlay rows through tools/verify.py (the per-row scorer, cfg overridden in memory), slus rows
    through tools/fidelity/slus_iso.py (an isolated copy of build_slus/ with every moved TU swapped and its
    recipe changed, linked and compared with retail: verify.py's slus reference is the pinned object and cannot
    score a symbol respelling); pin_census.landing_refusal must pass.  The pinned text is scored at the target
    too: rule 2 holds -> trade kind `recipe-switch` (byte-neutral), else `coherence`.
 2. SNAPSHOT every file the switch touches: ledger/rows.jsonl, ledger/recipe_trades.jsonl, the overlay split
    tables, ledger/splits/slus.jsonl + slus.build.ninja, tools/build/configure.py, build_slus/build.ninja, and
    each row's src text.
 3. RECORD the trades first (ledger/recipe_trades.jsonl, charter rule 4), then SWITCH:
      overlay rows: common.set_row_cfgs (split tables, rows.jsonl, the build roots' exported tables);
      slus rows:    tools/build/configure.py CC_VER (the TU's line replaced, or added when the TU used the
                    default), build_slus/build.ninja regenerated (tools/configure.py in the view root) and
                    required to differ from the pinned ledger/splits/slus.build.ninja ONLY on the moved TUs'
                    ccver/ccflags lines, then copied over the pinned copy; ledger/splits/slus.jsonl re-derived
                    from it (row_db.edges_of - the table tools/registry.py rebuilds rows.jsonl from) and
                    required to differ only on the moved TUs; ledger/rows.jsonl cfg/cell/flags + cfg_corrected.
    then APPLY the candidate texts to src/ and journal them (ledger/sweeps/recipe_move_<tag>.jsonl).
 4. GATE: the overlay windows (gate_all.py; LAND_ISOLATED=1 -> the build_ovl_gate root, as land_coherence.sh)
    when an overlay row moved; the SLUS SHA-1 gate (build_slus.sh; its new ledger/gate_slus.jsonl record must be
    MATCH with the recipe identical to the pinned copy) when a slus row moved.
 5. On ANY failure after step 2: every snapshot is written back (text, recipe, tables, trades), the build roots
    re-exported - the tree is as it was.  On success: the slus reference cache of the moved slus rows is
    re-baselined (tools/verify.py rebaseline_slus, gated on the SLUS gate just run).

Test hooks (tools/tests/test_land_recipe_move.py): --root runs against a throwaway copy of the tree (every
ledger/src/recipe write lands there; scoring still uses this tree's toolchain), and the gate commands can be
replaced with LAND_MOVE_GATE_OVL / LAND_MOVE_GATE_SLUS (bash strings run in the root; exit 0 = MATCH).
"""
from __future__ import annotations
import argparse, contextlib, fcntl, json, os, re, subprocess, sys, tempfile, time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent)); sys.path.insert(0, str(HERE))
import common  # noqa: E402
from common import parse_cfg, is_stock_cfg, sha_text, read_jsonl  # noqa: E402

SPLIT_CELLS = {"2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"}
OFF_SWITCHES = {"-mmips-as", "-mno-split-addresses"}
REAL_ROOT = common.ROOT


def splits(cfg):
    cell, flags = parse_cfg(cfg)
    return cell in SPLIT_CELLS and not (OFF_SWITCHES & set(flags))


@contextlib.contextmanager
def rooted(root: Path):
    """Point common's ROOT/LEDGER at `root` (every ledger/src write of this lander goes through common)."""
    old = (common.ROOT, common.LEDGER)
    common.ROOT, common.LEDGER = root, root / "ledger"
    try:
        yield
    finally:
        common.ROOT, common.LEDGER = old


# ------------------------------------------------------------------ slus recipe (pure text functions)

CC_LINE = re.compile(r'^(?P<ind>[ \t]*)"src/(?P<stem>[^"]+)\.c":\s*\("(?P<cell>[^"]*)",\s*"(?P<flags>[^"]*)"\),(?P<rest>.*)$')


def set_cc_ver(configure_text: str, stem: str, cell: str, flags: str, note: str) -> str:
    """tools/build/configure.py with TU `stem`'s CC_VER entry set to (cell, flags): the entry's line replaced,
    or a new line added at the end of the CC_VER dict when the TU compiled with DEFAULT_CC."""
    lines = configure_text.split("\n")
    try:
        start = next(i for i, l in enumerate(lines) if l.startswith("CC_VER = {"))
    except StopIteration:
        raise ValueError("configure.py has no CC_VER dict")
    end = next(i for i in range(start + 1, len(lines)) if lines[i].startswith("}"))
    entry = '    "src/%s.c": ("%s", "%s"),  # %s' % (stem, cell, flags, note)
    hits = [i for i in range(start + 1, end) if (m := CC_LINE.match(lines[i])) and m["stem"] == stem]
    if len(hits) > 1:
        raise ValueError("CC_VER lists src/%s.c %d times" % (stem, len(hits)))
    if hits:
        lines[hits[0]] = entry
    else:
        lines.insert(end, entry)
    return "\n".join(lines)


def recipe_diff_ok(old: str, new: str, stems) -> list:
    """Problems when the regenerated recipe differs from the pinned one anywhere but the moved TUs'
    ccver/ccflags lines (empty list = fine)."""
    import difflib
    a, b = old.splitlines(), new.splitlines()
    owner_a, cur = [], None
    for l in a:
        m = re.match(r"^build build/src/(\S+)\.o: cc ", l)
        cur = m.group(1) if m else (cur if l.startswith("  ") else None)
        owner_a.append(cur)
    bad = []
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if op == "equal":
            continue
        if op != "replace" or (i2 - i1) != (j2 - j1):
            bad.append("%s a[%d:%d] b[%d:%d]" % (op, i1, i2, j1, j2)); continue
        for k in range(i2 - i1):
            la, lb = a[i1 + k], b[j1 + k]
            if owner_a[i1 + k] not in stems or not re.match(r"^  (ccver|ccflags) = ", la) or la.split("=")[0] != lb.split("=")[0]:
                bad.append("line %d: %r -> %r" % (i1 + k + 1, la, lb))
    return bad


def edges_diff_ok(old_edges, new_edges, stems) -> list:
    bad = []
    if len(old_edges) != len(new_edges):
        return ["edge count %d -> %d" % (len(old_edges), len(new_edges))]
    for a, b in zip(old_edges, new_edges):
        if a == b:
            continue
        stem = Path(a["src"]).stem
        if stem not in stems or a["src"] != b["src"] or a["out"] != b["out"] or a["asflags"] != b["asflags"]:
            bad.append("edge %s changed outside the move" % a["src"])
    return bad


# ------------------------------------------------------------------ verification (step 1)

def verify_overlay_at(row, text, cfg):
    sys.path.insert(0, str(REAL_ROOT / "tools"))
    from verify import verify
    cell, flags = parse_cfg(cfg)
    r = dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(text)
        v = verify(r, f, include_root=(REAL_ROOT / "include").resolve())
    return {"exact": bool(v.get("exact")), "total": v.get("total"), "status": v.get("status")}


def verify_slus_at(changes):
    """changes: {stem: (text or None, cfg)} -> {"result", "detail", ...} from one isolated link."""
    from slus_iso import SlusView, cfg_to_ninja
    view = SlusView()
    try:
        cal = view.calibrate()
        if cal["result"] != "MATCH":
            return {"result": "ERROR", "detail": "isolated view does not reproduce retail before the move: %s" % cal}
        return view.gate({s: (t,) + cfg_to_ninja(c) for s, (t, c) in changes.items()})
    finally:
        import shutil
        shutil.rmtree(view.dest, ignore_errors=True)


# ------------------------------------------------------------------ the lander

class Lander:
    def __init__(self, root: Path, tag: str, lane: Path, round_=None, verify_overlay=None, verify_slus=None, log=print):
        self.root, self.tag, self.lane = Path(root), tag, Path(lane)
        self.round = round_ if round_ is not None else os.environ.get("ROUND", "fidelity-step4")
        self.verify_overlay = verify_overlay or verify_overlay_at
        self.verify_slus = verify_slus or verify_slus_at
        self.log = log

    # ---- inputs
    def entries(self):
        p = self.lane / "cells.jsonl"
        if not p.exists():
            raise SystemExit("no %s" % p)
        return [json.loads(l) for l in p.read_text().splitlines() if l.strip()]

    def plan(self):
        """Step 1: [(entry, row, cand, cur, rule2)] of the rows that may move; nothing written."""
        with rooted(self.root):
            by = {r["id"]: r for r in common.rows()}
            out, slus = [], {}
            for e in self.entries():
                rid, to = e["id"], e["to"]
                row = by.get(rid)
                if row is None:
                    self.log("skip unknown row", rid); continue
                c = rid.split("/")[0]
                cp = self.lane / "out" / c / Path(row["c_path"]).name
                if not cp.exists():
                    self.log("skip no candidate", rid); continue
                cand = cp.read_text(errors="replace")
                base = cp.with_name(cp.name + ".base_sha")
                cur = common.clean_path(row).read_text(errors="replace")
                if not base.exists() or base.read_text().strip() != sha_text(cur):
                    self.log("skip stale", rid); continue
                if row["cfg"] == to:
                    self.log("skip same recipe", rid); continue
                if not is_stock_cfg(to) or not splits(to):
                    self.log("skip target not a stock splitting recipe", rid, to); continue
                if row["kind"] == "slus":
                    from slus_module_context import require_individual_recipe
                    try:
                        require_individual_recipe(row, self.root)
                    except ValueError as exc:
                        self.log("skip grouped recipe move", str(exc)); continue
                    slus[Path(row["c_path"]).stem] = (e, row, cand, cur)
                    continue
                v = self.verify_overlay(row, cand, to)
                if not v.get("exact"):
                    self.log("skip not exact at target", rid, to, v.get("status"), v.get("total")); continue
                rule2 = bool(self.verify_overlay(row, cur, to).get("exact")) if cand != cur else True
                out.append((e, row, cand, cur, rule2))
            if slus:
                both = self.verify_slus({s: (None if cand == cur else cand, e["to"]) for s, (e, row, cand, cur) in slus.items()})
                if both.get("result") != "MATCH":
                    # find the culprits one by one, keep the rows that link exact on their own
                    self.log("slus: the moves together are %s (%s); trying one by one" % (both.get("result"), (both.get("detail") or "")[:160]))
                    keep = {}
                    for s, (e, row, cand, cur) in slus.items():
                        one = self.verify_slus({s: (None if cand == cur else cand, e["to"])})
                        if one.get("result") == "MATCH":
                            keep[s] = slus[s]
                        else:
                            self.log("skip not exact at target (isolated SLUS link)", row["id"], e["to"], (one.get("detail") or "")[:160])
                    if keep and len(keep) != len(slus):
                        both = self.verify_slus({s: (None if cand == cur else cand, e["to"]) for s, (e, row, cand, cur) in keep.items()})
                        if both.get("result") != "MATCH":
                            self.log("slus: the exact rows do not link exact together: no slus row moves"); keep = {}
                    slus = keep
                for s, (e, row, cand, cur) in slus.items():
                    rule2 = cand == cur or self.verify_slus({s: (None, e["to"])}).get("result") == "MATCH"
                    out.append((e, row, cand, cur, rule2))
        # outside `rooted`: the refusal runs this tree's own tools (the portability lint under tools/gate)
        from pin_census import landing_refusal
        ok = []
        for e, row, cand, cur, rule2 in out:
            if cand != cur:
                bad = landing_refusal(cand, cur, "src/%s/%s" % (row["container"], Path(row["c_path"]).name), row=row)
                if bad:
                    self.log("skip landing refusal", row["id"], bad[:120]); continue
            ok.append((e, row, cand, cur, rule2))
        return ok

    # ---- step 2: snapshots
    def touched_files(self, moves):
        r = self.root
        files = [r / "ledger/rows.jsonl", r / "ledger/recipe_trades.jsonl", r / "ledger/sweeps" / ("recipe_move_%s.jsonl" % self.tag)]
        for _e, row, _c, _cur, _r2 in moves:
            files.append(r / "src" / row["container"] / Path(row["c_path"]).name)
            if row["kind"] == "slus":
                files += [r / "ledger/splits/slus.jsonl", r / "ledger/splits/slus.build.ninja",
                          r / "tools/build/configure.py", r / "build_slus/build.ninja"]
            else:
                files.append(r / "ledger/splits" / (row["container"] + ".jsonl"))
        seen, out = set(), []
        for f in files:
            if f not in seen:
                seen.add(f); out.append(f)
        return out

    @staticmethod
    def snapshot(files):
        return {f: (f.read_bytes() if f.exists() else None) for f in files}

    def restore(self, snap, overlay_moved):
        for f, data in snap.items():
            if data is None:
                if f.exists():
                    f.unlink()
            else:
                f.write_bytes(data)
        if overlay_moved:
            for b in (self.root / "build_ovl", self.root / "build_ovl_raw"):
                if (b / "overlays").exists():
                    subprocess.run([sys.executable, str(self.root / "tools/row_db.py"), "export", str(b)], check=False,
                                   stdout=subprocess.DEVNULL)
        self.log("RESTORED %d files" % len(snap))

    # ---- step 3: switch
    def trade(self, e, row, cand, cur, rule2):
        return {"round": self.round, "date": time.strftime("%Y-%m-%d", time.gmtime()), "id": row["id"],
                "cfg_from": row["cfg"], "cfg_to": e["to"], "kind": "recipe-switch" if rule2 else "coherence",
                "how": e.get("coherence"), "rule2": rule2, "evidence": e.get("evidence") or {"source": "retail-proven"},
                "pins_before": _pins(cur), "pins_after": _pins(cand),
                "source_sha_before": sha_text(cur), "candidate_sha": sha_text(cand),
                "applied_via": ("tools/build/configure.py CC_VER + ledger/splits/slus.build.ninja + ledger/splits/slus.jsonl + "
                                "ledger/rows.jsonl" if row["kind"] == "slus" else
                                "common.set_row_cfgs (ledger/splits/%s.jsonl, ledger/rows.jsonl, build roots)" % row["container"]),
                "lander": "tools/fidelity/land_recipe_move.py %s" % self.tag,
                "why": "recipe moved toward the recipe the retail bytes prove (split-address fingerprint; charter clause 4b as "
                       "amended by Rulings 2026-09-24 (later) item 1); the candidate is byte-exact there; " +
                       ("the pinned text is exact there too (rule 2 holds: byte-neutral)" if rule2 else
                        "the pinned text is not (rule 2 waived by the coherence clause)")}

    def switch_slus(self, moves):
        r = self.root
        from slus_module_context import require_individual_recipe
        for _, row, *_ in moves:
            require_individual_recipe(row, r)
        stems = {Path(row["c_path"]).stem: e["to"] for e, row, *_ in moves}
        cfgp = r / "tools/build/configure.py"
        text = cfgp.read_text()
        for stem, to in stems.items():
            cell, flags = parse_cfg(to)
            text = set_cc_ver(text, stem, cell, " ".join(flags), "fidelity step 4 (%s): retail-proven splitting recipe" % self.tag)
        cfgp.write_text(text)
        b = r / "build_slus"
        if not (b / "build.ninja").exists():
            subprocess.run(["bash", str(r / "tools/build/mk_slus_root.sh")], check=True, stdout=subprocess.DEVNULL)
        g = subprocess.run([sys.executable, "tools/configure.py"], cwd=b, capture_output=True, text=True)
        if g.returncode:
            raise RuntimeError("configure.py failed: " + (g.stderr or g.stdout)[-300:])
        pinned = r / "ledger/splits/slus.build.ninja"
        new = (b / "build.ninja").read_text()
        bad = recipe_diff_ok(pinned.read_text(), new, set(stems))
        if bad:
            raise RuntimeError("regenerated recipe differs from the pinned copy outside the moved TUs: %s" % bad[:5])
        want = {s: parse_cfg(to) for s, to in stems.items()}
        for s, (cell, flags) in want.items():
            m = re.search(r"^build build/src/%s\.o: cc [^\n]*\n  ccver = ([^\n]*)\n  ccflags = ([^\n]*)\n" % re.escape(s), new, re.M)
            if not m or m.group(1).strip() != cell or m.group(2).strip() != " ".join(flags):
                raise RuntimeError("regenerated recipe does not carry %s at %s %s" % (s, cell, flags))
        sys.path.insert(0, str(REAL_ROOT / "tools"))
        from row_db import slus_edges
        old_edges = slus_edges(pinned.read_text(), r)
        new_edges = slus_edges(new, r)
        bad = edges_diff_ok(old_edges, new_edges, set(stems))
        if bad:
            raise RuntimeError("the recipe's cc edges would change outside the move: %s" % bad[:5])
        # ledger/splits/slus.jsonl is derived from the pinned recipe (row_db import); a hand landing that edited
        # the recipe without it leaves it stale (slus/w_8005A1D0, ca253080) - re-deriving it here repairs that
        drift = [a["src"] for a, b in zip(read_jsonl(r / "ledger/splits/slus.jsonl"), old_edges) if a != b]
        if drift:
            self.log("note: ledger/splits/slus.jsonl was out of step with the pinned recipe on %s; re-derived" % drift[:6])
        pinned.write_text(new)
        common.write_jsonl(r / "ledger/splits/slus.jsonl", new_edges)
        rs = read_jsonl(r / "ledger/rows.jsonl")
        ids = {row["id"]: e["to"] for e, row, *_ in moves}
        for x in rs:
            if x["id"] in ids:
                cell, flags = parse_cfg(ids[x["id"]])
                x["cfg"] = ids[x["id"]]; x["cell"] = cell; x["flags"] = " ".join(flags); x["stock"] = True; x["cfg_corrected"] = True
        common.write_jsonl(r / "ledger/rows.jsonl", rs)

    def apply_texts(self, moves):
        journal = self.root / "ledger/sweeps" / ("recipe_move_%s.jsonl" % self.tag)
        journal.parent.mkdir(parents=True, exist_ok=True)
        for e, row, cand, cur, rule2 in moves:
            p = self.root / "src" / row["container"] / Path(row["c_path"]).name
            if cand != cur:
                p.write_text(cand)
            common.append_jsonl(journal, {"id": row["id"], "transform": "recipe_move_" + self.tag, "in_sha": sha_text(cur),
                                          "out_sha": sha_text(cand), "outcome": "applied" if cand != cur else "noop",
                                          "cell_from": row["cfg"], "cell_to": e["to"], "source": self.lane.name,
                                          "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())})

    # ---- step 4: gates
    def gate(self, overlay_moved, slus_moved):
        env = dict(os.environ)
        if overlay_moved:
            cmd = os.environ.get("LAND_MOVE_GATE_OVL")
            if not cmd:
                cmd = ('EXP=gate SRCROOT="$PWD/src" bash tools/build/mk_ovl_root.sh && GATE_BUILD_ROOT=build_ovl_gate '
                       'python3 tools/build/gate_all.py --workers 8') if os.environ.get("LAND_ISOLATED") == "1" else \
                      "bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8"
            rc = subprocess.run(["bash", "-c", cmd], cwd=self.root, env=env).returncode
            self.log("overlay gate rc", rc)
            if rc:
                return False, "overlay window gate failed (rc %d)" % rc
        if slus_moved:
            cmd = os.environ.get("LAND_MOVE_GATE_SLUS")
            real = not cmd
            glog = self.root / "ledger/gate_slus.jsonl"
            n0 = len(read_jsonl(glog))
            rc = subprocess.run(["bash", "-c", cmd or "bash tools/build/build_slus.sh -j 8"], cwd=self.root, env=env).returncode
            self.log("SLUS gate rc", rc)
            if rc:
                return False, "SLUS gate failed (rc %d)" % rc
            if real:
                recs = read_jsonl(glog)
                if len(recs) <= n0 or recs[-1].get("result") != "MATCH" or recs[-1].get("recipe_vs_pinned") != "identical":
                    return False, "SLUS gate record is not MATCH on the pinned recipe: %s" % (recs[-1] if recs else None)
        return True, "gates MATCH"

    # ---- the run
    def run(self, apply=False):
        moves = self.plan()
        self.log("plan: %d row(s) may move" % len(moves))
        for e, row, cand, cur, rule2 in moves:
            self.log("  %-32s %s -> %s  pins %d -> %d  %s%s" % (row["id"], row["cfg"], e["to"], _pins(cur), _pins(cand),
                     "recipe-switch (rule 2 holds)" if rule2 else "coherence", "" if cand != cur else ", text unchanged"))
        if not apply or not moves:
            self.log("dry run: nothing written" if not apply else "nothing to land")
            return {"moved": [], "plan": [row["id"] for _e, row, *_ in moves]}
        overlay = [m for m in moves if m[1]["kind"] != "slus"]
        slus = [m for m in moves if m[1]["kind"] == "slus"]
        with rooted(self.root):
            snap = self.snapshot(self.touched_files(moves))
            try:
                trades = [self.trade(*m) for m in moves]
                for t in trades:
                    common.append_jsonl(self.root / "ledger/recipe_trades.jsonl", t)
                if overlay:
                    common.set_row_cfgs([(m[1]["id"], m[0]["to"], "%s: recipe moved to the retail-proven recipe (fidelity step 4)"
                                          % self.tag) for m in overlay])
                if slus:
                    self.switch_slus(slus)
                self.apply_texts(moves)
                ok, why = self.gate(bool(overlay), bool(slus))
            except Exception as ex:
                ok, why = False, "exception: %r" % (ex,)
            if not ok:
                self.log("FAILED:", why)
                self.restore(snap, bool(overlay))
                return {"moved": [], "failed": why}
        self.log("landed %d row(s)" % len(moves))
        rb = []
        if slus and self.root == REAL_ROOT:
            sys.path.insert(0, str(REAL_ROOT / "tools"))
            from verify import rebaseline_slus
            rb = rebaseline_slus([m[1]["id"] for m in slus])
            for r in rb:
                self.log("  slus cache:", r["id"], r["outcome"], r["detail"][:100])
        return {"moved": [m[1]["id"] for m in moves], "rebaselined": rb}


def _pins(text):
    sys.path.insert(0, str(REAL_ROOT / "tools"))
    from pin_census import sites_of
    return len(sites_of(text))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("tag"); ap.add_argument("lane", help="lane dir holding out/ and cells.jsonl")
    ap.add_argument("--apply", action="store_true", help="land for real (default: dry run - verify and print the plan)")
    ap.add_argument("--root", help="tree to write into (tests: a throwaway copy); default this repository")
    ap.add_argument("--round")
    a = ap.parse_args(argv)
    root = Path(a.root).resolve() if a.root else REAL_ROOT
    lane = Path(a.lane)
    if not lane.is_absolute():
        lane = (REAL_ROOT / lane) if (REAL_ROOT / lane).exists() else (REAL_ROOT / "work/native_lane" / lane)
    if a.apply and os.environ.get("LAND_ISOLATED") != "1":
        for pat in ("[c]odex exec", "[s]weep.py "):
            if subprocess.run(["pgrep", "-f", pat], capture_output=True).returncode == 0:
                raise SystemExit("a lane or sweep is running: wait (or LAND_ISOLATED=1)")
    if a.apply:                                        # one landing at a time; a dry run never queues behind one
        (root / "build_ovl/work").mkdir(parents=True, exist_ok=True)
        with open(root / "build_ovl/work/land.lock", "w") as lk:
            fcntl.flock(lk, fcntl.LOCK_EX)
            res = Lander(root, a.tag, lane, round_=a.round).run(apply=True)
    else:
        res = Lander(root, a.tag, lane, round_=a.round).run(apply=False)
    print(json.dumps(res))
    return 0 if (not a.apply or res.get("moved") or not res.get("failed")) else 1


if __name__ == "__main__":
    sys.exit(main())
