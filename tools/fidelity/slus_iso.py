#!/usr/bin/env python3
"""An isolated SLUS link gate: prove slus TU texts AT A GIVEN RECIPE by building the whole executable in a
private copy of build_slus/ and comparing it with retail (config/slus_006.14.sha1 + baserom/).

Why this exists (fidelity step 4, docs/TOOLCHAIN_FIDELITY_PLAN.md).  tools/verify.py scores a slus row by
object identity (or masked disassembly) against the cached PINNED object (ledger/cache/slus_dis, built from
raw/ at the registered recipe).  A pinned page-constant text assembles `lui $2,0x8008` as a literal
immediate, while its natural spelling carries `lui $2,%hi(D_80082E60)` + an R_MIPS_HI16 relocation: the
linked bytes can be identical and verify still reads ~100 "differences" (lane r77_fable_splitaddr's 95 / 97
/ 187 cellscore totals against 0 / 7 / 40 relocation-resolved words).  The link resolves every relocation
the way the real gate does, so it is the only honest scorer for a symbol respelling of a slus row.

    view = SlusView(dest)                        # copy of build_slus/ (objects, recipe, ninja log); src/ is a
                                                 # directory of symlinks into src/slus/, so one TU can be swapped
    r = view.gate({"w_8003D92C": (text, "2.7.2-cdk", "")})   # -> {"result": "MATCH"|"NO MATCH"|"ERROR", ...}

`gate()` writes each candidate TU as a real file, rewrites its `ccver`/`ccflags` lines in the copy's
build.ninja, runs ninja (the changed TUs + link + objcopy), compares the image with the baserom, then puts
the view back: the symlinks and the pristine recipe return and the swapped TUs are rebuilt pristine, so the
next call starts from the gated tree.  Residue when not MATCH: differing 4-byte words overall and inside the
changed TUs' functions (addresses from the copy's linked ELF), and the size drift of those functions.

`strip_externs=True` models genuine ASPSX's small-data rule (every `.extern` absolute; only TU-defined
small .comm/.sbss `$gp`-relative - lane r77_fable_splitaddr, docs/evidence/fidelity_step1_aspsx_diff.md)
by withholding the `.extern` lines from maspsx for the swapped TUs only (AZURE_MASPSX_COMPANION wrapper),
except `keep_externs`: the symbols retail proves `$gp`-relative (R_MIPS_GPREL16 in the pinned object,
`gp_symbols()`), which the original TU must have defined.
It is a MEASUREMENT of the pending step-3 decision 3, never a landing path: a text exact only with it on
does not pass the real SLUS gate today.

Nothing under the real build_slus/, src/, ledger/ or config/ is written.  The copy is ~8 MB.
"""
from __future__ import annotations
import os, re, shutil, subprocess, sys, tempfile
import json
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from common import ROOT, parse_cfg  # noqa: E402
from slus_module_context import load_manifest, module_for_row  # noqa: E402
import slus_partitions as partitions  # noqa: E402
from row_db import edges_of  # noqa: E402
from slus_modules import logical_edges  # noqa: E402
from fidelity.objread import read_elf  # noqa: E402

BUILD_SLUS = ROOT / "build_slus"
IMAGE = "build/slus_006.14"
ELF = "build/slus_006.14.elf"
NICE = ["nice", "-n10", "ionice", "-c2", "-n7"]

STRIP_WRAPPER = r'''#!/usr/bin/env python3
# fidelity step 4 measurement: withhold the `.extern` lines from maspsx (genuine ASPSX addresses every
# extern absolutely) except the symbols named in AZURE_STEP4_KEEP_EXTERNS (the ones retail proves
# $gp-relative, i.e. defined in the original TU), then run the real maspsx with the same arguments.
import os, subprocess, sys
keep = set(filter(None, os.environ.get("AZURE_STEP4_KEEP_EXTERNS", "").split(",")))
src = sys.stdin.read()
def drop(l):
    s = l.strip()
    return s.startswith(".extern") and s[len(".extern"):].split(",")[0].strip() not in keep
out = "".join(l for l in src.splitlines(True) if not drop(l))
maspsx = os.environ["AZURE_STEP4_REAL_MASPSX"]
sys.exit(subprocess.run([sys.executable, maspsx] + sys.argv[1:], input=out, text=True).returncode)
'''


