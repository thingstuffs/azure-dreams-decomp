"""T92: a STAGED page-address run collapsed to the symbol at the run's final address.

APPEARS     a pinned local seeded with an integer page and then biased to its real address by one or
            more offset steps, the pins holding the two halves apart:

                (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3328;
                table = (s16 *)((s16)action->angle);
                update_x_entry = (u16 *)((s32)table + table_work);
                (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3318;
                update_y_entry = (u16 *)((s32)table + table_work);
                ASM_KEEP(update_y_entry);           <- freed with the second run

            and its declaration-initialiser form, with the run spread over other statements and a
            pin on one of them (dungeon/func_8180E7F4):

                u32 dead_base = 0x800E0000;
                s32 dead_index;
                ASM_KEEP_NV(dead_base);
                dead_index = ((S_800277F4_20 *)donor_runtime)->unk_03;
                ASM_KEEP(dead_index);               <- inside the window: erased jointly
                dead_base += 0x3DF0;
                ASM_KEEP_NV(dead_base);

            and the pointer form, where the bias is spelled through a byte view
            (`lookup_base = (s16 *)((u8 *)lookup_base - 0x3328);`), often inside the `#else` arm of
            an `#ifdef NON_MATCHING` whose port arm already NAMES the symbol.

RESOLVES    six rows of the round-63/66 big-row lanes, byte-exact at their recorded recipes:
            dungeon/func_818C3B90 (2 runs, 3 pins), func_818BDEBC (2/2), func_81912154 (2/2),
            func_8180E7F4 (1/3), func_819ADDB8 (1/1).  Mechanism, unchanged from t29/t54: the page
            constant plus a separate bias hides the address from cse's `fold_rtx`, and the keep stops
            the fold that would otherwise put one integer address in one pseudo.  Written as the
            symbol at the final address, gcc splits it into the `lui`/`addiu` HIGH/LO_SUM pair retail
            has, and the whole staging run - seed, bias and pins - goes.

            Why the two owners missed the shape (measured 2026-09-21 on the five lane rows):
              * t29_addrsym substitutes the symbol for every USE and deletes the local, so a variable
                re-staged to a SECOND symbol later in the same function refuses `modified`
                (func_818C3B90: `{'table_work': 'modified'}`), and a run in a `#else` arm refuses
                `port-arm` because collapsing the `#ifdef` changes `unscored_text`.
              * t54_pagebase keeps the local but its only candidate that DROPS the bias step is
                `cursor_candidates`, which refuses any function containing a `goto` or a label (all
                five rows are m2c goto soup), any non-pointer local (`s32 table_work`,
                `u32 dead_base`) and any variable with more than one definition.  Its `anchor:`
                candidates respell the page and leave the `-= 0x3328` standing.

CANDIDATES  each run alone and all runs together, each with (a) every pin inside the run's window,
            (b) only the window's pins that name the staged local, (c) the whole function's pins.
            The window runs from the seed to the last bias step and swallows the pin statements that
            immediately follow it.  A candidate is screened against the pinned text's cc1 listing and
            only a listing-exact one (plus the two nearest) is put to the byte verifier.  The rewrite
            NEVER touches a port arm: a candidate whose `unscored_text` moved is dropped, so a run
            inside `#else` is rewritten there and the `#ifdef NON_MATCHING` arm stays byte-identical.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
import xform.t29_addrsym as A
import xform.screen as screen

MAX_RUNS = 8
MAX_LISTINGS = 160
MAX_VERIFY = 6
MAX_STEP_STATEMENTS = 12

mask_comments = A.mask_comments
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
# A declaration head before the assigned name.  The type token MUST be separated from the name by
# whitespace or by at least one star, or the regex splits an identifier (`lookup_bas` + `e`).
TYPE = (r"(?:register[ \t]+)?(?:(?:unsigned|signed|const|volatile|static|struct|union)[ \t]+)*"
        r"[A-Za-z_]\w*(?:[ \t]+long)?(?:[ \t]+\**[ \t]*|[ \t]*\*+[ \t]*)")
SEED_RE = re.compile(r"(?:^|[;{}:])(?P<lead>[ \t\n]*(?:%s)?)\(?(?P<v>[A-Za-z_]\w*)\)?[ \t]*=[ \t]*"
                     r"(?P<rhs>%s)[ \t]*;" % (TYPE, A.LIT), re.M)
PIN_STMT_RE = re.compile(r"[ \t]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;")
KEYWORDS = {"if", "while", "for", "switch", "return", "do", "else", "case", "goto", "default"}


def _elem_bytes(ty, ptr):
    """Bytes one `V += 1` step moves for a local declared `ty` with `ptr` stars."""
    if ptr > 1:
        return 4
    if ptr == 1:
        return A.ELEMSIZE.get(ty, 1)
    return 1                                       # an integer local: the offset is already bytes


def _step(chunk, v, ty, ptr):
    """Byte delta of a bias step on V in `chunk`, or None if the chunk is not one."""
    V = re.escape(v)
    m = re.fullmatch(r"[ \t\n]*\(?%s\)?[ \t]*(?P<op>[-+])=[ \t]*(?P<k>%s)[ \t]*;[ \t]*" % (V, NUM), chunk)
    if m:
        k = int(m.group("k"), 0) * _elem_bytes(ty, ptr)
        return -k if m.group("op") == "-" else k
    # `V = (T *)((u8 *)V - K);` / `V = (T *)V - K;` / `V = V + K;`
    m = re.fullmatch(r"[ \t\n]*\(?%s\)?[ \t]*=[ \t]*(?P<cast>%s*)\(?[ \t]*(?P<inner>%s*)\(?%s\)?"
                     r"[ \t]*(?P<op>[-+])[ \t]*(?P<k>%s)[ \t]*\)?[ \t]*;[ \t]*"
                     % (V, A.CAST, A.CAST, V, NUM), chunk)
    if not m:
        return None
    inner = m.group("inner") or ""
    if inner:
        it = re.sub(r"[\s()*]", " ", inner).split()
        scale = 1 if it and it[0] in A.BYTEPTR else _elem_bytes(ty, ptr)
    else:
        scale = _elem_bytes(ty, ptr)
    k = int(m.group("k"), 0) * scale
    return -k if m.group("op") == "-" else k


def _chunks(masked, start, stop):
    """Statement-sized spans of `masked[start:stop]`, split on top-level `;`."""
    out, depth, a = [], 0, start
    for i in range(start, stop):
        c = masked[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
            if depth < 0:
                out.append((a, i, masked[a:i]))
                return out, "brace"
        elif c == ";" and depth == 0:
            out.append((a, i + 1, masked[a:i + 1]))
            a = i + 1
    return out, "end"


def runs(text):
    """Staged page runs: [{'v','value','addr','seed','steps','lo','hi','ty','ptr'}] (offsets in text)."""
    masked = mask_comments(text)
    out = []
    for m in SEED_RE.finditer(masked):
        v = m.group("v")
        if v in KEYWORDS:
            continue
        decls = A.decls_of(masked, v)
        if not decls:
            continue
        tys = {(t, p) for t, p, _ in decls}
        if len(tys) != 1:
            continue                                # the same name declared twice at two types
        ty, ptr = next(iter(tys))
        page = int(re.search(r"0x(8[0-9A-Fa-f]{7})", m.group("rhs")).group(1), 16)
        cs, _ = _chunks(masked, m.end(), min(len(masked), m.end() + 4000))
        addr, steps, seen = page, [], 0
        for a, b, chunk in cs:
            if seen >= MAX_STEP_STATEMENTS:
                break
            body = chunk.strip()
            if not body:
                continue
            if re.search(r"[{}]|^\s*(?:%s)\b|^[ \t\n]*[A-Za-z_]\w*[ \t]*:" % "|".join(KEYWORDS), body):
                break
            seen += 1
            if PIN_STMT_RE.fullmatch(chunk.rstrip() + ";" if not chunk.rstrip().endswith(";") else chunk.rstrip()) \
                    or re.fullmatch(r"[ \t\n]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;[ \t]*", chunk):
                continue                            # a pin statement inside the run
            d = _step(chunk, v, ty, ptr)
            if d is not None:
                addr = (addr + d) & 0xFFFFFFFF
                steps.append((a, b))
                continue
            if re.search(r"\b%s\b" % re.escape(v), chunk):
                break                               # V is READ before the run finishes: stop here
        if not steps or addr == page:
            continue
        lo, hi = m.start("lead") + len(m.group("lead")), steps[-1][1]
        # Swallow the pin statements that immediately follow the last step; the WIDE window also
        # reaches past up to two further statements that still read V, because the consumer of the
        # staged address usually carries a keep of its own (func_818C3B90:
        # `update_y_entry = (u16 *)((s32)table + table_work); ASM_KEEP(update_y_entry);`).
        def swallow(at, over):
            used = 0
            for a2, b2, c2 in _chunks(masked, at, min(len(masked), at + 600))[0]:
                if not c2.strip():
                    continue
                if re.fullmatch(r"[ \t\n]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;[ \t]*", c2):
                    at = b2; continue
                if used < over and re.search(r"\b%s\b" % re.escape(v), c2) and "{" not in c2 and "}" not in c2:
                    at = b2; used += 1; continue
                break
            return at
        hi, wide = swallow(hi, 0), swallow(hi, 2)
        lhs = (m.start("lead") + len(m.group("lead")), m.start("rhs"))
        out.append({"v": v, "value": page, "addr": addr, "seed": (m.start("rhs"), m.end("rhs")), "lhs": lhs,
                    "steps": steps, "lo": lo, "hi": hi, "wide": wide, "ty": ty, "ptr": ptr})
    return out


def _tidy(t):
    return re.sub(r"[ \t]+$", "", t, flags=re.M)


def _edits(text, chosen):
    """(edit list on `text`, externs) for the chosen runs: seed respelled, bias steps cut."""
    edits, ext = [], set()
    for r in chosen:
        want = (r["ty"] + " " + "*" * r["ptr"]) if r["ptr"] else None
        sym = A.sym_expr(text, r["addr"], want, ext)
        if r["ptr"] == 0 and not re.fullmatch(r"\(%s\)\s*\S+" % re.escape(r["ty"]), sym):
            sym = "(%s)%s" % (r["ty"], sym)
        edits.append((r["seed"][0], r["seed"][1], sym))
        head = text[r["lhs"][0]:r["lhs"][1]]
        if head.lstrip().startswith("("):          # `(V) = ...` -> `V = ...`
            edits.append((r["lhs"][0], r["lhs"][1],
                          re.sub(r"\(\s*(%s)\s*\)" % re.escape(r["v"]), r"\1", head, count=1)))
        for a, b in r["steps"]:
            while a > 0 and text[a - 1] in " \t":
                a -= 1
            edits.append((a, b, ""))
    return edits, ext


def _apply(text, edits):
    t = text
    for a, b, rep in sorted(edits, reverse=True):
        t = t[:a] + rep + t[b:]
    return t


def _shift(edits, pos):
    """How far an offset at or after `pos` in the original text moves once `edits` are applied."""
    return sum(len(rep) - (b - a) for a, b, rep in edits if b <= pos)


def _externs(t, ext):
    if not ext:
        return t
    lines = t.splitlines(True)
    at = max((i for i, l in enumerate(lines) if l.startswith("#include")), default=-1) + 1
    lines[at:at] = [e for e in sorted(ext) if e.strip() not in t]
    return "".join(lines)


def _tidy(t):
    return re.sub(r"[ \t]+$", "", t, flags=re.M)


def rewrite(text, chosen, drop=()):
    """The chosen runs collapsed to their symbol, with the pin sites in `drop` erased.

    `drop` holds sites from a `sites_of(text)` call on the SAME text: the address edits go in
    first and each site is then taken by its ORDINAL, so two runs spelled identically in two
    functions of one file can never be confused for each other.  (An offset map would not do: a
    `stmt` site's span covers its whole line only when no comment trails the macro, so erasing a
    pin note ahead of it moves its start by the indentation as well.)
    """
    edits, ext = _edits(text, chosen)
    t = _apply(text, edits)
    if drop:
        before, after = sites_of(text), sites_of(t)
        if len(before) != len(after):
            return None                            # an edit swallowed a pin: not this generator's move
        order = {s[3]: i for i, s in enumerate(before)}
        moved = [after[order[s[3]]] for s in drop if s[3] in order]
        if len(moved) != len(drop):
            return None
        t = erase_many(t, moved, clean_notes=True)
    return _tidy(_externs(t, ext))


def candidates(text):
    """[(label, new_text)] - each run alone then all of them, with two or three pin groups each."""
    found = runs(text)[:MAX_RUNS]
    out, seen, sig = [], {text}, unscored_text(text)
    groups = [[r] for r in found] + ([found] if len(found) > 1 else [])
    for chosen in groups:
        tag = "run@%d" % chosen[0]["lo"] if len(chosen) == 1 else "runs%d" % len(chosen)
        win = [s for s in sites_of(text) if any(r["lo"] <= s[3] < r["hi"] for r in chosen)]
        named = [s for s in win if any(re.search(r"\b%s\b" % re.escape(r["v"]), text[s[3]:s[4]]) for r in chosen)]
        wider = [s for s in sites_of(text) if any(r["lo"] <= s[3] < r["wide"] for r in chosen)]
        outside = [s for s in sites_of(text) if s not in wider]
        near1 = wider + sorted(outside, key=lambda s: min(abs(s[3] - r["lo"]) for r in chosen))[:1]
        plans = [("win", win), ("wide", wider), ("wide+1", near1), ("var", named)]
        if len(sites_of(text)) <= 4:               # erasing every pin is only a plan on a small row
            plans.append(("fn", sites_of(text)))
        for name, group in plans:
            if not group:
                continue
            new = rewrite(text, chosen, group)
            if new is None or new in seen or unscored_text(new) != sig:
                continue
            if len(sites_of(new)) >= len(sites_of(text)):
                continue
            seen.add(new)
            out.append(("%s:%s:%s" % (tag, chosen[0]["v"], name), new))
    return out


class T:
    name = "t92_pagerun"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        found = runs(text)
        if not found:
            return "no staged page run"
        if not any(s[3] < r["hi"] and s[3] >= r["lo"] for r in found for s in sites_of(text)):
            return "no pin inside a staged page run"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        """One run at a time, each accepted candidate becoming the base for the next.

        A function usually stages the SAME local to two or three symbols (func_818C3B90 has four
        runs over two functions of the file), and the runs are independent: taking only the first
        exact one would leave the rest pinned.  The listing target stays the PINNED text's listing
        throughout - it is the byte-exact one, so every accepted step must still assemble to it.
        """
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "runs": len(runs(text))}
        if not candidates(text):
            return None, dict(info, refused=["no candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        cur, steps, listings, verifies, spent, nearest = text, [], 0, 0, set(), []
        while listings < MAX_LISTINGS and verifies < MAX_VERIFY:
            ranked = []
            for label, cand in candidates(cur):
                if cand in spent or listings >= MAX_LISTINGS:
                    continue
                lst = screen.compile_s(row, cand); listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                ranked.append((d, len(sites_of(cand)), label, cand))
            ranked.sort(key=lambda x: (x[0], x[1]))
            if not steps:
                nearest = [{"distance": d, "label": l} for d, _, l, _ in ranked[:6]]
            moved = False
            for d, _, label, cand in ranked:
                # a listing-exact candidate is always worth a verify; a distant one only while
                # nothing has been accepted yet, and then at most twice
                if verifies >= MAX_VERIFY or (d and (steps or verifies >= 2)):
                    break
                spent.add(cand); verifies += 1
                if vf(cand).get("exact"):
                    cur, moved = cand, True
                    steps.append("%s|d%d" % (label, d))
                    break
            if not moved:
                break
        info.update(listings=listings, tried=verifies)
        if not steps:
            return None, dict(info, nearest=nearest)
        return cur, dict(info, step="+".join(steps), pins_out=len(sites_of(cur)))
