"""T93: a block-scoped register-pinned local merged into an existing local of an ENCLOSING scope.

APPEARS     a nested block that declares its own `register T v ASM_REG("$n")` (with or without an
            initialiser) while a local of the same type, declared further out, is not named anywhere
            inside that block (dungeon/func_8180C3C0, seven such declarations in one function):

                switch (state) {
                    register void *object_m ASM_REG("$16");
                    register s32 object_index_m ASM_REG("$17");     <- the enclosing local
                    ...
                case 2:
                    {
                        register s32 object_index ASM_REG("$17") = 0;   <- the pin
                        u32 mask = 0x20000000;
                        void *object_slot = sequence;
                        loop_0: { ... object_index++; ... }
                    }

            ->      {
                        u32 mask;
                        void *object_slot;
                        object_index_m = 0;
                        mask = 0x20000000;
                        object_slot = sequence;
                        loop_0: { ... object_index_m++; ... }
                    }

            and the initialiser-free form inside an `if` body (dungeon/func_80DB9000):
            `register u32 uv_adjusted ASM_REG("$2");` merged into the function's `register u32
            coord_value;`, which is dead across that block.

RESOLVES    eight pins over two rows of the round-63 big lanes, byte-exact at their recorded recipes
            (func_8180C3C0 7, func_80DB9000 1).  Mechanism: the two names are ONE pseudo in retail.
            Splitting them gives the second value a pseudo that is born inside the block, which
            changes both its birth priority (sched.c `birthing_insn_p`) and the allocator's
            preference order - the register pin was standing in for the merge.  Same lever as
            t87/t90, one scope down.

            Why t87/t90 missed it (measured 2026-09-21 on four lane rows): both pair DECLARATIONS
            found by `natural._functions` and rename BY NAME.  func_8180C3C0 declares four separate
            `register s32 object_index ASM_REG("$17") = 0;` locals in four sibling blocks, so the
            name does not identify the variable and a by-name rewrite would corrupt the other three;
            neither module offered any of the four pairs (`t87` 2 candidates, `t90` 17, none of them
            the inner declarations).  This generator keys the donee by its DECLARATION SPAN and
            rewrites only the uses inside that declaration's own block.

KIT WAVE (round 71) - two detector gaps measured on work/native_lane/r70_kit_astra3 and astra4:
              * the donee's pin is not always IN its declaration.  dungeon/func_81008664 declares
                `s32 fall_duration = 0x10;` in a nested block and pins it with a separate
                `ASM_KEEP_NV(fall_duration);` statement; `donees()` only ever kept declarations
                carrying an `ASM_REG(...)`, so the row refused outright.  A plain declaration whose
                block holds a pin NAMING it is now a donee too (the rename hands the pin to the
                donor and the `erase` plan takes it).
              * the donor need not share the donee's type.  func_81008664's donor `fall_anim` is
                `u32` against the donee's `s32` - one pseudo in retail, two names of two widths in
                the recovered C - so an integer donee now also accepts an integer donor of ANOTHER
                width (no cast is needed: both are integers and C converts at the assignment).
                A pointer donee still needs its donor's exact type; the int<->pointer merges of
                func_818D4E68 and func_8180C3C0 (casts at every use) remain unbuilt.

CANDIDATES  every (inner pinned declaration, enclosing local of the same type not named in the
            block) pair, rename only and rename-plus-erase of the block's pins on the merged name,
            and the joint form that merges all of one donor's donees at once (the four blocks of
            func_8180C3C0 fall together).  Screened against the pinned text's cc1 listing; only
            listing-exact candidates (plus two nearest) reach the byte verifier.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
from xform.t29_addrsym import mask_comments
from xform.t36_paramwidth import functions
import xform.screen as screen

MAX_DONEES = 8
MAX_DONORS = 8
MAX_CROSS_DONORS = 6                               # donors of ANOTHER integer width, ranked after
SCAN_DONEES = 40
MAX_LISTINGS = 320
MAX_VERIFY = 6

NOT_TYPES = {"return", "else", "goto", "case", "do", "if", "while", "for", "switch", "sizeof",
             "default", "break", "continue", "typedef"}
INT_TYPES = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "long", "short", "char",
             "unsigned", "signed", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32"}
DECL_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<reg>register[ \t]+)?"
                     r"(?P<ty>(?:(?:unsigned|signed|const|volatile|struct|union)[ \t]+)*[A-Za-z_]\w*"
                     r"(?:[ \t]+long)?)[ \t]*(?P<p>\**)[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*"
                     r"(?P<pin>ASM_REG\([^)]*\))?[ \t]*(?:=[ \t]*(?P<init>[^;]+))?;[ \t]*$")


def _decl(line):
    m = DECL_RE.match(line)
    if not m or m.group("ty") in NOT_TYPES or m.group("v") in NOT_TYPES:
        return None
    # a declaration separates its type from its name (`s32 v;`); without that the regex also
    # matches an ASSIGNMENT (`fall_duration = 0x10;` as ty `fall_duratio` + name `n`)
    if not m.group("p") and m.end("ty") == m.start("v"):
        return None
    if re.match(r"^[ \t]*(?:%s)\b" % "|".join(NOT_TYPES), line):
        return None
    return m


def _block_of(masked, pos):
    """(open, close) offsets of the innermost brace block holding `pos`."""
    depth, stack = 0, []
    for i, c in enumerate(masked[:pos]):
        if c == "{":
            stack.append(i)
        elif c == "}" and stack:
            stack.pop()
    if not stack:
        return None
    open_at = stack[-1]
    depth = 0
    for i in range(open_at, len(masked)):
        if masked[i] == "{":
            depth += 1
        elif masked[i] == "}":
            depth -= 1
            if depth == 0:
                return open_at, i
    return None


def donees(text):
    """[{'v','ty','ptr','line','block','init','ind'}] - pinned register declarations in a NESTED block."""
    masked = mask_comments(text)
    lines = masked.split("\n")
    starts = [0]
    for l in lines:
        starts.append(starts[-1] + len(l) + 1)
    out, pins = [], sites_of(text)
    for fi, (fname, params, b0, b1) in enumerate(functions(text)):
        body = (masked.count("\n", 0, b0), masked.count("\n", 0, b1))
        top = _block_of(masked, b0 + 1)
        for i in range(body[0], min(body[1] + 1, len(lines))):
            m = _decl(lines[i])
            if not m:
                continue
            blk = _block_of(masked, starts[i] + len(m.group("ind")))
            if blk is None or top is None or blk == top:
                continue                           # a function-level declaration is t90's merge
            mirror = False
            if not m.group("pin"):
                # the pin is a KEEP STATEMENT in the same block, not the declaration itself
                v = m.group("v")
                if not any(blk[0] <= s[3] <= blk[1] and s[0] != "reg"
                           and v in [a.strip() for a in (s[2] or "").split(",")] for s in pins):
                    # ... or the pin is on the DONOR, not on this declaration at all (the MIRROR
                    # direction of the merge: dungeon/func_80084084's arm-local `register Entry
                    # *entry;` merged into the function's pinned `entry_m`).  Only paired with a
                    # PINNED donor, in donors() below.
                    if not any(b0 < s[3] < b1 for s in pins):
                        continue
                    mirror = True
            out.append({"v": m.group("v"), "ty": m.group("ty"), "ptr": len(m.group("p")),
                        "line": i, "block": blk, "init": (m.group("init") or "").strip(),
                        "ind": m.group("ind"), "fn": (b0, b1), "fi": fi,
                        "reg": bool(m.group("pin")), "mirror": mirror})
    # the declaration-borne ASM_REG donees first: they are the population this generator was
    # measured on, and a row's donee budget (MAX_DONEES) must not be spent on the new plain ones
    out.sort(key=lambda d: (d["mirror"], not d["reg"], d["line"]))
    return out[:SCAN_DONEES]


def donors(text, d):
    """Locals of the donee's type declared OUTSIDE its block and not named inside it."""
    masked = mask_comments(text)
    lines = masked.split("\n")
    starts = [0]
    for l in lines:
        starts.append(starts[-1] + len(l) + 1)
    inside = masked[d["block"][0]:d["block"][1]]
    out = []
    for i in range(masked.count("\n", 0, d["fn"][0]), min(masked.count("\n", 0, d["fn"][1]) + 1, len(lines))):
        m = _decl(lines[i])
        if not m or m.group("v") == d["v"]:
            continue
        if len(m.group("p")) != d["ptr"]:
            continue
        same = m.group("ty") == d["ty"]
        if not same and not (d["ptr"] == 0 and m.group("ty") in INT_TYPES and d["ty"] in INT_TYPES):
            continue                               # a pointer donee needs its donor's exact type
        at = starts[i]
        if d["block"][0] <= at <= d["block"][1]:
            continue                               # declared inside the donee's own block
        if re.search(r"\b%s\b" % re.escape(m.group("v")), inside):
            continue                               # alive in the block: not a merge, a clash
        if m.group("init"):
            continue                               # a declaration initialiser fixes its first value
        if d.get("mirror") and not _pinned(text, m.group("v"), d["fn"]):
            continue                               # nothing would be freed by this merge
        out.append(((0 if same else 1, abs(i - d["line"])), m.group("v")))
    # a donor of the donee's own type first, then the nearest declaration: the donor retail shared
    # the pseudo with is usually the one declared in the same group, and the menu is capped
    seen, ranked, cross = set(), [], []
    for (cls, _dist), v in sorted(out):
        if v in seen:
            continue
        seen.add(v)
        (ranked if cls == 0 else cross).append(v)
    return ranked[:MAX_DONORS] + cross[:MAX_CROSS_DONORS]


