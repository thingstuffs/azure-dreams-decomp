"""respell8.py: mechanical respell of a text onto GameWork's `view` member (r78 phase 8).
   gameWork.F / P->F (P declared `GameWork *P`) for every flat field F in gameWork+0x018..0x1DB -> the member path
   from respell_map8.json (gameWork.viewAngle -> gameWork.view.viewAngle, gameWork.unk_0A8 -> gameWork.view.unk_090,
   gameWork.unk_154 -> gameWork.view.slot[2].callback, ...).  `&gameWork.unk_018` under a pointer cast becomes
   `&gameWork.view` (the sub-object's address), otherwise `&gameWork.view.unk_000` (same type as before).
   Layout identity is proven by offsets8.py; the respell changes spelling only.
   CLI: respell8.py FILE...  (rewrites in place, prints `changed N` per file; exit 2 if a leftover is suspect)"""
import json, re, sys
from pathlib import Path
M = json.load(open(Path(__file__).resolve().parent / "respell_map8.json"))
FIELDS = "|".join(sorted(M, key=len, reverse=True))
def gw_vars(text):
    return set(re.findall(r"\bGameWork\s*\*\s*(?:const\s+)?([A-Za-z_]\w*)", text))
def respell(text):
    n = [0]
    def cast018(m):
        n[0] += 1; return m.group(1) + "&gameWork.view"
    # &gameWork.unk_018 directly under a pointer cast: the sub-object's own address
    t = re.sub(r"(\(\s*[A-Za-z_][\w ]*\*+\s*\)\s*\(?\s*)&\s*gameWork\s*\.\s*unk_018\b", cast018, text)
    def sub_dot(m):
        n[0] += 1; return "%s.%s" % (m.group(1), M[m.group(2)])
    t = re.sub(r"\b(gameWork)\s*\.\s*(%s)\b" % FIELDS, sub_dot, t)
    vs = gw_vars(t)
    if vs:
        def sub_arrow(m):
            n[0] += 1; return "%s->%s" % (m.group(1), M[m.group(2)])
        t = re.sub(r"\b(%s)\s*->\s*(%s)\b" % ("|".join(sorted(vs)), FIELDS), sub_arrow, t)
    # ((GameWork *)x)->F
    def sub_cast(m):
        n[0] += 1; return "%s->%s" % (m.group(1), M[m.group(2)])
    t = re.sub(r"(\(\s*GameWork\s*\*\s*\)\s*[A-Za-z_]\w*\s*\))\s*->\s*(%s)\b" % FIELDS, sub_cast, t)
    return t, n[0]
def suspects(text):
    """moved-field names still spelled directly off a GameWork-looking base (left for a human)"""
    vs = gw_vars(text) | {"gameWork"}
    out = [m.group(0) for m in re.finditer(r"\b(%s)\s*(\.|->)\s*(%s)\b" % ("|".join(sorted(vs)), FIELDS), text)]
    gv = set(re.findall(r"\bGameView\s*\*\s*([A-Za-z_]\w*)", text)) | set(re.findall(r"\bextern\s+GameView\s+([A-Za-z_]\w*)", text))
    ok = r"(?:\bview\s*\.|\b(?:%s)\s*(?:->|\.))\s*$" % "|".join(sorted(gv)) if gv else r"\bview\s*\.\s*$"
    out += [m.group(0) for m in re.finditer(r"\bviewAngle\b", text) if not re.search(ok, text[max(0, m.start() - 40):m.start()])]
    return out
if __name__ == "__main__":
    rc = 0
    for f in sys.argv[1:]:
        p = Path(f); t0 = p.read_text(errors="replace"); t, k = respell(t0)
        if t != t0: p.write_text(t)
        s = suspects(t)
        print(f, "changed", k, ("SUSPECT %s" % s[:4]) if s else "")
        if s: rc = 2
    sys.exit(rc)
