"""tidy9.py DIR...: drop local view typedefs that nothing references any more (a fold left them), incl. a
   `struct X; typedef struct X X;` forward pair; re-check() each changed text (must stay exact, else untouched)."""
import json, re, sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index
from check import check
from consolidate import parse_views, code_spans
LANE = Path(__file__).resolve().parent.parent; R = row_index()
def tidy(t):
    dropped = []
    for _ in range(6):
        code = lambda s: "".join(s[a:b] for a, b in code_spans(s))
        views = parse_views(t); hit = False
        for name, v in sorted(views.items(), key=lambda kv: -kv[1][1]):
            if name.startswith("struct "): continue
            if len(re.findall(r"\b%s\b" % name, code(t))) == 1:
                a, b = v[1], v[2]
                t = t[:a] + t[b:].lstrip("\n"); dropped.append(name); hit = True; break
        if not hit:
            m = next((m for m in re.finditer(r"^struct (\w+);\s*typedef struct \1 \1;[ \t]*\n", t, re.M) if len(re.findall(r"\b%s\b" % m.group(1), code(t))) == 3), None)
            if m: t = t[:m.start()] + t[m.end():]; dropped.append("fwd " + m.group(1)); continue
            break
    return t, dropped
def one(p):
    rid = "/".join(p.parts[-2:])[:-2]; t = p.read_text(); n, d = tidy(t)
    if not d: return {"id": rid, "tidy": []}
    rec = check(R[rid], n); ok = bool((rec.get("score") or {}).get("exact"))
    if ok: p.write_text(n)
    return {"id": rid, "tidy": d, "ok": ok}
if __name__ == "__main__":
    fs = [p for d in sys.argv[1:] for p in sorted(Path(d).glob("*/*.c"))]
    with ProcessPoolExecutor(12) as ex:
        res = list(ex.map(one, fs))
    print(len(fs), "files", sum(1 for r in res if r["tidy"] and r["ok"]), "tidied", [r["id"] for r in res if r["tidy"] and not r["ok"]])
