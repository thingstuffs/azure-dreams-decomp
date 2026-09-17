"""OR-zero pins -> plain constants (old-ASPSX `li` expansion: `li r,K` -> `ori r,$zero,K`).

t45_orzero_aspsx (2026-09-13).  Retail materialises small constants (0 < K < 0x8000) either as
`addiu rX,$zero,K` (GAS and ASPSX >= 2.50 expand `li` that way) or as `ori rX,$zero,K` (ASPSX < 2.50,
maspsx `expand_li`).  No C spelling reaches the `ori` form through gcc, so rows that needed it were
pinned with `register s32/u32 zero ASM_REG("$0")` carriers (`zero | K`).  A static census of retail bytes
found the `ori` form only in town: 22 pinned rows + 1 clean, no row mixing the two forms, in
address islands 0x80874C9C-0x808757A0, 0x80877FEC-0x80878110, 0x80878924-0x80878A78,
0x8087FD58-0x808816D8 (eleven rows in 0x80878180-0x80878714, and func_80880298, are addiu TUs).  The fix is the
per-function as-flag `--aspsx-version=2.40` (config/overlays/town.as_flags.jsonl, one proof record per
row) plus this rewrite; 20 rows / 38 pins, all landed.

    python3 tools/orzero_aspsx.py src/town/func_X.c > cand/town/func_X.c            # full rewrite
    rewrite(text, scored_only=True)       # NON_MATCHING arms untouched (the lint's unscored_text);
                                          # the full rewrite of the landed text is then the tidy,
                                          # landed by pin_census.landing_refusal's port codegen identity
    python3 tools/apply_candidates.py cand --transform t45_orzero_aspsx   (<name>.c.port_ref for rows
                                          whose current port build no longer compiles)

  `({ register s32/u32 zero ASM_REG("$0"); [ASM_KEEP(zero);] zero | (K); })` -> K
  a `register s32/u32 NAME ASM_REG("$0")` whose every use is `NAME | K` -> dropped, uses become K; its
      companion statements ASM_UNDEF(NAME); READ_ZERO(NAME); ASM_KEEP(NAME); and NON_MATCHING
      `NAME = 0;` arms go with it
  NON_MATCHING arms of the declaration (`s32/u32 NAME = 0;`, `#define NAME 0`) -> folded
  the nameless `#define ({...}) (value)` NON_MATCHING arms that 548963e9 left behind -> removed
  local wrapper macros (READ_ZERO, ASM_UNDEF, ...) left unreferenced -> removed
"""
import re, sys

TYPE32 = r'(?:s32|u32)'
SX = re.compile(r'\(\{\s*register ' + TYPE32 + r' (\w+) ASM_REG\("\$0"\);\s*(?:ASM_KEEP\(\1\);\s*)?\1 \| \(([^()]*)\);\s*\}\)')
BAD = re.compile(r'#ifdef NON_MATCHING\n#define \(\{[^\n]*\n#else\n#endif\n\n?')
REGDECL = r'[ \t]*register ' + TYPE32 + r' (\w+) ASM_REG\("\$0"\);[^\n]*\n'
FOLD = [
    re.compile(r'#ifndef NON_MATCHING\n' + REGDECL + r'#else\n#define \1 0\n#endif\n'),
]
FOLD_VAR = re.compile(r'#ifndef NON_MATCHING\n'
                      r'[ \t]*register (?P<type>s32|u32) (?P<name>\w+) ASM_REG\("\$0"\);[^\n]*\n'
                      r'#else\n[ \t]*(?P=type) (?P=name) = 0;\n#endif\n')
FOLD2 = re.compile(r'#ifdef NON_MATCHING\n[ \t]*(?P<type>s32|u32) (?P<name>\w+) = 0;\n'
                   r'#else\n(?P<indent>[ \t]*)register (?P=type) (?P=name) ASM_REG\("\$0"\);[^\n]*\n'
                   r'#endif\n')
DECL = re.compile(r'^' + REGDECL, re.M)
WRAP = re.compile(r'#if(?:n?def)? [^\n]*\n(?:#define (\w+)\([^\n]*\n|#else\n)+#endif\n')


def _scored(t):
    """t with the port/dead arm lines blanked (what the byte gate compiles, line numbers kept)."""
    sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
    from pin_census import arm_labels
    L = t.split("\n")
    lab = arm_labels(t) + ["both"] * 2
    return "\n".join("" if lab[i] in ("port", "dead") else l for i, l in enumerate(L))


def _map_code_lines(t, fix, scored_only=False):
    """Apply ``fix`` to non-directive code lines, excluding port/dead arms when requested."""
    labels = None
    if scored_only:
        sys.path.insert(0, str(__import__("pathlib").Path(__file__).resolve().parent))
        from pin_census import arm_labels
        labels = arm_labels(t)
    out = []
    for i, line in enumerate(t.splitlines(keepends=True)):
        if line.startswith("#") or (labels is not None and labels[i] in ("port", "dead")):
            out.append(line)
        else:
            out.append(fix(line))
    return "".join(out)


