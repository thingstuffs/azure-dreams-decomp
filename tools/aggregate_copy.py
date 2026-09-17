"""Conservative fixed-record copy recognizer and candidate generator.

This module deliberately recognizes only the copy family demonstrated in pin
research rounds 40--42:

* one 16-byte cursor loop, written as ``do/while`` or the m2c label/goto form;
* either one typed 16-byte assignment or four word loads followed by four stores;
* a source/end pair whose constant difference proves the loop extent; and
* an optional contiguous one-to-three-word tail.

Discovery is not a semantic approval.  In particular, object extent,
non-overlap, effective type and the compiler recipe still require review.  The
generator only emits source files; it never edits ``src/`` or a row recipe.
"""
from __future__ import annotations

from collections import Counter
from dataclasses import dataclass, asdict
import re

from pin_census import arm_labels, sites_of, unscored_text


WORD_TYPES = {"s32", "u32", "int", "unsigned", "long", "unsigned long"}
SCALAR_SIZE = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2,
               "s32": 4, "u32": 4, "int": 4, "unsigned": 4, "long": 4,
               "unsigned long": 4, "void": 1}
MAX_BYTES = 0x200


@dataclass(frozen=True)
class AggregateType:
    name: str
    size: int
    align: int
    array_only: bool
    declared_at: int = 0


@dataclass(frozen=True)
class Pointer:
    base: str
    volatile: bool = False


@dataclass(frozen=True)
class Affine:
    root: str
    offset: int
    stride: int
    path: tuple[str, ...]


@dataclass(frozen=True)
class Match:
    style: str
    start: int
    end: int
    src: str
    dst: str
    limit: str
    loop_bytes: int
    tail_bytes: int
    total_bytes: int
    attached_pins: int
    type_name: str | None
    needs_typedef: bool
    alias_vars: tuple[str, ...]

    def evidence(self):
        d = asdict(self)
        d.update(review_state="unreviewed", review_required=True,
                 required_reviews=["copy extent", "source/destination non-overlap",
                                   "four-byte alignment and effective type",
                                   "callers/object layout", "compiler recipe"])
        return d


@dataclass(frozen=True)
class Candidate:
    label: str
    text: str
    match: Match


@dataclass
class Scan:
    matches: list[Match]
    refusals: Counter


class Refusal(ValueError):
    pass


def _mask(text):
    """Blank comments and literals without moving source offsets."""
    # A backslash-newline is removed before C comments are recognized.  Keep a
    # continued // comment masked across physical lines as the compiler does.
    rx = re.compile(r"/\*.*?\*/|//(?:[^\n\\]|\\(?:\n|.))*|\"(?:[^\"\\\n]|\\.)*\"|'(?:[^'\\\n]|\\.)*'", re.S)
    return rx.sub(lambda m: "".join("\n" if c == "\n" else " " for c in m.group(0)), text)


