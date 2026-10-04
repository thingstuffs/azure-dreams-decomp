"""T139: an `extern M2C_UNK D_X;` data declaration written with the type other declarations of D_X agree on (readability).

APPEARS     m2c declares data it could not type as `extern M2C_UNK D_X;` / `extern M2C_UNK D_X[];`.  Round 93: 1,650 such
            declarations; 325 (248 rows) have exactly one concrete type among the other declarations of the same symbol
            in the same container (src/<container>/*.c) and include/.
RESOLVES    that type, only when the declaration SHAPE matches (scalar for scalar, array for array - an array/scalar
            swap would change what the uses mean).  Evidence that disagrees (two concrete types) or is absent: no edit.
            Every declaration at once, then one at a time; byte-verified; pins unchanged.
"""
import glob, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of

DECL = re.compile(r"^(?P<lead>[ \t]*extern[ \t]+)(?P<ty>[A-Za-z_][\w \t\*]*?)[ \t]*\b(?P<sym>D_[0-9A-Fa-f]{8})\b[ \t]*(?P<arr>\[[^\]\n]*\])?[ \t]*;", re.M)
_EV = {}


def evidence(container):
    """{sym: {(type, is_array)}} over the container's rows and include/."""
    if container not in _EV:
        ev = {}
        files = glob.glob(str(ROOT / "src" / container / "*.c")) + glob.glob(str(ROOT / "include/**/*.h"), recursive=True)
        for f in files:
            for m in DECL.finditer(Path(f).read_text(errors="replace")):
                ty = " ".join(m.group("ty").split())
                if "M2C_UNK" in ty:
                    continue
                ev.setdefault(m.group("sym"), set()).add((ty, m.group("arr") is not None))
        _EV[container] = ev
    return _EV[container]


def sites(text, container):
    ev = evidence(container); out = []
    for m in DECL.finditer(text):
        if " ".join(m.group("ty").split()) != "M2C_UNK":
            continue
        e = ev.get(m.group("sym"), set())
        if len(e) != 1:
            continue
        ty, arr = next(iter(e))
        if arr != (m.group("arr") is not None):
            continue
        out.append((m.start(), m.end(), m, ty))
    return out


def rewrite(text, chosen):
    for s, e, m, ty in sorted(chosen, key=lambda x: -x[0]):
        sp = "" if ty.endswith("*") else " "
        text = text[:s] + "%s%s%s%s%s;" % (m.group("lead"), ty, sp, m.group("sym"), m.group("arr") or "") + text[e:]
    return text


class T:
    name = "t139_dataextern"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text, row["id"].split("/")[0]) else "no M2C_UNK data extern with one agreed type"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text, row["id"].split("/")[0])
        if not ss:
            return None, {"refused": ["no site"]}
        n0 = len(sites_of(text)); tried = [0]

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or tried[0] >= 16:
                return False
            tried[0] += 1
            return bool(vf(t).get("exact"))
        allt = rewrite(text, ss)
        if ok(allt):
            return allt, {"externs": len(ss), "verifies": tried[0]}
        keep = []
        for s in ss:
            if ok(rewrite(text, keep + [s])):
                keep.append(s)
        if keep:
            return rewrite(text, keep), {"externs": len(keep), "of": len(ss), "verifies": tried[0]}
        return None, {"refused": ["no extern rewrite exact (%d verifies)" % tried[0]]}
