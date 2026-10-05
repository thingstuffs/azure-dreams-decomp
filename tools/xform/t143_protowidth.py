"""T143: callee prototype parameters written with the definition's (narrower) types; pins erased jointly where they fall.

APPEARS     m2c declares a callee `s32 func_X(s32, s32, s16, ...)` where the callee's definition takes s16/u16/s8/u8
            parameters.  The caller then stages the narrowing by hand (`(x << 16) >> 16`, a REG pin on the converted
            value).  Round 93 census: 1,353 such prototypes in 740 rows (22 pinned).  r93_opus_p26 solved
            dungeon/func_80CC085C 3 -> 0 by declaring `func_800A0818(s16, s16, s16, s16, void *)` from its definition:
            the call then emits retail's `sll 16; sra 16` conversions itself.
RESOLVES    the prototype's parameter list replaced by the definition's (same arity; definition found by true_name, same
            container else slus - as t138/t140).  Every widened prototype at once, then one at a time (greedy); on a
            pinned row each candidate is also tried with ALL pins erased and with each pin erased alone.
ACCEPTANCE  byte-exact; pins never grow (a pin may fall); no other text changes.
"""
import json, os, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of
from pin_sites import erase_many

MAX_VERIFY = int(os.environ.get("T143_MAX", "20"))
PROTO = re.compile(r"^(?P<head>[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t\*]*?\b(?P<name>(?:func|w)_[0-9A-Fa-f]{8})[ \t]*)\((?P<args>[^;{}()]*)\)(?P<tail>[ \t]*;)", re.M)
NARROW = re.compile(r"\b(?:s16|u16|s8|u8|short|char)\b")
_DEFS = None


def defs():
    global _DEFS
    if _DEFS is None:
        _DEFS = {}
        for l in open(ROOT / "ledger/rows.jsonl"):
            r = json.loads(l)
            _DEFS.setdefault((r["container"], r.get("true_name") or r["func"]), []).append(r["id"])
    return _DEFS


def split(s):
    s = s.strip()
    return [] if not s or s == "void" else [p.strip() for p in s.split(",")]


def ptype(p):
    m = re.match(r"(.*?)\b[A-Za-z_]\w*\s*$", p.strip())
    t = (m.group(1) if m and m.group(1).strip() else p).strip()
    return " ".join(t.split())


def def_params(container, name):
    for c in (container, "slus"):
        for rid in defs().get((c, name), []):
            p = ROOT / "src" / (rid + ".c")
            if not p.exists():
                continue
            m = re.search(r"^[A-Za-z_][\w \t\*]*?\b%s[ \t]*\(([^;{}()]*)\)[ \t\n]*\{" % re.escape(name), p.read_text(errors="replace"), re.M)
            if m:
                ps = split(m.group(1))
                if all(re.search(r"[A-Za-z_]\w*\s*$", x) for x in ps):
                    return ps
    return None


def sites(text, container):
    out = []
    for m in PROTO.finditer(text):
        ps = split(m.group("args"))
        if not ps or "..." in m.group("args"):
            continue
        d = def_params(container, m.group("name"))
        if not d or len(d) != len(ps):
            continue
        if any(NARROW.search(ptype(a)) and not NARROW.search(ptype(b)) for a, b in zip(d, ps)):
            out.append((m.start("args"), m.end("args"), ", ".join(" ".join(a.split()) for a in d)))
    return out


def rewrite(text, chosen):
    for s, e, args in sorted(chosen, key=lambda x: -x[0]):
        text = text[:s] + args + text[e:]
    return text


class T:
    name = "t143_protowidth"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text, row["id"].split("/")[0]) else "no prototype wider than its definition"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text, row["id"].split("/")[0])
        if not ss:
            return None, {"refused": ["no site"]}
        pins = sites_of(text); n0 = len(pins); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if budget[0] <= 0 or len(sites_of(t)) > n0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        def with_pins(t):
            """t, then t with all pins erased, then t with each pin erased alone (pinned rows)."""
            yield t
            ps = sites_of(t)
            if ps:
                yield erase_many(t, ps, clean_notes=True)
                if len(ps) > 1:
                    for s_ in ps:
                        yield erase_many(t, [s_], clean_notes=True)

        allt = rewrite(text, ss)
        for t in with_pins(allt):
            if ok(t):
                return t, {"prototypes": len(ss), "pins": "%d -> %d" % (n0, len(sites_of(t))), "verifies": len(tried)}
        keep = []
        for s in ss:
            t = rewrite(text, keep + [s])
            if ok(t):
                keep.append(s)
        if keep:
            base = rewrite(text, keep)
            for t in list(with_pins(base))[1:]:
                if ok(t):
                    return t, {"prototypes": len(keep), "of": len(ss), "pins": "%d -> %d" % (n0, len(sites_of(t))), "verifies": len(tried)}
            return base, {"prototypes": len(keep), "of": len(ss), "verifies": len(tried)}
        return None, {"refused": ["no widening exact (%d verifies)" % len(tried)]}