def _brace(text, opening):
    depth = 0
    for i in range(opening, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    raise Refusal("unbalanced-copy-block")


def _strip_outer(expr):
    expr = expr.strip()
    while expr.startswith("(") and expr.endswith(")"):
        depth = 0
        closes = None
        for i, c in enumerate(expr):
            depth += (c == "(") - (c == ")")
            if depth == 0:
                closes = i
                break
        if closes != len(expr) - 1:
            break
        expr = expr[1:-1].strip()
    return expr


def _number(s):
    try:
        return int(s.rstrip("uUlL"), 0)
    except ValueError:
        return None


def _top_add(expr):
    depth = 0
    for i in range(len(expr) - 1, -1, -1):
        c = expr[i]
        depth += (c == ")") - (c == "(")
        if depth == 0 and c in "+-" and i:
            n = _number(expr[i + 1:].strip())
            if n is not None:
                return expr[:i], n if c == "+" else -n
    return None


def _types(masked):
    """Sizes for simple aggregate types used by the proven copy idioms."""
    out = {}
    head = re.compile(r"\btypedef\s+struct\b[^\{;]*\{")
    for m in head.finditer(masked):
        if masked[:m.start()].count("{") != masked[:m.start()].count("}"):
            continue
        if "packed" in masked[m.start():m.end()]:
            continue
        close = _brace(masked, m.end() - 1)
        am = re.match(r"\s*([A-Za-z_]\w*)\s*;", masked[close + 1:])
        if not am:
            continue
        name = am.group(1)
        fields, offset, align, array_only = [], 0, 1, True
        for raw in masked[m.end():close].split(";"):
            raw = " ".join(raw.split())
            fm = re.fullmatch(r"(?:(?:const)\s+)?([A-Za-z_]\w*(?:\s+long)?)\s+(\**)([A-Za-z_]\w*)\s*(?:\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\])?", raw)
            if not fm:
                if raw:
                    fields = []
                break
            ty, stars, field, count = fm.groups()
            # Pointer-bearing and packed structs may have useful byte sizes, but
            # they are not generic record-copy types.  Their layout needs a
            # semantic type reconstruction, outside this mechanical tool.
            if stars:
                fields = []
                break
            size = SCALAR_SIZE.get(ty)
            if size is None:
                fields = []
                break
            n = int(count, 0) if count else 1
            a = min(size, 4)
            offset = (offset + a - 1) // a * a
            fields.append((field, offset, size, n))
            offset += size * n
            align = max(align, a)
            array_only &= count is not None
        if fields:
            size = (offset + align - 1) // align * align
            out[name] = (AggregateType(name, size, align, array_only and len(fields) == 1, m.start()),
                         {f: (o, s, n) for f, o, s, n in fields})
    return out


PTR_RE = re.compile(
    r"\b(?P<q>(?:(?:register|const|volatile)\s+)*)"
    r"(?P<base>[A-Za-z_]\w*)\s*(?P<q2>(?:(?:const|volatile)\s+)*)"
    r"(?P<stars>\*+)\s*(?P<q3>(?:(?:const|volatile)\s+)*)"
    r"(?P<name>[A-Za-z_]\w*)\b")


def _pointers(masked):
    out = {}
    for m in PTR_RE.finditer(masked):
        quals = (m.group("q") + m.group("q2") + m.group("q3")).split()
        out[m.group("name")] = Pointer(m.group("base"), "volatile" in quals)
    return out


def _pointer_decls(masked):
    return [(m.start(), m.group("name"),
             Pointer(m.group("base"), "volatile" in (m.group("q") + m.group("q2") + m.group("q3")).split()))
            for m in PTR_RE.finditer(masked)]


ASSIGN_RE = re.compile(r"(?<![\w.>*&])(?P<name>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<rhs>[^;\n]+);")
INIT_RE = re.compile(
    r"(?m)^[ \t]*(?:(?:register|const|volatile)\s+)*[A-Za-z_]\w*\s*\*+\s*"
    r"(?P<name>[A-Za-z_]\w*)(?:\s+ASM_REG\([^)]*\))?\s*=\s*(?P<rhs>[^;\n]+);")


def _assignments(masked):
    out = [(m.start("name"), m.group("name"), m.group("rhs").strip()) for m in ASSIGN_RE.finditer(masked)]
    out.extend((m.start("name"), m.group("name"), m.group("rhs").strip()) for m in INIT_RE.finditer(masked))
    return sorted(out)


CAST_RE = re.compile(r"^\(\s*(?:(?:const|volatile)\s+)?([A-Za-z_]\w*)\s*\*+\s*\)\s*(.+)$", re.S)


def _affine(expr, pos, assigns, pointers, types, seen=()):
    expr = _strip_outer(expr)
    add = _top_add(expr)
    if add:
        left, amount = add
        a = _affine(left, pos, assigns, pointers, types, seen)
        return Affine(a.root, a.offset + amount * a.stride, a.stride, a.path)
    cm = CAST_RE.match(expr)
    if cm:
        ty, rest = cm.groups()
        a = _affine(rest, pos, assigns, pointers, types, seen)
        stride = types.get(ty, (AggregateType("", SCALAR_SIZE.get(ty, 1), 1, False), {}))[0].size
        return Affine(a.root, a.offset, stride, a.path)
    if re.fullmatch(r"[A-Za-z_]\w*", expr):
        if expr in seen:
            raise Refusal("cyclic-pointer-alias")
        prior = [(p, rhs) for p, name, rhs in assigns if p < pos and name == expr]
        if prior:
            p, rhs = prior[-1]
            a = _affine(rhs, p, assigns, pointers, types, seen + (expr,))
            base = pointers.get(expr, Pointer("void")).base
            stride = types.get(base, (AggregateType("", SCALAR_SIZE.get(base, 1), 1, False), {}))[0].size
            return Affine(a.root, a.offset, stride, (expr,) + a.path)
        base = pointers.get(expr, Pointer("void")).base
        stride = types.get(base, (AggregateType("", SCALAR_SIZE.get(base, 1), 1, False), {}))[0].size
        return Affine(expr, 0, stride, (expr,))
    if re.fullmatch(r"&?D_[0-9A-Fa-f]{8}", expr):
        return Affine(expr.lstrip("&"), 0, 1, ())
    raise Refusal("unknown-copy-extent")


def _member(expr):
    compact = re.sub(r"\s+", "", expr)
    m = re.fullmatch(r"\(\(([A-Za-z_]\w*)\*\)([A-Za-z_]\w*)\)->([A-Za-z_]\w*)(?:\[(0x[0-9A-Fa-f]+|\d+)\])?", compact)
    if m:
        return m.groups()
    m = re.fullmatch(r"([A-Za-z_]\w*)->([A-Za-z_]\w*)(?:\[(0x[0-9A-Fa-f]+|\d+)\])?", compact)
    if m:
        return None, m.group(1), m.group(2), m.group(3)
    return None


def _word_access(expr, cursor, pointers, types):
    expr = _strip_outer(expr)
    mem = _member(expr)
    if mem:
        cast, var, field, index = mem
        if var != cursor:
            return None
        ty = cast or pointers.get(var, Pointer("")).base
        info = types.get(ty)
        if not info or field not in info[1]:
            raise Refusal("unknown-word-layout")
        off, size, count = info[1][field]
        i = int(index, 0) if index is not None else 0
        if size != 4 or i >= count or (count != 1 and index is None):
            raise Refusal("nonword-copy-field")
        return off + i * size
    compact = re.sub(r"\s+", "", expr)
    m = re.fullmatch(r"\*\((?:const)?(s32|u32|int)\*\)([A-Za-z_]\w*)", compact)
    if m and m.group(2) == cursor:
        return 0
    if compact == "*" + cursor and pointers.get(cursor, Pointer("")).base in WORD_TYPES:
        return 0
    return None


def _aggregate_access(expr, cursor, pointers, types):
    compact = re.sub(r"\s+", "", expr)
    m = re.fullmatch(r"\*\((?:const)?([A-Za-z_]\w*)\*\)([A-Za-z_]\w*)", compact)
    if m and m.group(2) == cursor and m.group(1) in types:
        info = types[m.group(1)][0]
        if info.align < 4:
            raise Refusal("under-aligned-copy-type")
        return info.size
    m = re.fullmatch(r"\*([A-Za-z_]\w*)", compact)
    if m and m.group(1) == cursor:
        ty = pointers.get(cursor, Pointer("")).base
        if ty in types:
            if types[ty][0].align < 4:
                raise Refusal("under-aligned-copy-type")
            return types[ty][0].size
    return None


def _plain_body(body):
    # m2c frequently wraps one cursor increment in a do/while(0).
    body = re.sub(r"\bdo\s*\{\s*([^{};]+;)\s*\}\s*while\s*\(\s*0\s*\)\s*;", r"\1", body)
    return body


def _copy_region(region, src, dst, pointers, types, increments):
    region = _plain_body(region)
    def cursor_stride(var):
        base = pointers.get(var, Pointer("void")).base
        return types.get(base, (AggregateType("", SCALAR_SIZE.get(base, 1), 1, False), {}))[0].size

    if increments:
        copy_eq = [m.start() for m in re.finditer(r"(?<![+!<>=-])=(?!=)", region)]
        last_copy = max(copy_eq) if copy_eq else -1
        for var in (src, dst):
            for m in re.finditer(r"\b" + re.escape(var) + r"\s*(?:\+\+|\+=\s*(?:0x[0-9A-Fa-f]+|\d+))", region):
                a = region.rfind(";", 0, m.start()) + 1
                b = region.find(";", m.end())
                statement = region[a:b if b >= 0 else len(region)]
                embedded = "=" in statement and "+=" not in statement and re.search(
                    r"\*\s*" + re.escape(var) + r"\s*\+\+", statement)
                if not embedded and m.start() < last_copy:
                    raise Refusal("cursor-update-before-copy")
    for m in list(re.finditer(r"\bASM_([A-Z0-9_]+)\s*\(([^;]*)\)\s*;", region)):
        macro, arg = m.group(1), m.group(2).strip()
        if not ((macro in ("SCHED_BARRIER", "MEM_BARRIER") and not arg) or
                (macro in ("KEEP", "KEEP_NV") and arg in (src, dst))):
            raise Refusal("copy-body-side-effect")
    region = re.sub(r"\bASM_[A-Z0-9_]+\s*\([^;]*\)\s*;", "", region)
    inc = Counter()
    for var in (src, dst):
        # Remove a stand-alone cursor increment completely; inside ``*p++`` keep
        # the pointer expression after accounting for its update.
        if re.search(r"\b" + re.escape(var) + r"\s*\+\+", region) and cursor_stride(var) != 16:
            raise Refusal("non-16-byte-cursor-step")
        standalone = re.compile(r"(?m)(^|;)\s*" + re.escape(var) + r"\s*\+\+\s*;")
        n0 = len(standalone.findall(region))
        region = standalone.sub(lambda m: m.group(1), region)
        n = len(re.findall(r"\b" + re.escape(var) + r"\s*\+\+", region))
        inc[var] += n0 + n
        region = re.sub(r"\b" + re.escape(var) + r"\s*\+\+", var, region)
    statements = [s.strip().strip("{} ") for s in region.split(";") if s.strip().strip("{} ")]
    loads, stores, direct, events, declarations = {}, {}, [], [], Counter()
    for stmt in statements:
        im = re.fullmatch(r"([A-Za-z_]\w*)\s*(?:\+\+|\+=\s*(0x[0-9A-Fa-f]+|\d+))", stmt)
        if im and im.group(1) in (src, dst):
            var = im.group(1)
            amount = 1 if "++" in stmt else int(im.group(2), 0)
            if amount * cursor_stride(var) != 16:
                raise Refusal("non-16-byte-cursor-step")
            inc[var] += 1
            continue
        dm = re.fullmatch(
            r"(?:(?:register|const)\s+)*(?:s32|u32|int|unsigned(?:\s+int)?|long(?:\s+int)?)\s+"
            r"([A-Za-z_]\w*)", stmt)
        if dm:
            declarations[dm.group(1)] += 1
            continue
        am = re.fullmatch(r"(.+?)\s*=\s*(.+)", stmt, re.S)
        if not am:
            raise Refusal("copy-body-side-effect")
        lhs, rhs = am.group(1).strip(), am.group(2).strip()
        lw = _aggregate_access(lhs, dst, pointers, types)
        rw = _aggregate_access(rhs, src, pointers, types)
        if lw is not None or rw is not None:
            if lw != rw or lw is None:
                raise Refusal("asymmetric-copy-access")
            direct.append((0, lw))
            events.append(("direct", 0, lw))
            continue
        lo = _word_access(lhs, dst, pointers, types)
        ro = _word_access(rhs, src, pointers, types)
        if ro is not None and re.fullmatch(r"[A-Za-z_]\w*", lhs):
            if lhs in loads:
                raise Refusal("duplicate-copy-event")
            loads[lhs] = ro
            events.append(("load", lhs, ro))
        elif lo is not None and re.fullmatch(r"[A-Za-z_]\w*", rhs):
            if rhs in stores:
                raise Refusal("duplicate-copy-event")
            stores[rhs] = lo
            events.append(("store", rhs, lo))
        elif lo is not None and ro is not None:
            if lo != ro:
                raise Refusal("asymmetric-copy-access")
            direct.append((lo, 4))
            events.append(("direct", lo, 4))
        else:
            raise Refusal("copy-body-side-effect")
    if increments and (inc[src] != 1 or inc[dst] != 1):
        raise Refusal("ambiguous-cursor-update")
    if not increments and sum(inc.values()):
        raise Refusal("tail-updates-cursor")
    if increments:
        if direct:
            if events != [("direct", 0, 16)]:
                raise Refusal("mixed-copy-forms")
        else:
            if (len(events) != 8 or [e[0] for e in events] != ["load"] * 4 + ["store"] * 4
                    or len(loads) != 4 or len(stores) != 4):
                raise Refusal("copy-events-not-load-then-store")
    if loads and (set(declarations) != set(loads) or
                  any(declarations[name] != 1 for name in loads)):
        # Deleting the loop also deletes its scratch assignments.  Only scratch
        # objects whose complete lifetime is inside this region are supported;
        # outer locals and globals can otherwise make those writes observable.
        raise Refusal("nonlocal-copy-scratch")
    if loads != stores:
        raise Refusal("unpaired-copy-word")
    ranges = direct + [(off, 4) for off in loads.values()]
    if not ranges:
        raise Refusal("unpaired-copy-word")
    ranges.sort()
    if len({(off, size) for off, size in ranges}) != len(ranges):
        raise Refusal("duplicate-copy-event")
    at = 0
    for off, size in ranges:
        if off != at or size <= 0:
            raise Refusal("noncontiguous-copy-words")
        at += size
    if at % 4:
        raise Refusal("noncontiguous-copy-words")
    return at, set(loads)


def _tail(masked, pos, src, dst, pointers, types):
    start = pos
    while start < len(masked) and masked[start].isspace():
        start += 1
    # A one-statement do/while(0) tail (the landed 84-byte control family).
    dm = re.match(r"do\s*\{", masked[start:])
    if dm:
        op = start + dm.end() - 1
        close = _brace(masked, op)
        cm = re.match(r"\s*while\s*\(\s*0\s*\)\s*;", masked[close + 1:])
        if cm:
            end = close + 1 + cm.end()
            try:
                n, temps = _copy_region(masked[op + 1:close], src, dst, pointers, types, False)
                if n in (4, 8, 12):
                    return n, end, temps
            except Refusal:
                pass
    best = (0, pos, set())
    semis = [m.end() for m in re.finditer(r";", masked[start:start + 1600])][:8]
    for rel in semis:
        end = start + rel
        try:
            n, temps = _copy_region(masked[start:end], src, dst, pointers, types, False)
            if n in (4, 8, 12):
                best = (n, end, temps)
        except Refusal:
            continue
    return best


def _line_tail(text, pos):
    nl = text.find("\n", pos)
    if nl < 0:
        return pos
    rest = text[pos:nl]
    return nl + 1 if not re.sub(r"/\*.*?\*/", "", rest).strip() else pos


def _attached_barrier(masked, text, pos):
    m = re.match(r"\s*ASM_(?:MEM|SCHED)_BARRIER\s*\(\s*\)\s*;", masked[pos:])
    if not m:
        return pos
    return _line_tail(text, pos + m.end())


def _aggregate_type(types, total, before, text):
    labs = arm_labels(text)
    choices = []
    for v in types.values():
        t = v[0]
        line = text.count("\n", 0, t.declared_at)
        if (t.declared_at < before and t.size == total and t.align >= 4 and t.array_only
                and (line >= len(labs) or labs[line] == "both")):
            choices.append(t)
    return sorted(choices, key=lambda t: (not re.search(r"Record|Payload|Copy", t.name), t.name))[0] if choices else None


def _loops(masked):
    for m in re.finditer(r"\bdo\s*\{", masked):
        op = m.end() - 1
        close = _brace(masked, op)
        cm = re.match(r"\s*while\s*\(\s*([A-Za-z_]\w*)\s*!=\s*([A-Za-z_]\w*)\s*\)\s*;", masked[close + 1:])
        if cm:
            yield "do", m.start(), close + 1 + cm.end(), op + 1, close, cm.group(1), cm.group(2)
    for m in re.finditer(r"(?m)^[ \t]*([A-Za-z_]\w*):\s*\{", masked):
        label, op = m.group(1), m.end() - 1
        close = _brace(masked, op)
        cm = re.match(r"\s*if\s*\(\s*([A-Za-z_]\w*)\s*!=\s*([A-Za-z_]\w*)\s*\)\s*goto\s+" + re.escape(label) + r"\s*;", masked[close + 1:])
        if cm:
            if len(re.findall(r"\b" + re.escape(label) + r"\b", masked)) != 2:
                continue
            yield "goto", m.start(), close + 1 + cm.end(), op + 1, close, cm.group(1), cm.group(2)


def _function_bounds(masked, pos):
    """Bounds of the top-level function body containing ``pos``."""
    depth, opening = 0, None
    for i, c in enumerate(masked):
        if c == "{":
            if depth == 0:
                opening = i
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and opening is not None:
                if opening < pos < i:
                    prefix = masked[max(0, opening - 500):opening]
                    if not re.search(r"\b[A-Za-z_]\w*\s*\([^;{}]*\)\s*$", prefix):
                        raise Refusal("copy-outside-function")
                    return opening, i
                opening = None
    raise Refusal("copy-outside-function")


def _parameter_bounds(masked, opening):
    """Bounds of the simple parameter list immediately before a function body."""
    close = masked.rfind(")", 0, opening)
    if close < 0 or masked[close + 1:opening].strip():
        raise Refusal("copy-outside-function")
    depth = 0
    for i in range(close, -1, -1):
        if masked[i] == ")":
            depth += 1
        elif masked[i] == "(":
            depth -= 1
            if depth == 0:
                return i, close
    raise Refusal("copy-outside-function")


def _macro_line(text, pos):
    line = text.count("\n", 0, pos)
    lines = text.splitlines()
    i = line
    while i > 0 and lines[i - 1].rstrip().endswith("\\"):
        i -= 1
    return i < len(lines) and lines[i].lstrip().startswith("#")


def _control_stack(masked, pos, start):
    stack, controls = [], []
    for m in re.finditer(r"[{}]", masked[start:pos]):
        at = start + m.start()
        if m.group() == "{":
            prefix = masked[max(start, at - 300):at]
            controlled = bool(re.search(r"(?:\b(?:if|for|while|switch)\s*\([^;{}]*\)|\belse)\s*$", prefix))
            stack.append((at, controlled))
        elif stack:
            stack.pop()
    controls = [at for at, controlled in stack if controlled]
    return tuple(controls)


def _line_guarded(masked, pos):
    line_start = masked.rfind("\n", 0, pos) + 1
    before = masked[line_start:pos].strip()
    if before:
        # A pointer declaration initializer starts after its type/declarator;
        # any other same-line prefix (notably ``if (...) {``) is conditional.
        if re.fullmatch(r"(?:(?:register|const|volatile)\s+)*[A-Za-z_]\w*\s*\*+", before):
            return False
        return True
    prev_end = line_start - 1
    prev_start = masked.rfind("\n", 0, max(prev_end, 0)) + 1
    return bool(re.search(r"\b(?:if|for|while|switch)\s*\([^;{}]*\)\s*$",
                          masked[prev_start:prev_end].strip()))


def _overwritten_before_use(masked, pos, name):
    """A copy scratch may survive the region only if its next mention overwrites it."""
    m = re.search(r"\b" + re.escape(name) + r"\b", masked[pos:])
    if not m:
        return True
    at = pos + m.start()
    line = masked[masked.rfind("\n", 0, at) + 1:masked.find("\n", at) if "\n" in masked[at:] else len(masked)]
    am = re.match(r"\s*" + re.escape(name) + r"\s*=\s*(.*?);", line)
    return bool(am and not re.search(r"\b" + re.escape(name) + r"\b", am.group(1)))


def _check_definitions(masked, local_assigns, names, before, f0, loop_controls):
    """Require every inferred pointer alias definition to dominate the copy."""
    for name in names:
        defs = [a for a in local_assigns if a[1] == name and a[0] < before]
        if len(defs) > 1:
            raise Refusal("ambiguous-copy-definition")
        if any(_line_guarded(masked, d[0]) or
               not set(_control_stack(masked, d[0], f0)).issubset(loop_controls)
               for d in defs):
            raise Refusal("conditional-copy-definition")


def analyze(text):
    masked, refusals = _mask(text), Counter()
    types, pointers, assigns = _types(masked), _pointers(masked), _assignments(masked)
    pointer_decls = _pointer_decls(masked)
    provisional = []
    raw_loops = list(_loops(masked))
    repeated_sources = Counter(x[5] for x in raw_loops)
    for style, start, loop_end, b0, b1, src, limit in raw_loops:
        try:
            if _macro_line(text, start):
                raise Refusal("preprocessor-copy-body")
            f0, f1 = _function_bounds(masked, start)
            p0, p1 = _parameter_bounds(masked, f0)
            local_assigns = [a for a in assigns if f0 < a[0] < f1]
            loop_controls = set(_control_stack(masked, start, f0))
            prefix = masked[f0 + 1:start]
            if re.search(r"\bgoto\s+[A-Za-z_]\w*\s*;|^[ \t]*[A-Za-z_]\w*\s*:", prefix, re.M):
                raise Refusal("nonlocal-control-before-copy")
            _check_definitions(masked, local_assigns, (src, limit), start, f0, loop_controls)
            if repeated_sources[src] > 1:
                raise Refusal("parallel-copy-arms")
            src_decls = [d for d in pointer_decls
                         if ((f0 < d[0] < start) or (p0 < d[0] < p1)) and d[1] == src]
            if len(src_decls) != 1:
                raise Refusal("shadowed-copy-cursor")
            body = masked[b0:b1]
            # The destination is the other incremented pointer in this deliberately narrow family.
            names = [n for n in pointers if re.search(r"\b" + re.escape(n) + r"\s*(?:\+\+|\+=)", body)]
            dsts = [n for n in names if n != src]
            if len(dsts) != 1:
                raise Refusal("ambiguous-copy-destination")
            dst = dsts[0]
            dst_decls = [d for d in pointer_decls
                         if ((f0 < d[0] < start) or (p0 < d[0] < p1)) and d[1] == dst]
            if len(dst_decls) != 1:
                raise Refusal("shadowed-copy-cursor")
            local_pointers = dict(pointers)
            for _, name, pointer in sorted(
                    d for d in pointer_decls
                    if (f0 < d[0] < start) or (p0 < d[0] < p1)):
                local_pointers[name] = pointer
            if (local_pointers.get(src, Pointer("")).volatile or
                    local_pointers.get(dst, Pointer("")).volatile or
                    local_pointers.get(limit, Pointer("")).volatile or re.search(r"\bvolatile\b", body)):
                raise Refusal("volatile-copy")
            fn_text = masked[f0:f1]
            if re.search(r"&\s*(?:" + re.escape(src) + "|" + re.escape(dst) + r")\b", fn_text):
                raise Refusal("cursor-address-escapes")
            macro_capture = (r"(?m)^[ \t]*#[ \t]*define[^\n]*(?:\\\n[^\n]*)*\b(?:" +
                             re.escape(src) + "|" + re.escape(dst) + r")\b")
            if re.search(macro_capture, masked):
                raise Refusal("cursor-captured-by-macro")
            loop_width, loop_temps = _copy_region(body, src, dst, local_pointers, types, True)
            if loop_width != 16:
                raise Refusal("non-16-byte-copy-loop")
            sa = _affine(src, start, local_assigns, local_pointers, types)
            ea = _affine(limit, start, local_assigns, local_pointers, types)
            _check_definitions(masked, local_assigns, sa.path + ea.path,
                               start, f0, loop_controls)
            if sa.root != ea.root:
                raise Refusal("copy-end-different-root")
            loop_bytes = ea.offset - sa.offset
            if loop_bytes <= 0 or loop_bytes % 16 or loop_bytes > MAX_BYTES:
                raise Refusal("unknown-copy-extent")
            tail_bytes, end, tail_temps = _tail(masked, loop_end, src, dst, local_pointers, types)
            end = _attached_barrier(masked, text, end)
            total = loop_bytes + tail_bytes
            if total > MAX_BYTES or total % 4:
                raise Refusal("unsupported-copy-size")
            labs = arm_labels(text)
            l0, l1 = text.count("\n", 0, start), text.count("\n", 0, end)
            if any(x in ("port", "dead") for x in labs[l0:l1 + 1]):
                raise Refusal("unscored-copy-arm")
            # Cursor values cannot silently become the post-loop values elsewhere.
            rest = masked[end:f1]
            if re.search(r"\b(?:" + re.escape(src) + "|" + re.escape(dst) + r")\b", rest):
                raise Refusal("residual-cursor-use")
            if any(not _overwritten_before_use(masked, end, v) for v in loop_temps | tail_temps):
                raise Refusal("uncertain-residual-copy-value")
            agg = _aggregate_type(types, total, start, text)
            try:
                da = _affine(dst, start, local_assigns, local_pointers, types)
                dpath = da.path
            except Refusal:
                # Destination identity is a semantic-review fact; unlike the
                # source/end relation it is not used to infer copy extent.
                dpath = (dst,)
                da = None
            if da and da.root == sa.root:
                slo, shi = sa.offset, sa.offset + total
                dlo, dhi = da.offset, da.offset + total
                if max(slo, dlo) < min(shi, dhi):
                    raise Refusal("overlapping-copy-range")
            aliases = tuple(sorted(set(sa.path + dpath)))
            attached = sum(start <= s[3] < end for s in sites_of(text))
            provisional.append(Match(style, start, end, src, dst, limit, loop_bytes, tail_bytes,
                                     total, attached, agg.name if agg else None, agg is None, aliases))
        except Refusal as e:
            refusals[str(e)] += 1
    return Scan(provisional, refusals)


def _insert_typedef(text, name, size):
    words = size // 4
    typedef = "\ntypedef struct {\n    u32 words[%d];\n} %s;\n" % (words, name)
    masked = _mask(text)
    includes, pp_depth, brace_depth, pos = [], 0, 0, 0
    for raw, blank in zip(text.splitlines(True), masked.splitlines(True)):
        stripped = blank.lstrip()
        if stripped.startswith(("#if ", "#ifdef", "#ifndef")):
            pp_depth += 1
        elif stripped.startswith("#endif"):
            pp_depth = max(0, pp_depth - 1)
        elif pp_depth == 0 and brace_depth == 0 and stripped.startswith("#include"):
            includes.append(pos + len(raw))
        brace_depth += blank.count("{") - blank.count("}")
        pos += len(raw)
    at = includes[-1] if includes else 0
    return text[:at] + typedef + text[at:]


def _candidate_for(text, match):
    ty = match.type_name
    if ty is None:
        base = "CopyRecord%d" % match.total_bytes
        ty, i = base, 2
        while re.search(r"\b" + re.escape(ty) + r"\b", text):
            ty, i = base + "_%d" % i, i + 1
    indent = re.match(r"[ \t]*", text[text.rfind("\n", 0, match.start) + 1:match.start]).group(0)
    stmt = "%s*(%s *)%s = *(%s *)%s;\n" % (indent, ty, match.dst, ty, match.src)
    out = text[:match.start] + stmt + text[match.end:]
    if match.needs_typedef:
        out = _insert_typedef(out, ty, match.total_bytes)
    if unscored_text(out) != unscored_text(text):
        raise Refusal("unscored-copy-arm")
    return out


def candidates(text):
    out, seen = [], set()
    for match in analyze(text).matches:
        candidate = _candidate_for(text, match)
        if candidate in seen:
            continue
        seen.add(candidate)
        out.append(Candidate("aggregate:%d:%s" % (match.total_bytes, match.style), candidate, match))
    return out
