"""T140: `argN` parameter names in a callee prototype written with the names the callee's definition uses (readability).

APPEARS     m2c writes callee prototypes with placeholder names: `extern s32 func_X(void *arg0, s32 arg1);`.  Round 93's
            Sonnet rename lanes (rn1-rn7) spent most of their edits copying the definition's names onto these.
RESOLVES    the definition's parameter names, positionally, when the definition (row whose `true_name` - or `func` when
            true_name is null - is func_X, same container else slus, with an actual `func_X(...) {` definition) has the
            SAME number of parameters and every name is a plain identifier that is not already used elsewhere in the
            prototype.  Only `argN` names are replaced (a prototype parameter that already has a real name stays).
            Types are untouched.  Byte-neutral by construction; still verified.
"""
import json, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of

_DEFS = None
PROTO = re.compile(r"^(?P<head>[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t\*]*?\b(?P<name>(?:func|w)_[0-9A-Fa-f]{8})[ \t]*)\((?P<args>[^;{}()]*)\)(?P<tail>[ \t]*;)", re.M)
ARGN = re.compile(r"^arg[0-9]$")


def defs():
    global _DEFS
    if _DEFS is None:
        _DEFS = {}
        for l in open(ROOT / "ledger/rows.jsonl"):
            r = json.loads(l)
            _DEFS.setdefault((r["container"], r.get("true_name") or r["func"]), []).append(r["id"])
    return _DEFS


def split_params(s):
    s = s.strip()
    if not s or s == "void":
        return []
    return [p.strip() for p in s.split(",")]


def pname(p):
    m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", p)
    return m.group(1) if m else None


def def_names(container, name):
    for c in (container, "slus"):
        for rid in defs().get((c, name), []):
            p = ROOT / "src" / (rid + ".c")
            if not p.exists():
                continue
            m = re.search(r"^[A-Za-z_][\w \t\*]*?\b%s[ \t]*\(([^;{}()]*)\)[ \t\n]*\{" % re.escape(name), p.read_text(errors="replace"), re.M)
            if m:
                ps = split_params(m.group(1))
                names = [pname(x) for x in ps]
                if all(n and re.fullmatch(r"[A-Za-z_]\w*", n) for n in names):
                    return names
    return None


def sites(text, container):
    out = []
    for m in PROTO.finditer(text):
        ps = split_params(m.group("args"))
        if not ps or not any(ARGN.match(pname(p) or "") for p in ps):
            continue
        dn = def_names(container, m.group("name"))
        if not dn or len(dn) != len(ps) or any(ARGN.match(n) for n in dn) or len(set(dn)) != len(dn):
            continue
        new = []
        for p, n in zip(ps, dn):
            cur = pname(p)
            if cur and ARGN.match(cur):
                p = re.sub(r"\b%s\b(\s*(\[[^\]]*\])?\s*)$" % cur, n + r"\1", p)
            new.append(p)
        if [pname(p) for p in new] != [pname(p) for p in ps]:
            if len({pname(p) for p in new}) == len(new):
                out.append((m.start("args"), m.end("args"), ", ".join(new)))
    return out


def rewrite(text, chosen):
    for s, e, args in sorted(chosen, key=lambda x: -x[0]):
        text = text[:s] + args + text[e:]
    return text


class T:
    name = "t140_protoparams"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text, row["id"].split("/")[0]) else "no argN prototype with a matching definition"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text, row["id"].split("/")[0])
        if not ss:
            return None, {"refused": ["no site"]}
        new = rewrite(text, ss)
        if len(sites_of(new)) == len(sites_of(text)) and vf(new).get("exact"):
            return new, {"prototypes": len(ss)}
        return None, {"refused": ["not exact"]}
