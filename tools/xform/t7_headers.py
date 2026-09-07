"""T7: a function's local address-named struct becomes the shared record type from include/records/.

For every `typedef struct S_<fn>_<n> {...} S_<fn>_<n>;   /* base in fn */` that T4 emitted and the
struct census assigned to a record class with a generated header (ledger/records.json), the
typedef is dropped, `#include "records/<Rec>.h"` is added, every `S_<fn>_<n>` becomes `<Rec>`, and
each member access whose type sits in a union view in the shared layout is rewritten to that view
(`->unk_04` -> `->unk_04.as_s8`, `->unk_00` -> `->unk_00.at00_s32.v`) so the function reads the offset with exactly the type it did before.
The bytes therefore cannot move; the row is still verified (per-row scorer, then the window gate
through the sweep's normal path), all structs of the file at once and, on a mismatch, one at a
time (the exact subset is kept).

Refusals (journalled): an access to a rewritten member whose base cannot be attributed to one
struct (neither `((S *)expr)->` nor an identifier declared `S *ident`), `sizeof(S)` (the shared
span differs), a struct the census left unmapped (in-row union, unknown width), a `_pre` record.
"""
import hashlib, json, re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
_REC = None
def records():
    global _REC
    if _REC is None:
        _REC = json.load(open(ROOT / "ledger/records.json"))
    return _REC

def sname_index():
    """(row id, struct name) -> (record name, record)."""
    idx = {}
    for name, rec in records().items():
        for key in rec["paths"]:
            row, _, sname = key.partition("|")
            idx[(row, sname)] = (name, rec)
    return idx

TYPEDEF = re.compile(r"[ \t]*typedef struct (S_[0-9A-F]+_\d+) \{\n(.*?)\n\} \1;[ \t]*/\* (.*?) \*/[ \t]*\n?", re.S)
MEMBER = re.compile(r"^\s+(.+?)\s+(?:\(\*)?unk_([0-9A-F]+)(?:\))?(?:\([^)]*\))?;", re.M)
INCLUDE = re.compile(r"^[ \t]*#include[ \t]+\"[^\"]+\"[ \t]*\n", re.M)

def local_members(body):
    out = {}
    for m in MEMBER.finditer(body):
        if m.group(1).strip().startswith("u8 pad"):
            continue
        out[int(m.group(2), 16)] = m.group(1).strip()
    return out

def base_before(text, i):
    """The base expression that ends at text[i] (just before '->'): ('cast', struct) for `((S *)expr)`,
    ('ident', name) for an identifier, else (None, None)."""
    j = i
    while j > 0 and text[j - 1] in " \t":
        j -= 1
    if j > 0 and text[j - 1] == ")":
        depth = 0; k = j - 1
        while k >= 0:
            if text[k] == ")": depth += 1
            elif text[k] == "(":
                depth -= 1
                if depth == 0: break
            k -= 1
        if k < 0:
            return None, None
        inner = text[k + 1:j - 1].strip()
        m = re.match(r"\(\s*(S_[0-9A-F]+_\d+|[A-Za-z_][A-Za-z0-9_]*)\s*\*\s*\)", inner)
        if m:
            return "cast", m.group(1)
        return None, None
    m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)$", text[:j])
    if m:
        return "ident", m.group(1)
    return None, None