def tu_block_re(stem):
    return re.compile(r"(^build build/src/%s\.o: cc \S+[^\n]*\n  ccver = )([^\n]*)(\n  ccflags = )([^\n]*)(\n)"
                      % re.escape(stem), re.M)


def set_tu_recipe(ninja_text: str, stem: str, cell: str, flags: str) -> str:
    """The recipe text with TU `stem`'s ccver/ccflags replaced (ValueError when the TU has no cc edge)."""
    rx = tu_block_re(stem)
    if not rx.search(ninja_text):
        raise ValueError(f"no cc edge for src/{stem}.c in the recipe")
    return rx.sub(lambda m: m.group(1) + cell + m.group(3) + flags + m.group(5), ninja_text, count=1)


def gp_symbols(stem):
    """Symbols the pinned (retail-exact) object of TU `stem` addresses through $gp (ledger/cache/slus_dis)."""
    p = ROOT / "ledger" / "cache" / "slus_dis" / f"{stem}.txt"
    if not p.exists():
        return set()
    return set(re.findall(r"R_MIPS_GPREL16\s+([A-Za-z_][\w.]*)", p.read_text()))


def cfg_to_ninja(cfg: str):
    """'2.7.2-cdk -G0 -fno-x' -> ('2.7.2-cdk', '-G0 -fno-x') - the recipe's ccver / ccflags pair."""
    cell, flags = parse_cfg(cfg)
    return cell, " ".join(flags)


