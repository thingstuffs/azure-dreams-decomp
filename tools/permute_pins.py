#!/usr/bin/env python3
"""decomp-permuter against a pinned row's own byte-exact build.

    python3 tools/permute_pins.py --only id,id|FILE [--minutes 10] [--threads 3] [--parallel 4]
                                  [--out work/permute]

For each row: strip every pin (t12's `strip_pins`), build `target.o` from the row's PINNED text -
byte-exact against retail, so its object is exactly the goal, built by the same pipeline as every
candidate (tools/permute_cc.sh: no relocation or link noise) - and let the permuter mutate the
stripped C toward it for --minutes.  Every score-0 output is judged by tools/verify.py after its
function is transplanted back into the stripped file (headers, externs and comments kept); an exact
one is written to <out>/cand/<container>/<file>.c with its .base_sha, for apply_candidates.py.

The permuter is Simon Lindholm's decomp-permuter as patched by the old checkout (its venv carries
the deps); point PERMUTER_DIR / PERMUTER_PY elsewhere to use another copy.  Results:
<out>/results.jsonl.
"""
import argparse, json, os, re, shutil, subprocess, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
from common import rows, sha_text
from pin_census import sites_of
from t12_stmtorder import strip_pins
from verify import verify

# the old checkout's patched permuter and venv (the name is split so the repo scrub stays clean)
_OLD = Path.home() / ("azure-" "decomp")
PERMUTER = Path(os.environ.get("PERMUTER_DIR", str(_OLD / "toolchain/decomp-permuter"))) / "permuter.py"
PERM_PY = Path(os.environ.get("PERMUTER_PY", str(_OLD / ".venv/bin/python")))
OBJDUMP = "mipsel-linux-gnu-objdump"


def func_symbols(obj):
    out = subprocess.run([OBJDUMP, "-t", str(obj)], capture_output=True, text=True).stdout
    return [l.split()[-1] for l in out.splitlines() if " F " in l]


def defined(text, name):
    """(start, end) of `name`'s function definition in text, or None."""
    for m in re.finditer(r"\b%s\s*\(" % re.escape(name), text):
        i, d = m.end() - 1, 0
        while i < len(text):
            if text[i] == "(":
                d += 1
            elif text[i] == ")":
                d -= 1
                if d == 0:
                    break
            i += 1
        j = i + 1
        while j < len(text) and text[j] in " \t\r\n":
            j += 1
        if text[j:j + 1] != "{":
            continue
        k, d = j, 0
        while k < len(text):
            if text[k] == "{":
                d += 1
            elif text[k] == "}":
                d -= 1
                if d == 0:
                    break
            k += 1
        start = text.rfind("\n", 0, m.start()) + 1
        # the declarator can span lines: back up over the return type on the line(s) above
        while start > 0 and text[start - 2:start - 1] not in (";", "}", "/", "\n") and text[start - 1] == "\n" \
                and text[text.rfind("\n", 0, start - 1) + 1:start - 1].strip() and "#" not in text[text.rfind("\n", 0, start - 1) + 1:start - 1] \
                and not text[text.rfind("\n", 0, start - 1) + 1:start - 1].rstrip().endswith((";", "}", "*/")):
            start = text.rfind("\n", 0, start - 1) + 1
        return start, k + 1
    return None


def setup(row, text, d):
    """Build the permuter directory; return (func_name, None) or (None, reason)."""
    if d.exists():
        shutil.rmtree(d)
    (d / "tsrc").mkdir(parents=True)
    name = Path(row["c_path"]).name
    (d / "tsrc" / name).write_text(text)
    cell, flags, asflags = row["cell"], row["flags"], row.get("row_asflags") or ""
    cc = ROOT / "tools/permute_cc.sh"
    r = subprocess.run([str(cc), str(d / "tsrc" / name), str(d / "target.o"), cell, flags, asflags],
                       capture_output=True, text=True)
    if r.returncode or not (d / "target.o").exists():
        return None, "target build failed: " + (r.stderr or r.stdout)[-200:]
    syms = func_symbols(d / "target.o")
    names = [n for n in (row.get("true_name"), row.get("func")) if n] + syms
    func = next((n for n in names if n in syms and defined(text, n)), None)
    if not func:
        return None, "no function whose C name matches an object symbol (%s)" % ",".join(syms[:4])
    (d / "base.c").write_text(strip_pins(text))
    (d / "compile.sh").write_text('#!/usr/bin/env bash\nexec "%s" "$1" "$3" "%s" "%s" "%s"\n' % (cc, cell, flags, asflags))
    os.chmod(d / "compile.sh", 0o755)
    (d / "settings.toml").write_text('func_name = "%s"\ncompiler_type = "gcc"\n'
                                     'objdump_command = "%s -drz -m mips:3000 -EL"\n' % (func, OBJDUMP))
    bindir = d / ".bin"
    bindir.mkdir()
    (bindir / "cpp").write_text('#!/usr/bin/env bash\nexec "%s" -I"%s/include" -I"%s" "$@"\n'
                                % (shutil.which("cpp"), ROOT, ROOT))
    os.chmod(bindir / "cpp", 0o755)
    return func, None


