"""T12: the pin-free statement order.

`tools/pin_probe.py --strip` erases every pin of a row at once and records what is left.  For a
large share of the rows that land within a few words of retail, the residue is one instruction
*moved*: the aligned view shows a single `insert X` paired with a single `delete X` and nothing
else.  That is not a compiler wall - it is one C statement sitting in the wrong slot, and the
statement order is the source's to choose.  This plugin searches for the slot.

Method: strip every pin, then walk the function's *simple* statements (one line, no braces, no
control keyword, not a label) and try each one moved 1..K slots earlier or later among its
immediate siblings at the same brace depth.  First byte-exact candidate wins; the row lands
pin-free.  Nothing else is attempted - a row this engine misses is an exemplar for a lane, not a
row to grind.

Why a reordering may be searched freely: **the verdict is byte equality against retail.**  A
candidate that reordered two statements whose order matters cannot compile to retail's bytes, so
a semantic change cannot survive the gate.  The dependency guard below only saves probes; it is
not what makes the result correct.

Eligibility comes from `ledger/pins_strip.jsonl` (the fresh measurement of *this* text), never
from `ledger/pins.jsonl` (the frozen pinned text).  A row whose strip damage is above BAND, or
whose recorded input sha is stale, is refused with the reason named.
"""
import json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of, erase

BAND = 8            # strip damage a row must already be within
MAX_SHIFT = 3       # how far a statement may travel
BUDGET = 60         # verify runs per row
CLASSES = {"reorder-only", "reg-rename", "li-expansion", "const-remat", "broad",
           "code-motion", "block-order", "addressing", "length-drift", "delay-slot"}

NOTE_RE = re.compile(r"[ \t]*/\*\s*(MATCH pin:|UNRESOLVED C shape \(pin\)).*?\*/", re.S)
IDENT_RE = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")
KEYWORDS = {"if", "else", "for", "while", "do", "switch", "case", "default", "return", "goto",
            "break", "continue", "sizeof", "struct", "union", "enum", "typedef", "static",
            "const", "volatile", "register", "unsigned", "signed", "void", "char", "short",
            "int", "long", "float", "double"}
TYPEWORDS = {"u8", "s8", "u16", "s16", "u32", "s32", "f32", "void", "char", "short", "int",
             "long", "float", "double", "unsigned", "signed", "register", "const", "volatile",
             "static", "struct", "union", "enum"}

_STRIP = None


def strip_census():
    """row id -> the strip probe's record for that row."""
    global _STRIP
    if _STRIP is None:
        _STRIP = {}
        p = ROOT / "ledger/pins_strip.jsonl"
        if p.exists():
            for line in p.read_text().splitlines():
                if line.strip():
                    r = json.loads(line)
                    _STRIP[r["id"]] = r
    return _STRIP


def strip_pins(text):
    """Every ASM_* site erased, and the pin notes that described them with it."""
    cur = text
    for s in sorted(sites_of(text), key=lambda s: s[3], reverse=True):
        cur = erase(cur, s)
    out = []
    for ln in cur.splitlines(True):
        nl = "\n" if ln.endswith("\n") else ""
        body = NOTE_RE.sub("", ln[:len(ln) - len(nl)])
        if not body.strip() and ("MATCH pin:" in ln or "UNRESOLVED C shape (pin)" in ln):
            continue                      # the note's whole line went with its pin
        out.append(body.rstrip() + nl if body != ln[:len(ln) - len(nl)] else ln)
    return "".join(out)


def mask(text):
    """Same-length copy with comment and string bodies blanked (safe to scan)."""
    out, i, n = list(text), 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text[i + 1:i + 2] == "*":
            j = text.find("*/", i + 2); j = n if j < 0 else j + 2
        elif c == "/" and text[i + 1:i + 2] == "/":
            j = text.find("\n", i); j = n if j < 0 else j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
        else:
            i += 1
            continue
        for k in range(i, j):
            if out[k] != "\n":
                out[k] = " "
        i = j
    return "".join(out)


def depths(lines_masked):
    """Brace depth *before* each line."""
    d, out = 0, []
    for ln in lines_masked:
        out.append(d)
        d += ln.count("{") - ln.count("}")
    return out