def _or_only(t, name, scored_only=False):
    """Whether untouched source uses NAME only as the left operand of OR.

    Recognised declarations, companions, and type-consistent conditional fallbacks are syntax,
    not value uses.  This check must precede every fold/removal: otherwise a later refusal can
    accidentally return source whose conditional declaration was already normalised away.
    """
    probe = _scored(t) if scored_only else t
    if not scored_only:
        for fold in FOLD:
            probe = fold.sub("", probe)
        probe = FOLD_VAR.sub("", probe)
        probe = FOLD2.sub("", probe)
        probe = re.sub(r'#ifdef NON_MATCHING\n[ \t]*' + name + r' = 0;\n#endif\n', '', probe)

    def remove_syntax(line):
        line = re.sub(r'^[ \t]*register ' + TYPE32 + r' ' + name
                      + r' ASM_REG\("\$0"\);[^\n]*(?:\n)?$', '', line)
        return re.sub(r'^[ \t]*(?:ASM_UNDEF|READ_ZERO|ASM_KEEP)\(' + name
                      + r'\);[^\n]*(?:\n)?$', '', line)
    probe = _map_code_lines(probe, remove_syntax)
    code = re.sub(r'/\*.*?\*/', '', probe, flags=re.S)
    uses = re.findall(r'\b' + name + r'\b(\s*\|)?', code)
    return bool(uses) and all(uses)


def drop_name(t, name, scored_only=False):
    """Every declaration of NAME and its companions removed, and `NAME | K` -> K; None if NAME has
    any other use.  scored_only: port arms (`NAME = 0;` fallbacks) are left as they are."""
    if not _or_only(t, name, scored_only):
        return None

    def remove_companions(line):
        line = re.sub(r'^[ \t]*register ' + TYPE32 + r' ' + name
                      + r' ASM_REG\("\$0"\);[^\n]*(?:\n)?$', '', line)
        return re.sub(r'^[ \t]*(?:ASM_UNDEF|READ_ZERO|ASM_KEEP)\(' + name
                      + r'\);[^\n]*(?:\n)?$', '', line)
    u = _map_code_lines(t, remove_companions, scored_only)
    if not scored_only:
        u = re.sub(r'#ifdef NON_MATCHING\n[ \t]*' + name + r' = 0;\n#endif\n', '', u)
    code = re.sub(r'/\*.*?\*/', '', _scored(u) if scored_only else u, flags=re.S)
    uses = re.findall(r'\b' + name + r'\b(\s*\|)?', code)
    if not uses or not all(uses):
        return None
    def fix(line):                                        # never inside a directive
        line = re.sub(r'\(\s*' + name + r'\s*\|\s*([^()]+?)\)', r'(\1)', line)
        return re.sub(r'\b' + name + r'\s*\|\s*', '', line)
    return _map_code_lines(u, fix, scored_only)


def rewrite(t, scored_only=False):
    """scored_only: never touch a NON_MATCHING port arm (the lint's unscored_text); the port-only
    leftovers go in a second, codegen-identical tidy pass (the full rewrite of the landed text)."""
    safe = {m.group(1) for m in DECL.finditer(t) if _or_only(t, m.group(1), scored_only)}
    t = _map_code_lines(t, lambda line: SX.sub(lambda m: m.group(2), line), scored_only)
    if scored_only:
        def scored_ifndef(m):
            return m.group(1) if m.group(2) in safe else m.group(0)
        t = re.sub(r'(#ifndef NON_MATCHING\n)' + REGDECL, scored_ifndef, t)  # matching arm only

        def scored_ifdef(m):
            return m.group(1) if m.group(3) in safe else m.group(0)
        t = re.sub(r'(#ifdef NON_MATCHING\n[ \t]*(s32|u32) (\w+) = 0;\n#else\n)'
                   r'[ \t]*register \2 \3 ASM_REG\("\$0"\);[^\n]*\n', scored_ifdef, t)
        for name in dict.fromkeys(re.findall(r'\b(\w+) \|', _scored(t))):
            if name in safe and (re.search(r'(?:#define \b' + name + r'\b 0|\b' + TYPE32 + r' ' + name + r' = 0;)', t) or re.search(r'register ' + TYPE32 + r' ' + name + r' ASM_REG\("\$0"\)', t)):
                u = drop_name(t, name, scored_only=True)
                if u is not None:
                    t = u
        return t
    t = BAD.sub("", t)
    for f in FOLD:
        t = f.sub(lambda m: m.group(0).split("\n")[1] + "\n"
                  if m.group(1) in safe else m.group(0), t)
    t = FOLD_VAR.sub(lambda m: m.group(0).split("\n")[1] + "\n"
                     if m["name"] in safe else m.group(0), t)
    t = FOLD2.sub(lambda m: f'{m["indent"]}register {m["type"]} {m["name"]} ASM_REG("$0");\n'
                  if m["name"] in safe else m.group(0), t)
    for name in dict.fromkeys(m.group(1) for m in DECL.finditer(t)):
        u = drop_name(t, name) if name in safe else None
        if u is not None:
            t = u
    for m in list(WRAP.finditer(t)):                       # wrappers nothing uses any more
        names = re.findall(r'#define (\w+)\(', m.group(0))
        rest = t.replace(m.group(0), "")
        if names and not any(re.search(r'\b' + n + r'\s*\(', rest) for n in names):
            t = rest
    return t


if __name__ == "__main__":
    for f in sys.argv[1:]:
        print(rewrite(open(f).read()), end="")