class SlusView:
    def __init__(self, dest=None, source=BUILD_SLUS):
        source = Path(source)
        self.src_real = Path(os.path.realpath(source / "src"))
        self.dest = Path(dest) if dest else Path(tempfile.mkdtemp(prefix="slus_iso_"))
        if self.dest.exists() and (self.dest / "build.ninja").exists() and (self.dest / ".iso_ok").exists():
            pass                                              # reuse a prepared view
        else:
            if self.dest.exists():
                shutil.rmtree(self.dest)
            if not (source / "build.ninja").exists() or not (source / IMAGE).exists():
                raise RuntimeError("build_slus/ has no built tree: run tools/build/build_slus.sh first")
            shutil.copytree(source, self.dest, symlinks=True)
            srcdir = self.dest / "src"
            real = Path(os.path.realpath(srcdir))
            if srcdir.is_symlink():
                srcdir.unlink()
                srcdir.mkdir()
                for f in sorted(real.iterdir()):
                    (srcdir / f.name).symlink_to(f)
            (self.dest / ".iso_ok").write_text("")
        self.pristine = (self.dest / "build.ninja").read_text()
        self.modules = load_manifest(self.dest / "config/slus_modules.json")
        self.partitions = partitions.load_plan(self.dest / "config/slus_partitions.json")
        if self.partitions:
            self.aliases = partitions.read_aliases(self.dest / "config/names.tsv")
            edges = logical_edges(partitions.project_edges(edges_of(self.pristine), self.partitions), self.modules)
            expected = [json.loads(line) for line in (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line.strip()]
            if edges != expected:
                raise ValueError("partition build differs from the complete logical ledger")
            partitions.validate_context(self.partitions, self.modules, edges, self.dest / "raw/slus", self.aliases)

    def physical_stem(self, stem):
        if self._partition_context(stem)[0]:
            raise ValueError("partition context requires physical_stems: " + stem)
        module = module_for_row(self.modules, "slus/" + stem)
        return Path(module["source"]).stem if module else stem

    def _partition_context(self, stem):
        return partitions.connected_context("slus/" + stem, getattr(self, "partitions", []), self.modules)

    def physical_stems(self, stem):
        parents, owners = self._partition_context(stem)
        if parents:
            return [Path(unit["source"]).stem for unit in partitions.row_units("slus/" + stem, parents, owners)]
        return [self.physical_stem(stem)]

    def _requested_recipes(self, stem, cell, flags):
        parents, owners = self._partition_context(stem)
        if not parents:
            return {self.physical_stem(stem): (cell, flags)}
        parent = next((p for p in parents if p["id"] == "slus/" + stem), None)
        recipe = parent["recipe"] if parent else module_for_row(owners, "slus/" + stem)["recipe"]
        if (cell, flags) != (recipe["ccver"], recipe["ccflags"]):
            raise ValueError("partition recipe trial requires an explicit physical-owner plan: " + stem)
        return {Path(unit["source"]).stem: (unit["recipe"]["ccver"], unit["recipe"]["ccflags"])
                for unit in partitions.row_units("slus/" + stem, parents, owners)}

    def _partition_coverage(self):
        """Source parsing cannot detect every macro-generated function: read ELF."""
        for module in self.modules:
            if module.get("data_pieces"):
                from slus_data_pieces import verify_data_pieces
                verify_data_pieces(self.dest / "build" / Path(module["source"]).with_suffix(".o"), module)
        plan = getattr(self, "partitions", [])
        if not plan:
            return
        names = {part["module"] for parent in plan for part in parent["parts"]}
        owners = [module for module in self.modules if module["name"] in names]
        expected = partitions.expected_units(plan, owners)
        emitted = {}
        for source in expected:
            obj = read_elf((self.dest / "build/src" / (Path(source).stem + ".o")).read_bytes())
            emitted[source] = [self.aliases.get(name, name) for name, symbol in obj.symbols.items()
                if symbol[2] == "func" and symbol[0] and (symbol[0] == ".text" or symbol[0].startswith(".text."))]
        partitions.check_emitted(expected, emitted)

    # ---------------------------------------------------------------- helpers
    def _ninja(self, targets, env=None):
        if env is None:
            env = dict(os.environ)
            env.pop("AZURE_MASPSX", None); env.pop("AZURE_MASPSX_COMPANION", None)
        r = subprocess.run(NICE + ["ninja", "-C", str(self.dest), "-j", "2"] + targets, capture_output=True, text=True,
                           env=env, timeout=1800)
        return r.returncode, (r.stdout + r.stderr)

    def _restore(self, stems, snapshots=None):
        (self.dest / "build.ninja").write_text(self.pristine)
        for stem in stems:
            p = self.dest / "src" / f"{stem}.c"
            if p.is_symlink() or p.exists():
                p.unlink()
            if snapshots is None:
                p.symlink_to(self.src_real / f"{stem}.c")
            else:
                saved = snapshots[stem]
                if saved["link"] is not None:
                    p.symlink_to(saved["link"])
                else:
                    p.write_bytes(saved["bytes"])
                    p.chmod(saved["mode"])
                    os.utime(p, ns=saved["times"])
        paths = partitions.output_paths(getattr(self, "partitions", []))
        for parent in getattr(self, "partitions", []):
            if Path(parent["source"]).stem in stems:
                for relative in [paths["remainders"][parent["source"]], *paths["parts"][parent["id"]].values()]:
                    p = self.dest / relative
                    if p.exists():
                        p.unlink()
        for stem in {target for s in stems for target in self.physical_stems(s)}:
            o = self.dest / "build" / "src" / f"{stem}.o"
            if o.exists():
                o.unlink()
        if stems:
            rc, out = self._ninja([IMAGE])     # stock env: the pristine objects and image back
            if rc:
                raise RuntimeError("could not rebuild the pristine objects of %s: %s" % (stems, out[-400:]))
            self._partition_coverage()
            if (self.dest / IMAGE).read_bytes() != (ROOT / "baserom/slus_006.14").read_bytes():
                raise RuntimeError("restored isolated view does not reproduce retail")

    def symbols(self):
        """{name: (addr, size)} of the copy's linked ELF (functions and objects with a size)."""
        r = subprocess.run(["mipsel-linux-gnu-nm", "-S", "--defined-only", str(self.dest / ELF)], capture_output=True, text=True)
        out = {}
        for line in r.stdout.splitlines():
            p = line.split()
            if len(p) == 4:
                out[p[3]] = (int(p[0], 16), int(p[1], 16))
        return out

    def tu_functions(self, stem):
        """Global functions TU `stem` defines (its object's `T` symbols)."""
        o = self.dest / "build" / "src" / f"{stem}.o"
        r = subprocess.run(["mipsel-linux-gnu-nm", "--defined-only", str(o)], capture_output=True, text=True)
        return [l.split()[2] for l in r.stdout.splitlines() if len(l.split()) == 3 and l.split()[1] == "T"]

    def calibrate(self):
        """Build the view as it stands (the current src/slus texts at the pinned recipe) and compare with
        retail: the control every measurement starts from.  Returns the same record as gate()."""
        rc, out = self._ninja([IMAGE])
        if rc:
            return {"result": "ERROR", "detail": out[-600:].replace(str(ROOT), "<repo>")}
        try:
            self._partition_coverage()
        except (OSError, ValueError) as exc:
            return {"result": "ERROR", "detail": "partition coverage: " + str(exc)}
        got = (self.dest / IMAGE).read_bytes(); ref = (ROOT / "baserom" / "slus_006.14").read_bytes()
        return {"result": "MATCH" if got == ref else "NO MATCH", "words_diff": len(self._diff_words(got, ref))}

    # ---------------------------------------------------------------- the gate
    def pristine_symbols(self):
        """{name: (addr, size)} of the view built from the current src/slus at the pinned recipe (cached)."""
        if getattr(self, "_pristine_syms", None) is None:
            cal = self.calibrate()
            if cal["result"] != "MATCH":
                raise RuntimeError("the isolated view does not reproduce retail before any change: %s" % cal)
            self._pristine_syms = self.symbols()
        return self._pristine_syms

    def gate(self, changes: dict, strip_externs=False, keep=False, keep_externs=()):
        """changes: {stem: (text or None, cell, flags)} - text None keeps the TU's current src text.
        Returns {"result": MATCH|NO MATCH|ERROR, "words_diff" (whole image), "residue" (aligned word diff
        of the swapped TUs' functions against their retail words), "fn_size_drift", "detail"}."""
        import difflib
        stems = list(changes)
        if any(not re.fullmatch(r"[A-Za-z0-9_]+", stem) for stem in stems):
            return {"result": "ERROR", "detail": "invalid logical source stem"}
        physical = list(dict.fromkeys(target for s in stems for target in self.physical_stems(s)))
        recipes = {}
        try:
            for stem, (_, cell, flags) in changes.items():
                for target, recipe in self._requested_recipes(stem, cell, flags).items():
                    if target in recipes and recipes[target] != recipe:
                        return {"result": "ERROR", "detail": f"conflicting recipes for module {target}"}
                    recipes[target] = recipe
        except ValueError as exc:
            return {"result": "ERROR", "detail": str(exc)}
        for module in self.modules:
            target = Path(module["source"]).stem
            original = (module["recipe"]["ccver"], module["recipe"]["ccflags"])
            if target in recipes and recipes[target] != original:
                cohort = {Path(m["source"]).stem for m in module["members"]}
                if not cohort.issubset(changes):
                    return {"result": "ERROR", "detail": f"recipe change requires every member of module {target}"}
        text = self.pristine
        before = self.pristine_symbols()
        fn_before = {s: self.tu_functions(s) for s in physical}
        snapshots = {}
        for stem in stems:
            p = self.dest / "src" / f"{stem}.c"
            stat = p.stat()
            snapshots[stem] = {"link": os.readlink(p) if p.is_symlink() else None,
                               "bytes": p.read_bytes(), "mode": stat.st_mode & 0o777,
                               "times": (stat.st_atime_ns, stat.st_mtime_ns)}
        try:
            for target, (cell, flags) in recipes.items():
                text = set_tu_recipe(text, target, cell, flags)
            for stem, (ctext, cell, flags) in changes.items():
                if ctext is not None:
                    p = self.dest / "src" / f"{stem}.c"
                    p.unlink()
                    p.write_text(ctext)
            for target in physical:
                o = self.dest / "build" / "src" / f"{target}.o"
                if o.exists():
                    o.unlink()
            (self.dest / "build.ninja").write_text(text)
            env = dict(os.environ)
            env.pop("AZURE_MASPSX", None); env.pop("AZURE_MASPSX_COMPANION", None)
            if strip_externs:
                w = self.dest / "strip_extern_maspsx.py"
                w.write_text(STRIP_WRAPPER)
                env["AZURE_MASPSX_COMPANION"] = str(w)
                env["AZURE_STEP4_REAL_MASPSX"] = str(ROOT / "tools" / "maspsx" / "maspsx.py")
                env["AZURE_STEP4_KEEP_EXTERNS"] = ",".join(sorted(keep_externs))
            rc, out = self._ninja([f"build/src/{s}.o" for s in physical], env=env)
            if rc:
                return {"result": "ERROR", "detail": "compile: " + out[-600:].replace(str(ROOT), "<repo>")}
            try:
                self._partition_coverage()
            except (OSError, ValueError) as exc:
                return {"result": "ERROR", "detail": "partition coverage: " + str(exc)}
            rc, out = self._ninja([IMAGE])
            if rc:
                return {"result": "ERROR", "detail": "link: " + out[-600:].replace(str(ROOT), "<repo>")}
            got = (self.dest / IMAGE).read_bytes()
            ref = (ROOT / "baserom" / "slus_006.14").read_bytes()
            if got == ref:
                return {"result": "MATCH", "words_diff": 0, "residue": 0, "fn_size_drift": {}, "detail": ""}
            syms = self.symbols()
            load = self._load_base(ref)
            drift, residue, per_fn = {}, 0, {}
            for s in physical:
                for f in sorted(set(fn_before[s]) | set(self.tu_functions(s))):
                    a, b = syms.get(f), before.get(f)
                    if not a or not b:
                        per_fn[f] = "missing"; continue
                    if a[1] != b[1]:
                        drift[f] = a[1] - b[1]
                    gw = [got[i:i + 4] for i in range(a[0] - load, a[0] - load + a[1], 4)]
                    tw = [ref[i:i + 4] for i in range(b[0] - load, b[0] - load + b[1], 4)]
                    d = sum(max(a2 - a1, b2 - b1) for op, a1, a2, b1, b2 in
                            difflib.SequenceMatcher(None, gw, tw, autojunk=False).get_opcodes() if op != "equal")
                    per_fn[f] = d; residue += d
            words = self._diff_words(got, ref)
            return {"result": "NO MATCH", "words_diff": len(words), "residue": residue, "per_fn": per_fn,
                    "fn_size_drift": drift, "detail": "%d differing words in the swapped TUs' functions (aligned "
                    "against retail)%s; %d image words differ" % (residue, "; size drift %s" % drift if drift else "", len(words))}
        finally:
            if not keep:
                self._restore(stems, snapshots)

    @staticmethod
    def _diff_words(a: bytes, b: bytes):
        n = min(len(a), len(b))
        out = [i for i in range(0, n - n % 4, 4) if a[i:i + 4] != b[i:i + 4]]
        if len(a) != len(b):
            out.append(n)
        return out

    @staticmethod
    def _load_base(image: bytes):
        """vram of image offset 0: a PS-X EXE's text address (header word 0x18) sits at offset 0x800."""
        import struct
        if image[:8] != b"PS-X EXE":
            return None
        return struct.unpack("<I", image[0x18:0x1c])[0] - 0x800


def main():
    import argparse, json
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("stem"); ap.add_argument("cand"); ap.add_argument("--cfg", required=True)
    ap.add_argument("--view", help="a prepared view dir to reuse"); ap.add_argument("--strip-externs", action="store_true")
    a = ap.parse_args()
    v = SlusView(a.view)
    cell, flags = cfg_to_ninja(a.cfg)
    print(json.dumps(v.gate({a.stem: (Path(a.cand).read_text(), cell, flags)}, strip_externs=a.strip_externs), indent=1))


if __name__ == "__main__":
    main()
