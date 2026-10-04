"""T138: an `M2C_UNK func_X();` prototype written with the return type of func_X's real definition (readability; pins untouched).

APPEARS     m2c declares callees it could not type as `M2C_UNK func_X();  /* extern */`.  Round 93's Sonnet/luna prototype
            lanes typed ~1,000 of them by hand from the callee's definition; what was left was one prototype per row.
RESOLVES    the definition's return type, found the way tools/lanes/proto_check.py checks it: the row whose `true_name`
            is func_X (or whose `func` is func_X when true_name is null) in the SAME container, else slus; the definition
            line `<type> func_X(...) {` in that row's source.  Rows are filed by file offset, so a row FILED as func_X
            may define a different function - only an actual definition of func_X counts.  A same-address function in
            another overlay is a different function and is never used.  Types the row cannot see (a struct pointer not
            declared in the row) are skipped.  The parameter list stays `()`.
            Candidates: every prototype at once, then one at a time; byte-verified (a return type can move bytes in
            principle: the verifier decides).  Pins unchanged; the leftover count must fall.
"""
import json, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of

_DEFS = None
PROTO = re.compile(r"^(?P<lead>[ \t]*(?:extern[ \t]+)?)M2C_UNK(?P<sp>[ \t]+)(?P<name>(?:func|w)_[0-9A-Fa-f]{8})[ \t]*\((?P<args>[^;{}]*)\)[ \t]*;", re.M)
BASIC = {"void", "s8", "u8", "s16", "u16", "s32", "u32", "int", "char", "short", "long", "unsigned", "signed",
         "unsigned int", "unsigned char", "unsigned short", "f32", "float"}


def defs():
    global _DEFS
    if _DEFS is None:
        _DEFS = {}
        for l in open(ROOT / "ledger/rows.jsonl"):
            r = json.loads(l)
            name = r.get("true_name") or r["func"]
            _DEFS.setdefault((r["container"], name), []).append(r["id"])
    return _DEFS


def def_type(container, name):
    for c in (container, "slus"):
        for rid in defs().get((c, name), []):
            p = ROOT / "src" / (rid + ".c")
            if not p.exists():
                continue
            m = re.search(r"^([A-Za-z_][\w \t\*]*?)[ \t]*\b%s[ \t]*\([^;{]*\)[ \t\n]*\{" % re.escape(name), p.read_text(errors="replace"), re.M)
            if m:
                t = " ".join(m.group(1).replace("static", "").split())
                return t or None
    return None


def visible(t, text):
    base = t.replace("*", "").replace("const", "").strip()
    return base in BASIC or bool(re.search(r"\b(typedef\b[^;]*\b%s\b|struct\s+%s\b)" % (re.escape(base), re.escape(base)), text)) \
        or base in ("EntityRec", "GameWork")


def sites(text, container):
    out = []
    for m in PROTO.finditer(text):
        t = def_type(container, m.group("name"))
        if t and t != "M2C_UNK" and "M2C_UNK" not in t and visible(t, text):
            out.append((m.start(), m.end(), m, t))
    return out


def rewrite(text, chosen):
    for s, e, m, t in sorted(chosen, key=lambda x: -x[0]):
        sp = "" if t.endswith("*") else " "
        text = text[:s] + "%s%s%s%s(%s);" % (m.group("lead"), t, sp, m.group("name"), m.group("args")) + text[e:]
    return text


class T:
    name = "t138_protodef"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text, row["id"].split("/")[0]) else "no M2C_UNK prototype with a visible definition type"

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
            return allt, {"protos": len(ss), "verifies": tried[0]}
        keep = []
        for s in ss:
            if ok(rewrite(text, keep + [s])):
                keep.append(s)
        if keep:
            return rewrite(text, keep), {"protos": len(keep), "of": len(ss), "verifies": tried[0]}
        return None, {"refused": ["no prototype rewrite exact (%d verifies)" % tried[0]]}