def _pinned(text, name, fn):
    """Does a pin site inside the function span `fn` name `name`?"""
    rx = re.compile(r"\b%s\b" % re.escape(name))
    return any(fn[0] < s[3] < fn[1] and rx.search(text[s[3]:s[4]]) for s in sites_of(text))


def _fn_pins(text, fi, donor):
    """Pin sites of the fi-th function of `text` that name `donor`."""
    fns = functions(text)
    if fi >= len(fns):
        return []
    _n, _p, b0, b1 = fns[fi]
    rx = re.compile(r"\b%s\b" % re.escape(donor))
    return [s for s in sites_of(text) if b0 < s[3] < b1 and rx.search(text[s[3]:s[4]])]


def _prologue(lines, first, last):
    """Indices of the declaration lines opening a block (blank lines allowed between)."""
    out, i = [], first
    while i <= last:
        s = lines[i].strip()
        if not s:
            i += 1; continue
        if _decl(lines[i]) is None:
            break
        out.append(i); i += 1
    return out


def merge(text, ds, donor):
    """Every donee in `ds` (one block each) renamed to `donor`, its declaration gone."""
    masked = mask_comments(text)
    lines, mlines = text.split("\n"), masked.split("\n")
    edits = {}                                     # line index -> replacement lines
    for d in sorted(ds, key=lambda d: -d["line"]):
        b0, b1 = d["block"]
        first = masked.count("\n", 0, b0) + 1
        last = masked.count("\n", 0, b1)
        pro = _prologue(mlines, first, last)
        if d["line"] not in pro:
            return None                            # not the block's own declaration prologue
        body = []
        if d["init"]:
            # keep program order: every initialiser of the prologue becomes an assignment, in order
            for i in pro:
                m = _decl(mlines[i])
                if i == d["line"]:
                    body.append("%s%s = %s;" % (d["ind"], donor, d["init"]))
                elif m.group("init"):
                    body.append("%s%s = %s;" % (m.group("ind"), m.group("v"), m.group("init").strip()))
            head = []
            for i in pro:
                m = _decl(mlines[i])
                if i == d["line"]:
                    continue
                head.append("%s%s%s %s%s;" % (m.group("ind"), m.group("reg") or "", m.group("ty"),
                                              m.group("p"), m.group("v"))
                            if m.group("init") else lines[i])
            edits[pro[0]] = (pro[-1], head + body)
        else:
            edits[d["line"]] = (d["line"], [])
        # rename the uses inside the block (the declaration's own line is handled above)
        for i in range(first, last + 1):
            if i in (x for x in pro if x == d["line"]):
                continue
            if re.search(r"\b%s\b" % re.escape(d["v"]), mlines[i]):
                lines[i] = re.sub(r"\b%s\b" % re.escape(d["v"]), donor, lines[i])
    for at in sorted(edits, reverse=True):
        end, rep = edits[at]
        lines = lines[:at] + rep + lines[end + 1:]
    return "\n".join(lines)