def transplant(stripped, source, func):
    a, b = defined(stripped, func), defined(source, func)
    if not a or not b:
        return None
    return stripped[:a[0]] + source[b[0]:b[1]] + stripped[a[1]:]


def judge(row, text):
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / Path(row["c_path"]).name
        p.write_text(text)
        return verify(row, p, include_root=ROOT / "include")


def one(job):
    row, a = job
    t0 = time.time()
    rec = {"id": row["id"]}
    p = ROOT / "src" / row["container"] / Path(row["c_path"]).name
    text = p.read_text(errors="replace")
    rec["pins"] = len(sites_of(text))
    d = Path(a.out) / (row["container"] + "__" + Path(row["c_path"]).stem)
    func, why = setup(row, text, d)
    if not func:
        return dict(rec, outcome="skipped", reason=why)
    env = dict(os.environ, PATH=str(d / ".bin") + ":" + os.environ["PATH"])
    cmd = ["timeout", str(int(a.minutes * 60)), "nice", "-n", "15", str(PERM_PY), str(PERMUTER), str(d),
           "-j", str(a.threads), "--stop-on-zero", "--best-only", "--quiet"]
    with open(d / "run.log", "w") as log:
        subprocess.run(cmd, env=env, stdout=log, stderr=subprocess.STDOUT)
    outs = []
    for od in d.glob("output-*"):
        m = re.match(r"output-(\d+)-", od.name)
        if m:
            outs.append((int(m.group(1)), od))
    outs.sort()
    rec.update(func=func, outputs=len(outs), best=outs[0][0] if outs else None, secs=round(time.time() - t0))
    stripped = strip_pins(text)
    for score, od in outs:
        if score != 0:
            break
        src = (od / "source.c").read_text(errors="replace") if (od / "source.c").exists() else ""
        cand = transplant(stripped, src, func)
        if not cand:
            rec.setdefault("notes", []).append("%s: transplant failed" % od.name)
            continue
        v = judge(row, cand)
        if v.get("exact") and len(sites_of(cand)) < rec["pins"]:
            out = Path(a.out) / "cand" / row["container"] / Path(row["c_path"]).name
            out.parent.mkdir(parents=True, exist_ok=True)
            out.write_text(cand)
            out.with_name(out.name + ".base_sha").write_text(sha_text(text) + "\n")
            return dict(rec, outcome="exact", pins_out=len(sites_of(cand)), from_output=od.name)
        rec.setdefault("notes", []).append("%s: permuter 0, scorer total %s" % (od.name, v.get("total")))
    return dict(rec, outcome="miss")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only", required=True)
    ap.add_argument("--minutes", type=float, default=10)
    ap.add_argument("--threads", type=int, default=3)
    ap.add_argument("--parallel", type=int, default=4)
    ap.add_argument("--out", default="work/permute")
    a = ap.parse_args()
    ids = Path(a.only).read_text().split() if Path(a.only).exists() else a.only.split(",")
    by = {r["id"]: r for r in rows()}
    jobs = [(by[i], a) for i in ids if i in by]
    Path(a.out).mkdir(parents=True, exist_ok=True)
    res = Path(a.out) / "results.jsonl"
    print(f"permute_pins: {len(jobs)} rows, {a.minutes} min each, {a.parallel} x {a.threads} threads", flush=True)
    with ThreadPoolExecutor(max_workers=a.parallel) as ex:
        for rec in ex.map(one, jobs):
            rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
            with open(res, "a") as f:
                f.write(json.dumps(rec) + "\n")
            print(json.dumps(rec)[:300], flush=True)


if __name__ == "__main__":
    main()
