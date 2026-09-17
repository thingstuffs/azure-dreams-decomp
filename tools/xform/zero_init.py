"""Replace a guarded hardware-zero binding with an ordinary initialized local.

The only source rewrite is::

    register s32 name ASM_REG("$0");

to::

    s32 name = 0;

(``$zero`` is accepted too).  All admitted sites in one source are changed in
one candidate.  Admission is intentionally conservative: the declaration must
be a live, direct local declaration without an initializer, and its scope may
contain only reads and exact ``name = 0;`` writes.  Address escape, nonzero or
unknown assignment, increment/compound assignment, ambiguous shadowing, macro
definitions, macro calls touching the value, and raw/ASM output uses refuse the
site.  Comments and string/character literals are masked during analysis.

This is separate from generic pin erasure: removing the binding without adding
the initializer leaves an uninitialized C local and tests a different source.
"""
from __future__ import annotations

from bisect import bisect_right
from dataclasses import dataclass
import re
from typing import Sequence

from pin_census import arm_labels, sites_of


TARGET_RE = re.compile(
    r'(?<![A-Za-z0-9_])(?P<indent>[ \t]*)register[ \t]+s32[ \t]+'
    r'(?P<name>[A-Za-z_]\w*)[ \t]+ASM_REG\([ \t]*"\$(?:0|zero)"[ \t]*\)'
    r'[ \t]*;')
FUNCTION_RE = re.compile(
    r'^[A-Za-z_][\w \t\*]*?\b(?P<name>[A-Za-z_]\w*)'
    r'\s*\([^;{}()]*\)\s*\{', re.M)
CONTROL_WORDS = {"if", "while", "for", "switch"}
CALL_KEYWORDS = CONTROL_WORDS | {"sizeof", "_Alignof", "typeof", "__typeof__"}
NON_DECLARATION_PREFIXES = {
    "return", "goto", "case", "sizeof", "if", "while", "for", "switch",
    "do", "else", "break", "continue",
}


@dataclass(frozen=True)
class Site:
    name: str
    start: int
    end: int
    line: int
    scope_start: int
    scope_end: int


def _mask(text: str, strings: bool = True) -> str:
    """Mask comments and, by default, literals while preserving offsets/newlines."""
    out = list(text)
    i, state = 0, "code"
    quote = ""
    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ""
        if state == "code":
            if ch == "/" and nxt == "*":
                out[i] = out[i + 1] = " "
                i += 2
                state = "block"
                continue
            if ch == "/" and nxt == "/":
                out[i] = out[i + 1] = " "
                i += 2
                state = "line"
                continue
            if ch in ('"', "'"):
                quote = ch
                if strings:
                    out[i] = " "
                i += 1
                state = "literal-mask" if strings else "literal-keep"
                continue
            i += 1
            continue
        if state == "block":
            if ch == "*" and nxt == "/":
                out[i] = out[i + 1] = " "
                i += 2
                state = "code"
                continue
            if ch != "\n":
                out[i] = " "
            i += 1
            continue
        if state == "line":
            if ch == "\n":
                state = "code"
            else:
                out[i] = " "
            i += 1
            continue
        if ch == "\\" and i + 1 < len(text):
            if state == "literal-mask":
                if ch != "\n":
                    out[i] = " "
                if text[i + 1] != "\n":
                    out[i + 1] = " "
            i += 2
            continue
        if ch == quote:
            if state == "literal-mask":
                out[i] = " "
            i += 1
            state = "code"
            continue
        if state == "literal-mask" and ch != "\n":
            out[i] = " "
        i += 1
    return "".join(out)


def _line_data(text: str):
    lines = text.splitlines(keepends=True)
    starts, offset = [], 0
    for line in lines:
        starts.append(offset)
        offset += len(line)
    if not lines or offset < len(text) or (text and text.endswith("\n")):
        starts.append(offset)
    return lines, starts


def _line_of(starts: Sequence[int], offset: int) -> int:
    return max(0, bisect_right(starts, offset) - 1)


def _define_lines(text: str) -> set[int]:
    """Physical lines belonging to a #define, including continuations."""
    lines = _mask(text).splitlines(keepends=True)
    result, continuing = set(), False
    for index, line in enumerate(lines):
        starts_define = bool(re.match(r"^[ \t]*#[ \t]*define\b", line))
        if starts_define or continuing:
            result.add(index)
            continuing = line.rstrip("\r\n").rstrip().endswith("\\")
        else:
            continuing = False
    return result