def candidates(text):
    """[(label, new_text)] - each (donee, donor) pair, alone and jointly per donor."""
    out, seen, sig = [], {text}, unscored_text(text)
    ds, pairs, taken = donees(text), {}, 0
    for d in ds:
        ds_donors = donors(text, d)
        if not ds_donors:
            continue                               # nothing of its type is free over the block
        taken += 1
        if taken > MAX_DONEES:
            break
        for v in ds_donors:
            pairs.setdefault((d["v"], v, d["ty"], d["ptr"]), []).append(d)
    # ... and one joint candidate per DONOR across donee names: func_8180C3C0 merges
    # `source_object`, `object` and `child` into `object_m` in three different blocks, which no
    # per-name group would ever put together
    per_donor = {}
    for (name, donor, ty, ptr), group in pairs.items():
        per_donor.setdefault((donor, ty, ptr), [])
        for d in group:
            if d not in per_donor[(donor, ty, ptr)]:
                per_donor[(donor, ty, ptr)].append(d)
    for (donor, ty, ptr), group in per_donor.items():
        if len({d["v"] for d in group}) > 1:
            pairs[("all", donor, ty, ptr)] = group
    for (name, donor, _, _), group in pairs.items():
        for chosen in ([] if name == "all" else [[d] for d in group]) + ([group] if len(group) > 1 else []):
            new = merge(text, chosen, donor)
            if new is None:
                continue
            label = "%s->%s@%s" % (name, donor,
                                   chosen[0]["line"] + 1 if len(chosen) == 1 else "x%d" % len(chosen))
            plans = [("rename", new)]
            left = [s for s in sites_of(new)
                    if s[2] == donor and any(d["block"][0] <= s[3] <= d["block"][1] for d in chosen)]
            if left:
                plans.append(("erase", erase_many(new, left, clean_notes=True)))
            wide = _fn_pins(new, chosen[0]["fi"], donor)
            if wide and wide != left:
                plans.append(("erase-fn", erase_many(new, wide, clean_notes=True)))
            for tag, cand in plans:
                if cand in seen or unscored_text(cand) != sig:
                    continue
                if len(sites_of(cand)) >= len(sites_of(text)):
                    continue
                seen.add(cand)
                out.append(("%s:%s" % (label, tag), cand))
    return out


class T:
    name = "t93_scopemerge"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        ds = donees(text)
        if not ds:
            return "no pinned register declaration in a nested block"
        return None if any(donors(text, d) for d in ds) else "no enclosing local free over the block"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "donees": len(donees(text))}
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