def movable(line_masked):
    """A one-line simple statement that may be re-slotted."""
    s = line_masked.strip()
    if not s or s.startswith("#") or "{" in s or "}" in s:
        return False
    if not s.endswith(";"):
        return False
    if re.match(r"^[A-Za-z_][A-Za-z0-9_]*\s*:", s):        # a label
        return False
    head = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)", s)
    if head and head.group(1) in ("return", "goto", "break", "continue", "else", "do", "case",
                                  "default", "if", "while", "for", "switch", "typedef", "extern"):
        return False
    return True


def is_decl(line_masked):
    s = line_masked.strip()
    w = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)", s)
    return bool(w and w.group(1) in TYPEWORDS)


def rw(line):
    """(writes, reads) identifier sets - a pruning heuristic, not a correctness argument."""
    body = line.strip().rstrip(";")
    m = re.match(r"^(.*?)(?<![=!<>+\-*/%&|^])=(?!=)(.*)$", body)
    if m:
        lhs, rhs = m.group(1), m.group(2)
        w = {i for i in IDENT_RE.findall(lhs) if i not in KEYWORDS}
        r = {i for i in IDENT_RE.findall(rhs) if i not in KEYWORDS}
        r |= {i for i in IDENT_RE.findall(lhs) if i not in KEYWORDS and lhs.strip() != i}
        return w, r
    ids = {i for i in IDENT_RE.findall(body) if i not in KEYWORDS}
    return ids, ids                                        # a call: assume it touches its operands


def independent(a, b):
    wa, ra = rw(a)
    wb, rb = rw(b)
    return not (wa & (wb | rb) or wb & ra)


class T:
    name = "t12_stmtorder"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no live pin site"
        if "NON_MATCHING" in text:
            return "NON_MATCHING arm"
        if re.search(r"__asm__\s*(__volatile__\s*)?\(\s*\"[a-z]", text):
            return "inline asm body"
        rec = strip_census().get(row["id"])
        if rec is None:
            return "no strip probe for this row"
        if rec.get("in_sha") != sha_text(text):
            return "strip probe is stale for this text"
        if rec.get("exact"):
            return "strip probe says pin-free already (rerun t2)"
        t = rec.get("total")
        if t is None or t > BAND:
            return f"strip damage {t} above band {BAND}"
        if rec.get("class") not in CLASSES:
            return f"residue class {rec.get('class')} outside the menu"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        base = strip_pins(text)
        lines = base.splitlines(True)
        masked = mask(base).splitlines(True)
        dep = depths(masked)
        n = len(lines)
        tried = 0
        info = {"pins_in": len(sites_of(text)), "base_lines": n}

        v = verify_fn(base)
        tried += 1
        if v.get("exact"):
            return base, dict(info, step="strip", tried=tried, pins_out=0)
        info["strip_total"] = v.get("total")

        # candidate moves, cheapest first: every movable line shifted k slots among the siblings
        # at its own brace depth, with no non-movable line crossed.
        cands = []
        for k in range(1, MAX_SHIFT + 1):
            for i in range(n):
                if not movable(masked[i]):
                    continue
                for direction in (-1, 1):
                    j = i + direction * k
                    if not (0 <= j < n):
                        continue
                    span = range(min(i, j), max(i, j) + 1)
                    if any(dep[x] != dep[i] or not movable(masked[x]) for x in span):
                        continue
                    if is_decl(masked[i]) != is_decl(masked[j]):
                        continue           # a declaration stays among declarations
                    if not all(independent(lines[i], lines[x]) for x in span if x != i):
                        continue
                    cands.append((i, j))
        seen = set()
        for i, j in cands:
            if tried >= BUDGET:
                info["stopped"] = "budget"
                break
            out = lines[:]
            ln = out.pop(i)
            out.insert(j, ln)
            cand = "".join(out)
            h = sha_text(cand)
            if h in seen or cand == base:
                continue
            seen.add(h)
            v = verify_fn(cand)
            tried += 1
            if v.get("exact"):
                return cand, dict(info, step=f"move line {i}->{j}", tried=tried, pins_out=0,
                                  moved=lines[i].strip()[:60])
        return None, dict(info, tried=tried, cands=len(cands), pins_out=info["pins_in"])