def rewrite_struct(text, sname, cls, paths, body, needs_compat=False):
    """Rename one struct to its record type and route its non-identity members through the union views.
    Returns (new_text, sites) or raises ValueError with the refusal reason."""
    local = local_members(body)
    nonid = {}
    for off, ty in local.items():
        p = paths.get(f"0x{off:X}")
        if p is None:
            raise ValueError(f"member unk_{off:02X} not in the record mapping")
        if p != f"unk_{off:02X}":
            nonid[f"unk_{off:02X}"] = p
    if re.search(r"\bsizeof\s*\(\s*" + re.escape(sname) + r"\b", text):
        raise ValueError("sizeof(struct): the shared span differs")
    if needs_compat:
        # a hand-trimmed prelude (T1 saw no full boilerplate block) may still carry typedefs the compat
        # header defines identically: drop those lines (byte-neutral); any other definition of those
        # names is a clash we refuse.  Identical macro redefinitions are benign in C and stay.
        dup = re.compile(r"^[ \t]*typedef[ \t]+(?:s32[ \t]+M2C_UNK|s8[ \t]+M2C_UNK8|s16[ \t]+M2C_UNK16|s32[ \t]+M2C_UNK32|s64[ \t]+M2C_UNK64|float[ \t]+f32|double[ \t]+f64|long[ \t]+long[ \t]+s64|unsigned[ \t]+long[ \t]+long[ \t]+u64)[ \t]*;[ \t]*\n", re.M)
        text = dup.sub("", text)
        if re.search(r"^[ \t]*typedef\b[^\n]*\b(M2C_UNK\d*|f32|f64|s64|u64)[ \t]*;", text, re.M):
            raise ValueError("inline typedef of a compat-header name with a different definition")
    idents = set(re.findall(r"\b" + re.escape(sname) + r"\s*\*+\s*([A-Za-z_][A-Za-z0-9_]*)\s*[,;)=\[]", text))
    sites = 0
    if nonid:
        out = []; pos = 0
        for m in re.finditer(r"->\s*(unk_[0-9A-F]+)\b(?!\s*\.)", text):
            mem = m.group(1)
            if mem not in nonid:
                continue
            kind, who = base_before(text, m.start())
            mine = (kind == "cast" and who == sname) or (kind == "ident" and who in idents)
            if not mine:
                # another struct's member of the same name, or an access we cannot attribute
                if kind == "cast" and who != sname:
                    continue
                if kind == "ident" and who not in idents and not re.search(r"\b" + re.escape(who) + r"\b", body):
                    # an identifier of some other declared type: leave it, unless it is undeclared and ambiguous
                    other_types = re.findall(r"\b(S_[0-9A-F]+_\d+|Rec_[A-Za-z0-9_]+)\s*\*+\s*" + re.escape(who) + r"\b", text)
                    if other_types and sname not in other_types:
                        continue
                raise ValueError(f"cannot attribute ->{mem} at offset {m.start()} to one struct")
            out.append(text[pos:m.start()]); out.append("->" + nonid[mem]); pos = m.end(); sites += 1
        out.append(text[pos:]); text = "".join(out)
    text = re.sub(r"\b" + re.escape(sname) + r"\b", cls, text)
    return text, sites

def add_include(text, header):
    line = f'#include "{header}"\n'
    if line in text:
        return text
    last = None
    for m in INCLUDE.finditer(text):
        last = m
    if last:
        return text[:last.end()] + line + text[last.end():]
    return line + text

class T:
    name = "t7_headers"; level = 4
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        idx = sname_index()
        if not any((row["id"], m.group(1)) in idx for m in TYPEDEF.finditer(text)):
            return "no struct of a shared record class"
        return None

    @staticmethod
    def plan(text, row):
        """[(sname, cls, header, sha, paths, body, whole_typedef_span)] for every convertible struct."""
        idx = sname_index(); out = []
        for m in TYPEDEF.finditer(text):
            sname = m.group(1)
            if (row["id"], sname) not in idx:
                continue
            name, rec = idx[(row["id"], sname)]
            if not rec.get("compiles", True):
                continue
            out.append((sname, name, rec["header"], rec["sha256"], rec["paths"][row["id"] + "|" + sname], m.group(2), (m.start(), m.end()), rec.get("needs_compat", False)))
        return out

    @staticmethod
    def apply_subset(text, items):
        cur = text; sites = 0; headers = {}
        # drop typedefs from the end so spans stay valid
        for sname, cls, header, sha, paths, body, (s, e), _nc in sorted(items, key=lambda it: -it[6][0]):
            cur = cur[:s] + cur[e:]
        for sname, cls, header, sha, paths, body, _, needs_compat in items:
            cur, n = rewrite_struct(cur, sname, cls, paths, body, needs_compat); sites += n
            headers[cls] = sha
            cur = add_include(cur, header)
        return cur, sites, headers

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        items = T.plan(text, row)
        if not items:
            return None, {}
        refused = []
        try:
            cand, sites, headers = T.apply_subset(text, items)
            v = verify_fn(cand)
            if v.get("exact"):
                return cand, {"records": sorted(headers), "header_sha": headers, "sites": sites, "structs": len(items)}
        except ValueError as e:
            refused.append(str(e))
        # one struct at a time; keep the exact subset
        kept = []; cur = text; sites = 0; headers = {}
        for it in items:
            try:
                cand, n, h = T.apply_subset(text, kept + [it])
            except ValueError as e:
                refused.append(f"{it[0]}: {e}"); continue
            v = verify_fn(cand)
            if v.get("exact"):
                kept.append(it); cur, sites, headers = cand, n, h
            else:
                refused.append(f"{it[0]}: not exact ({v.get('class')}, {v.get('total')})")
        if not kept:
            return None, {"refused": refused[:6]}
        return cur, {"records": sorted(headers), "header_sha": headers, "sites": sites, "structs": len(kept), "refused": refused[:6]}

    @staticmethod
    def apply(text, row, census):
        items = T.plan(text, row)
        if not items:
            return None
        cand, _, _ = T.apply_subset(text, items)
        return cand
