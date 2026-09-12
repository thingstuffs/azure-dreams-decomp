#!/usr/bin/env python3
"""Static census of every row's C at the pin -> ledger/census.jsonl (one record per row)."""
import json, re, collections
from pathlib import Path
from common import ROOT, LEDGER, rows, write_jsonl, raw_path
from pin_census import sites_of

PIN_RE = re.compile(r"\bASM_([A-Z0-9_]+)\(")
REG_RE = re.compile(r'ASM_REG\("\$?([a-z0-9]+)"\)')
M2C_LOCAL_RE = re.compile(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+|phi_[a-z0-9_]+)\b")
LOCAL_STRUCT_RE = re.compile(r"\b((?:S_|Struct|Func)[0-9A-F]{7,8}[A-Za-z0-9_]*)\b")
CALL_RE = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")
DATA_RE = re.compile(r"\b(D_[0-9A-F]{8})\b")
LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:\s*(?://.*|/\*.*)?$", re.M)
DEF_RE = re.compile(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\(", re.M)

def audit_index():
    d = json.load(open(ROOT / "config/decomp_audit_baseline.json"))
    idx = {}
    for key, v in d.get("sites", {}).items():
        c = collections.Counter(s.split("|")[0] for s in v.get("sites", []))
        idx[key] = dict(c)
    return idx

DECL_LINE = re.compile(r"^[ \t]*(?!(?:return|goto|if|else|while|for|switch|case|do)\b)(?:extern[ \t]+)?[A-Za-z_][A-Za-z0-9_ \t\*]*\b(?P<name>func_[0-9A-F]{8}|[A-Za-z_][A-Za-z0-9_]*)[ \t]*\([^;{]*\)[ \t]*(?:__attribute__[^;]*)?;[ \t]*$")   # a type-prefixed prototype, never a `return f();` statement

def live_sites(text, sites):
    """The baseline audit (config/decomp_audit_baseline.json) grandfathers every fidelity site as it
    was at the pin.  A site is LIVE only while the current text still carries its spelling: a
    LABEL_AS_CALL site while `target(` is still called (declarations do not count), a
    PASSTHRU_NO_ARGS site while an empty-paren call of the target remains.  The other classes are
    byte-derived and never block; they are kept as recorded."""
    calls = "\n".join(l for l in text.splitlines() if not DECL_LINE.match(l) and not l.lstrip().startswith("#"))
    # `extern T name_tail(void) asm("func_X");` aliases: a call of the alias is a call of func_X
    aliases = {}
    for m in re.finditer(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\([^)]*\)\s*(?:__attribute__\(\([^)]*\)\)\s*)?(?:__asm__|asm)\s*\(\s*\"(func_[0-9A-F]{8})\"\s*\)", text):
        aliases.setdefault(m.group(2), set()).add(m.group(1))
    def called(tgt, empty=False):
        names = [tgt] + sorted(aliases.get(tgt, ()))
        pat = r"(?<![A-Za-z0-9_])(?:" + "|".join(re.escape(n) for n in names) + r")\s*\(" + (r"\s*\)" if empty else "")
        return re.search(pat, calls) is not None
    out = []
    for s in sites:
        cls, tgt = (s.split("|") + ["", ""])[:2]
        if cls == "LABEL_AS_CALL":
            if called(tgt): out.append(s)
        elif cls == "PASSTHRU_NO_ARGS":
            if called(tgt, empty=True): out.append(s)
        else:
            out.append(s)
    return out

_SITES = None
def audit_sites():
    """{container/func: [site strings]} straight from the baseline."""
    global _SITES
    if _SITES is None:
        d = json.load(open(ROOT / "config/decomp_audit_baseline.json"))
        _SITES = {key: list(v.get("sites", [])) for key, v in d.get("sites", {}).items()}
    return _SITES

def live_audit(row, text):
    """{class: n} of the row's sites still present in `text` (the current clean file)."""
    keys = [f"{row['container']}/{f}" for f in (row.get("defs") or [row["func"]])]
    c = collections.Counter()
    for k in keys:
        for s in live_sites(text, audit_sites().get(k, [])):
            c[s.split("|")[0]] += 1
    return dict(c)

_DW0 = re.compile(r"\bdo\s*\{", re.S)
_LOOP0 = re.compile(r"\bwhile\s*\(\s*0\s*\)\s*\{|\bfor\s*\(\s*;\s*0\s*;\s*\)")   # never a do-while tail


def _dowhile0(text):
    """Brace-matched count of `do { ... } while (0)`, excluding `#define` macro bodies."""
    n = 0
    for m in _DW0.finditer(text):
        line_start = text.rfind("\n", 0, m.start()) + 1
        if text[line_start:m.start()].lstrip().startswith("#define"):
            continue
        depth, i = 0, m.end() - 1
        while i < len(text):
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        if i >= len(text):
            continue
        if re.match(r"\s*while\s*\(\s*0\s*\)", text[i + 1:i + 24]):
            n += 1
    # `while (0) { }` and `for (; 0;) { }` are the SAME zero-byte barrier - byte-identical to the
    # empty do-while in all 18 checks of the 2026-09-11 fence study (docs/PIN_PATTERNS.md section 9).
    # Uncounted, a lane that learned the equivalence could trade a counted fence for an invisible one.
    for m in _LOOP0.finditer(text):
        line_start = text.rfind("\n", 0, m.start()) + 1
        if not text[line_start:m.start()].lstrip().startswith("#define"):
            n += 1
    return n


_DEPINJ = re.compile(r"^[ \t]*(\w+)[ \t]*=[ \t]*\(.*\)[ \t]*\+[ \t]*(\w+)[ \t]*;[ \t]*\n[ \t]*\1[ \t]*-=[ \t]*\2[ \t]*;", re.M)
_LIVETIE = re.compile(r"\b(\w+)[ \t]*\+[ \t]*(\w+)[ \t]*-[ \t]*\2\b")


def _fakedep(text):
    """Fake dependencies in C clothing, counted like pins: t15's `depinject` (`x = (e) + a; x -= a;`)
    and `livetie` (`arg + v - v`).  Both emit nothing and exist only to steer the scheduler or keep
    a value live - scaffolding census could not see, so a sweep could trade a pin for one and look
    like progress (the 2026-09-12 deep pass did, 35 rows, reverted).  Counted over code only
    (comments and strings blanked); dead stores (t15 `deadstore`) are not detectable this way."""
    code = re.sub(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S)
    return len(_DEPINJ.findall(code)) + len(_LIVETIE.findall(code))


def census_one(row, audit):
    p = raw_path(row)
    if not p.exists():
        return {"id": row["id"], "missing": True}
    text = p.read_text(errors="replace")
    body = text
    defs = set(DEF_RE.findall(text))
    # Count what the pin MACHINERY can see, not what the text mentions.  PIN_RE matches any
    # `ASM_x(` including a pin note in a comment and a local wrapper `#define` - so a row the
    # campaign had already freed went on being counted as pinned, and STATUS drifted further
    # from pin_watch/pin_probe/the sweep the more rows were cleared.  `sites_of` is the
    # detector every one of those tools acts on, so counting through it makes them agree by
    # construction.  Verified 2026-09-10 to miss no real site anywhere in src/.
    pins = collections.Counter(s[1][4:] for s in sites_of(text))
    regs = collections.Counter(REG_RE.findall(text))
    labels = [l for l in LABEL_RE.findall(text) if l not in ("default", "case")]
    keys = [f"{row['container']}/{f}" for f in (row.get("defs") or [row["func"]])]
    aud = collections.Counter()
    for k in keys:
        aud.update(audit.get(k, {}))
    cp = ROOT / "src" / row["container"] / Path(row["c_path"]).name
    live = live_audit(row, cp.read_text(errors="replace") if cp.exists() else text)
    rec = {
        "id": row["id"], "lines": text.count("\n"), "chars": len(text),
        "boiler": "This header contains macros emitted by m2c" in text or "typedef float f32;" in text,
        "m2c_field": len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#")))),
        "pins": dict(pins), "pin_total": sum(pins.values()), "pin_regs": dict(regs),
        "gotos": len(re.findall(r"\bgoto\s+[A-Za-z_]", text)), "computed_goto": len(re.findall(r"\bgoto\s*\*", text)),
        "labels": len(labels), "jt_keep": "jt_keep" in text or "&&" in text,
        "m2c_locals": len(set(M2C_LOCAL_RE.findall(text))),
        "local_structs": sorted(set(LOCAL_STRUCT_RE.findall(text)))[:12],
        "n_local_structs": len(set(LOCAL_STRUCT_RE.findall(text))),
        "externs": len(re.findall(r"^extern\b", text, re.M)),
        "calls": sorted(set(CALL_RE.findall(text)) - defs), "data": sorted(set(DATA_RE.findall(text))),
        "nonmatching": "NON_MATCHING" in text,
        "inline_asm": len(re.findall(r"__asm__|\basm\s*\(", text)), "include_asm": "INCLUDE_ASM(" in text,
        "noreturn": text.count("noreturn"), "register_decls": len(re.findall(r"\bregister\b", text)),
        # scaffolding debt (docs/FIDELITY.md): the noreturn tail-call spelling and the maspsx markers
        "tail_idiom": len(re.findall(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)", text)) + len(re.findall(r"\basm\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)|__asm__\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)", text)),
        "markers": sum(pins.get(k, 0) for k in ("TAILSLOT_PIN", "TAILSLOT_PIN_TIED", "PAGEBASE_PIN", "JALDELAY_PIN", "LIVE_SIBCALL_PIN", "SHAPE_D_SIBCALL_PIN", "BRANCH_LABEL_SPLIT")),
        # a `do { one statement } while (0)` is not a loop: it is a zero-byte scheduling barrier
        # (a bare block does NOT reproduce it - only the loop note does), so it is scaffolding in C
        # clothing and is counted like a pin, never silently traded for one.  Two corrections from
        # an audit: the old flat regex missed 15 sites whose body contains nested braces, and it
        # counted 14 legitimate `#define` macro bodies as debt - `do { ... } while (0)` inside a
        # macro is ordinary C hygiene, not scaffolding, so those lines are excluded.
        "dowhile0": _dowhile0(text),
        "fakedep": _fakedep(text),
        "volatile": text.count("volatile"), "switch": len(re.findall(r"\bswitch\s*\(", text)),
        "audit": live, "audit_pin": dict(aud), "ndefs": len(defs),
    }
    return rec

def main():
    audit = audit_index()
    rs = rows()
    recs = [census_one(r, audit) for r in rs]
    write_jsonl(LEDGER / "census.jsonl", recs)
    by = {r["id"]: r for r in rs}
    tot = collections.Counter(); B = collections.Counter()
    for c in recs:
        if c.get("missing"): continue
        sz = by[c["id"]]["size"]
        for k, cond in (("boiler", c["boiler"]), ("m2c_field", c["m2c_field"] > 0), ("pins", c["pin_total"] > 0),
                        ("gotos", c["gotos"] > 0), ("computed_goto", c["computed_goto"] > 0), ("m2c_locals", c["m2c_locals"] > 0),
                        ("local_structs", c["n_local_structs"] > 0), ("nonmatching", c["nonmatching"]), ("inline_asm", c["inline_asm"] > 0), ("dowhile0", c.get("dowhile0", 0) > 0), ("fakedep", c.get("fakedep", 0) > 0),
                        ("audit_blocking", any(k2 in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k2 in c["audit"])),
                        ("audit_any", bool(c["audit"])), ("clean_shape", not c["boiler"] and c["m2c_field"] == 0 and c["pin_total"] == 0 and c["gotos"] == 0 and c["m2c_locals"] == 0)):
            if cond: tot[k] += 1; B[k] += sz
    print(f"{'defect':16} {'files':>6} {'bytes':>9}")
    for k in ("boiler", "m2c_field", "m2c_locals", "pins", "gotos", "computed_goto", "local_structs", "nonmatching", "inline_asm", "dowhile0", "fakedep", "audit_blocking", "audit_any", "clean_shape"):
        print(f"{k:16} {tot[k]:6d} {B[k]:9d}")

if __name__ == "__main__":
    main()