def _macro_names(text: str) -> set[str]:
    """Names defined in this translation unit, including lowercase wrappers."""
    comments_masked = _mask(text)
    return set(re.findall(
        r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)\b", comments_masked, re.M))


def _code_for_braces(text: str) -> str:
    code = list(_mask(text))
    lines, starts = _line_data(text)
    continuing = False
    for index, line in enumerate(lines):
        start = starts[index]
        masked_line = "".join(code[start:start + len(line)])
        directive = continuing or bool(re.match(r"^[ \t]*#", masked_line))
        if directive:
            for pos in range(start, min(start + len(line), len(code))):
                if code[pos] != "\n":
                    code[pos] = " "
            continuing = line.rstrip("\r\n").rstrip().endswith("\\")
        else:
            continuing = False
    return "".join(code)


def _pairs(code: str, opening: str, closing: str) -> list[tuple[int, int]]:
    stack, result = [], []
    for index, char in enumerate(code):
        if char == opening:
            stack.append(index)
        elif char == closing and stack:
            result.append((stack.pop(), index))
    return result


def _function_regions(code: str, brace_pairs: Sequence[tuple[int, int]]) -> list[tuple[int, int]]:
    by_open = {start: end for start, end in brace_pairs}
    regions = []
    for match in FUNCTION_RE.finditer(code):
        if match.group("name") in CONTROL_WORDS:
            continue
        opening = match.end() - 1
        if opening in by_open:
            regions.append((opening, by_open[opening]))
    return regions


def _call_spans(code: str, start: int, end: int,
                paren_pairs: Sequence[tuple[int, int]]) -> list[tuple[str, int, int]]:
    by_open = {opening: closing for opening, closing in paren_pairs}
    calls = []
    for match in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", code[start:end]):
        name = match.group(1)
        opening = start + match.end() - 1
        closing = by_open.get(opening)
        if closing is not None and closing <= end:
            calls.append((name, opening, closing))
    return calls


def _unsafe_use(code: str, occurrence: re.Match, scope_end: int,
                calls: Sequence[tuple[str, int, int]],
                paren_pairs: Sequence[tuple[int, int]]) -> bool:
    start, end = occurrence.span()
    name = occurrence.group(0)
    for callee, opening, closing in calls:
        if opening < start < closing and callee not in CALL_KEYWORDS:
            return True

    grouped_start, grouped_end = start, end
    while True:
        wrappers = [pair for pair in paren_pairs
                    if pair[0] < grouped_start and grouped_end <= pair[1]
                    and not code[pair[0] + 1:grouped_start].strip()
                    and not code[grouped_end:pair[1]].strip()]
        if not wrappers:
            break
        opening, closing = max(wrappers, key=lambda pair: pair[0])
        grouped_start, grouped_end = opening, closing + 1

    before = code[:grouped_start].rstrip()
    after = code[grouped_end:scope_end]
    if re.search(r"(?:\+\+|--)\s*$", before):
        return True
    if before.endswith("&") and not before.endswith("&&"):
        return True

    operator = re.match(
        r"\s*(?:\)\s*)*(?P<op>(?:<<|>>|[+\-*/%&|^])=|=(?!=)|\+\+|--)", after)
    if not operator:
        return False
    if operator.group("op") != "=":
        return True
    if grouped_start != start or grouped_end != end:
        return True
    semicolon = code.find(";", end, scope_end)
    if semicolon < 0:
        return True
    assignment = code[start:semicolon + 1]
    return re.fullmatch(rf"{re.escape(name)}\s*=\s*0\s*;", assignment) is None


def _has_shadow(code: str, name: str) -> bool:
    """Conservatively recognize a later declaration, including unknown typedefs."""
    for occurrence in re.finditer(rf"\b{re.escape(name)}\b", code):
        boundary = max(code.rfind(char, 0, occurrence.start())
                       for char in (";", "{", "}", "(", "\n"))
        prefix = code[boundary + 1:occurrence.start()].strip()
        if not prefix or not re.fullmatch(
                r"(?:[A-Za-z_]\w*[ \t]+)+(?:\*+[ \t]*)?", prefix + " "):
            continue
        words = re.findall(r"[A-Za-z_]\w*", prefix)
        if words and words[0] not in NON_DECLARATION_PREFIXES:
            return True
    return False


def _has_bypassing_entry(code: str, declaration_end: int,
                         scope_start: int, scope_end: int,
                         function_start: int, function_end: int) -> bool:
    """Whether control can enter a later label without running the initializer.

    Ordinary labels are function scoped.  A forward goto from before the
    declaration, or a goto originating outside its lexical scope, can therefore
    skip the initializer.  A goto later in the same scope cannot.  Any later
    case/default label is conservatively refused because its owning switch can
    dispatch past the declaration, including through a nested compound block.
    Comments and literals have already been masked.
    """
    tail = code[declaration_end:scope_end]
    if re.search(r"\b(?:case|default)\b", tail):
        return True

    # Match labels wherever a statement may occur, including ``if (c) label:``.
    # Non-label colons only matter if a matching goto also exists, in which case
    # refusing the ambiguous construct is the conservative result.
    label_re = re.compile(r"\b(?P<label>[A-Za-z_]\w*)\s*:")
    function = code[function_start:function_end]
    for match in label_re.finditer(tail):
        label = match.group("label")
        if label in ("case", "default"):
            continue

        if re.search(rf"&&\s*{re.escape(label)}\b", function):
            return True
        if re.search(r"\bgoto\s*\*", function):
            return True
        for goto in re.finditer(
                rf"\bgoto\s+{re.escape(label)}\s*;", function):
            goto_start = function_start + goto.start()
            if goto_start < declaration_end:
                return True
            if not scope_start < goto_start < scope_end:
                return True
    return False


def _admitted_sites(text: str) -> list[Site]:
    comments_masked = _mask(text, strings=False)
    code = _code_for_braces(text)
    lexical = _mask(text)
    lines, starts = _line_data(text)
    labels = arm_labels(text)
    definitions = _define_lines(text)
    brace_pairs = _pairs(code, "{", "}")
    paren_pairs = _pairs(code, "(", ")")
    functions = _function_regions(code, brace_pairs)
    macro_names = _macro_names(text)
    live_lines = {
        site[5] - 1 for site in sites_of(text)
        if site[0] == "reg" and site[1] == "ASM_REG" and site[2] in ("0", "zero")
    }

    admitted = []
    for target in TARGET_RE.finditer(comments_masked):
        register_start = target.start() + len(target.group("indent"))
        if lexical[register_start:register_start + len("register")] != "register":
            continue
        line = _line_of(starts, target.start())
        if line in definitions or line not in live_lines:
            continue
        if line < len(labels) and labels[line] in ("port", "dead"):
            continue
        function = next((region for region in functions
                         if region[0] < target.start() < region[1]), None)
        if function is None:
            continue
        scopes = [pair for pair in brace_pairs
                  if function[0] <= pair[0] < target.start() < pair[1] <= function[1]]
        if not scopes:
            continue
        scope_start, scope_end = max(scopes, key=lambda pair: pair[0])
        name = target.group("name")
        tail = lexical[target.end():scope_end]

        if (name in macro_names or _has_shadow(tail, name)
                or _has_bypassing_entry(
                    lexical, target.end(), scope_start, scope_end,
                    function[0], function[1])):
            continue
        name_occurrences = list(re.finditer(rf"\b{re.escape(name)}\b", tail))
        absolute_occurrences = []
        name_pattern = re.compile(rf"{re.escape(name)}")
        for occurrence in name_occurrences:
            absolute_occurrences.append(name_pattern.match(
                lexical, target.end() + occurrence.start(), target.end() + occurrence.end()))
        if any(occurrence is None for occurrence in absolute_occurrences):
            continue

        calls = _call_spans(lexical, target.end(), scope_end, paren_pairs)
        unsafe = False
        for occurrence in absolute_occurrences:
            occurrence_line = _line_of(starts, occurrence.start())
            if occurrence_line in definitions:
                unsafe = True
                break
            if _unsafe_use(lexical, occurrence, scope_end, calls, paren_pairs):
                unsafe = True
                break
        if unsafe:
            continue
        admitted.append(Site(name, target.start(), target.end(), line + 1,
                             scope_start, scope_end))
    return admitted


def zero_init_candidates(text: str) -> list[tuple[str, str]]:
    """Return zero or one candidate containing every independently admitted site."""
    sites = _admitted_sites(text)
    if not sites:
        return []
    candidate = text
    for site in sorted(sites, key=lambda item: item.start, reverse=True):
        declaration = text[site.start:site.end]
        replacement = re.sub(
            r"\bregister\s+s32\s+([A-Za-z_]\w*)\s+"
            r"ASM_REG\(\s*\"\$(?:0|zero)\"\s*\)\s*;",
            r"s32 \1 = 0;", declaration, count=1)
        candidate = candidate[:site.start] + replacement + candidate[site.end:]
    labels = ",".join(f"{site.name}@{site.line}" for site in sites)
    return [(f"zero-init:{labels}", candidate)]


class T:
    name = "zero_init"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if zero_init_candidates(text) else "no guarded hardware-zero initialization"

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        candidates = zero_init_candidates(text)
        if not candidates:
            return None, {"refused": ["no guarded hardware-zero initialization"]}
        label, candidate = candidates[0]
        score = verify_fn(candidate)
        if score.get("exact"):
            return candidate, {"label": label, "sites": label.count("@")}
        return None, {"refused": ["ordinary zero initialization is not exact"],
                      "candidate_score": score}
