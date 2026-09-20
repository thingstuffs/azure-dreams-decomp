"""T85: a function-wide callee-saved register role swap resolved as an allocno ORDER question.

APPEARS     `register void *entity_data ASM_REG("$19")` / `register s32 attempt ASM_REG("$18")`
            (dungeon/func_8009AB4C) and `register s32 table_index ASM_REG("$16")` + `ASM_KEEP`
            (town/func_800AC3CC): erasing the pins keeps every opcode and PERMUTES two or more
            callee-saved registers from prologue to epilogue.  The population is recognised from the
            `cc1 -dl -dg` dumps, not the text (round-61 study, work/native_lane/r61_alloc_study/NOTE.md):
            the pin-erased build must have MORE allocnos than the pinned one, its dispositions must be
            a permutation of the pinned ones (the pins' own hard registers included), and every
            contested allocno must cross a call.  Rows where erasing only changes reference counts
            (func_8009DEFC) or where the contested registers are argument registers (func_8046C188)
            are a preference family, not this one, and are refused here.
RESOLVES    gcc 2.x global.c.  `register x asm("$19")` gives the decl a hard register, so x is not an
            allocno: erasing the pin ADDS one allocno and every lower-priority allocno slides one
            register down the callee-saved sequence (study rule R1).  `qsort (allocno_order, ...,
            allocno_compare)` (global.c:546) ranks by `floor_log2(n_refs)*n_refs/live_length*10000*size`
            descending, ties by allocno number = declaration order (R2/R3), and `find_reg` hands out
            $s0,$s1,$s2 ... strictly in that order for call-crossing values (R4), so for them THE
            REGISTER IS THE RANK and a two-register swap is exactly one inversion in the sort.
            Reordering independent statements moves no live_length at all (R6: 60 legal permutations
            of one prologue gave two distinct flow vectors), which is why the sol lanes' 10-20
            spellings per row all coalesced.  The levers that do move the key are (a) deleting a
            redundant copy of a formal into a local - the live range then starts at function entry
            (func_8009AB4C: 41 -> 80 insns, priority 5853 -> 3000, byte-exact), (b) splitting an
            over-used local that carries two meanings - n_refs falls and the range lengthens
            (func_800AC3CC: 8 refs/26 insns -> 5 refs/32 insns, 9230 -> 3125, byte-exact), and
            (d) narrowing or widening a scalar, which creates or removes a conversion pseudo.
CANDIDATES  (a) a local assigned only `x = p;` from a never-written formal of the same type: the copies
            and the declaration go, uses are renamed to the formal;  (b) a local or parameter with two
            or more whole-line assignments whose later values have disjoint uses: the tail is split
            into a second local declared after the first, in the original type and - when the region's
            assignments share one cast and its uses another - in the use's type with both casts
            dropped;  (d) the pinned variable, its source formal and the scalars around the pin
            retyped s32 <-> s16/u16 (t84_narrowparams' retype, prototype included).  Each lever text
            is taken with the row's pins erased jointly (and, when other pin kinds are present, with
            only the register pins erased).
            PRE-GATE: every candidate is compiled once with `-dl -dg` and run through
            tools/alloc_sim.py's `find_reg` model - exact on all 14 builds of the study - with the
            allocnos mapped back to C names by declaration order (R3); a candidate survives only if
            every name that retail's (pinned) build placed lands in the same register.  The same
            compile yields the normalised listing (alloc_sim.norm_asm == screen.compile_s's
            normalisation, the study's trust check), so the listing screen is free; `vf` is called on
            listing-exact candidates only (at most 6), and always on a listing-exact one even if the
            name mapping refused it.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import alloc_sim
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t84_narrowparams import retype
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t84_narrowparams import retype
    import screen

MAX_DUMPS = 40
MAX_VERIFY = 6
NEAR = 2            # listing distance still worth a byte score (probe.py's rule in the r61 study)
MAX_CANDS = 34
CALLEE = {"16", "17", "18", "19", "20", "21", "22", "23", "30",
          "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "fp"}
REGNO = {**{str(n): n for n in range(32)},
         **{"s%d" % i: 16 + i for i in range(8)}, **{"v0": 2, "v1": 3},
         **{"a%d" % i: 4 + i for i in range(4)}, **{"t%d" % i: 8 + i for i in range(8)},
         "fp": 30, "sp": 29, "ra": 31, "gp": 28, "at": 1}
KEYWORDS_STMT = {"return", "if", "while", "for", "switch", "else", "do", "goto"}
ASSIGN = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<e>.*);[ \t]*$")
WRITE = r"(?:\+\+|--)?[ \t]*\b%s\b[ \t]*(?:\+\+|--|[-+*/%%&|^]?=(?!=)|<<=|>>=)"


# ------------------------------------------------------------------------------- text inspection

def the_function(text):
    """(fname, params, body_start, body_end) when the file is one definition, else None."""
    fs = functions(text)
    return fs[0] if len(fs) == 1 else None


def pinned_vars(text):
    """[(name, regno, site)] for every `register T v ASM_REG("$r")` on a callee-saved register."""
    out = []
    for s in sites_of(text):
        if s[0] != "reg" or s[2] not in CALLEE:
            continue
        ids = re.findall(r"[A-Za-z_]\w*", s[6])
        if ids:
            out.append((ids[-1], REGNO.get(s[2], -1), s))
    return out


def body_lines(text):
    """(lines, masked_lines, first_body_line, last_body_line) for the single function."""
    f = the_function(text)
    if not f:
        return None
    masked = mask_comments(text)
    return (text.split("\n"), masked.split("\n"),
            masked.count("\n", 0, f[2]), masked.count("\n", 0, f[3]))


def assignments(mlines, lo, hi, v):
    """Line indices of whole-line assignments `v = ...;` in the body."""
    out = []
    for i in range(lo, hi + 1):
        m = ASSIGN.match(mlines[i])
        if m and m.group("v") == v:
            out.append(i)
    return out


def written_elsewhere(mlines, lo, hi, v, allow):
    """True when v is written other than on the `allow` lines (compound assign, ++/--, &v)."""
    pat = re.compile(WRITE % re.escape(v))
    for i in range(lo, hi + 1):
        if i in allow:
            continue
        ln = mlines[i]
        if pat.search(ln) or re.search(r"&[ \t]*\b%s\b" % re.escape(v), ln):
            return True
    return False


def decl_line_of(mlines, lo, hi, v):
    """Index of v's own declaration line (only when v is declared alone on it), else None."""
    for i in range(lo, hi + 1):
        m = alloc_sim.DECL_LINE.match(mlines[i])
        if not m or "," in m.group("body"):
            continue
        d = alloc_sim._declarators(m.group("body"))
        if len(d) == 1 and d[0][0] == v:
            return i
    return None


def init_line_of(mlines, lo, hi, v):
    """(line index, initialiser) when v is declared with a plain initialiser `T v = expr;`."""
    for i in range(lo, hi + 1):
        m = re.match(r"^[ \t]*(?P<head>[A-Za-z_][\w \t*]*?)\b%s[ \t]*=(?!=)[ \t]*(?P<e>[^;]+);[ \t]*$"
                     % re.escape(v), mlines[i])
        if m and m.group("head").split() and m.group("head").split()[0] not in KEYWORDS_STMT:
            return i, m.group("e").strip()
    return None


def decl_block(mlines, lo, hi):
    """Indices of the declaration lines of the function's top block."""
    out = []
    for i in range(lo + 1, hi + 1):
        s = mlines[i].strip()
        if not s:
            continue
        m = alloc_sim.DECL_LINE.match(mlines[i])
        if not m or not alloc_sim._declarators(m.group("body")):
            break
        out.append(i)
    return out


# ------------------------------------------------------------------------------------- the levers

def lever_a(text):
    """[(label, text)] with a redundant `x = formal;` copy deleted and its uses renamed."""
    f, bl = the_function(text), body_lines(text)
    if not f or not bl:
        return []
    lines, mlines, lo, hi = bl
    params = {p: t for p, t, _, _ in f[1]}
    out = []
    for name, ty, scalar in alloc_sim.locals_in_order(text, f[2], f[3]):
        if not scalar:
            continue
        asg = assignments(mlines, lo, hi, name)
        init = init_line_of(mlines, lo, hi, name)          # `T x = param;` - the copy IS the decl
        srcs = set()
        for i in asg:
            srcs.add(ASSIGN.match(mlines[i]).group("e").strip())
        if init is not None:
            srcs.add(init[1])
        if len(srcs) != 1:
            continue
        p = srcs.pop()
        if p not in params:
            continue
        dl = init[0] if init is not None else decl_line_of(mlines, lo, hi, name)
        if dl is None:
            continue
        # the local must spell the formal's own type: a narrower or wider copy converts
        dtoks = [x for x in re.findall(r"[A-Za-z_]\w*|\*", mlines[dl].split("=")[0].split(";")[0])
                 if x not in alloc_sim.QUALIFIERS]
        ptoks = [x for x in re.findall(r"[A-Za-z_]\w*|\*", params[p]) if x not in alloc_sim.QUALIFIERS]
        if dtoks[:-1] != ptoks or dtoks[-1] != name:
            continue
        if written_elsewhere(mlines, lo, hi, name, set(asg) | {dl}):
            continue
        if written_elsewhere(mlines, lo, hi, p, set()):
            continue
        keep = [ln for i, ln in enumerate(lines) if i not in set(asg) | {dl}]
        new = re.sub(r"\b%s\b" % re.escape(name), p, "\n".join(keep))
        out.append(("a:%s<-%s" % (name, p), new))
    return out


def cast_of(e):
    """The leading cast of an expression (`(void *)x` -> `void *`), else None."""
    m = re.match(r"^\(\s*([A-Za-z_][\w \t]*\**)\s*\)\s*(.+)$", e.strip())
    return (m.group(1).strip(), m.group(2).strip()) if m else None


def lever_b(text, near):
    """[(label, text)] splitting a multiply-assigned local/parameter into a second variable."""
    f, bl = the_function(text), body_lines(text)
    if not f or not bl:
        return []
    lines, mlines, lo, hi = bl
    params = {p: t for p, t, _, _ in f[1]}
    decls = decl_block(mlines, lo, hi)
    names = [(n, ty, sc) for n, ty, sc in alloc_sim.locals_in_order(text, f[2], f[3]) if sc]
    cands = [(n, " ".join(ty)) for n, ty, sc in names] + [(p, t) for p, t in params.items()]
    out = []
    for v, ty in sorted(cands, key=lambda c: -len(assignments(mlines, lo, hi, c[0]))):
        asg = assignments(mlines, lo, hi, v)
        if len(asg) < 2 or written_elsewhere(mlines, lo, hi, v, set(asg)):
            continue
        uses = [i for i in range(lo, hi + 1) if re.search(r"\b%s\b" % re.escape(v), mlines[i]) and i not in asg]
        for k in (0, 1):
            if k >= len(asg) - 0 or (k == 0 and v not in params):
                continue                              # a local needs a value before the split region
            region = asg[k:]
            if len(region) < 1 or any(region[0] < i <= region[-1] for i in uses):
                continue                              # a use between the region's assignments is ambiguous
            if k and not any(asg[k - 1] < i < region[0] for i in uses):
                continue                              # the kept assignment would reach the tail unread
            tail = [i for i in uses if i > region[-1]]
            if not tail:
                continue
            new_name = v + "_b"
            if re.search(r"\b%s\b" % re.escape(new_name), text):
                continue
            acasts = [cast_of(ASSIGN.match(mlines[i]).group("e")) for i in region]
            ucast = None
            if all(a for a in acasts) and len(set(a[0] for a in acasts)) == 1:
                cs = set()
                for i in tail:
                    cs |= set(re.findall(r"\(\s*([A-Za-z_][\w \t]*\**)\s*\)\s*%s\b" % re.escape(v), mlines[i]))
                    if len(re.findall(r"\b%s\b" % re.escape(v), mlines[i])) != len(re.findall(r"\(\s*[A-Za-z_][\w \t]*\**\s*\)\s*%s\b" % re.escape(v), mlines[i])):
                        cs = set()
                        break
                if len(cs) == 1:
                    ucast = cs.pop()
            forms = [("keep", ty, False)] + ([("cast", ucast, True)] if ucast else [])
            for fl, nty, strip in forms:
                ls = list(lines)
                for i in region:
                    m = ASSIGN.match(mlines[i])
                    e = m.group("e").strip()
                    if strip:
                        c = cast_of(e)
                        e = c[1] if c else e
                    ls[i] = "%s%s = %s;" % (m.group("ind"), new_name, e)
                for i in tail:
                    ls[i] = (re.sub(r"\(\s*%s\s*\)\s*%s\b" % (re.escape(nty), re.escape(v)), new_name, ls[i])
                             if strip else re.sub(r"\b%s\b" % re.escape(v), new_name, ls[i]))
                    if re.search(r"\b%s\b" % re.escape(v), ls[i]) and strip:
                        ls[i] = re.sub(r"\b%s\b" % re.escape(v), new_name, ls[i])
                if not decls:
                    continue
                base = nty.strip()
                decl = "%s%s %s%s;" % (re.match(r"[ \t]*", lines[decls[0]]).group(0),
                                       base.rstrip("* ").strip(), "*" * base.count("*"), new_name)
                for pl, at in (("last", decls[-1] + 1), ("prev", decls[-1])):
                    out.append(("b:%s@%d:%s:%s" % (v, k, fl, pl), "\n".join(ls[:at] + [decl] + ls[at:])))
    return out


def lever_d(text, near):
    """[(label, text)] with a scalar around the pin narrowed or widened."""
    f = the_function(text)
    if not f:
        return []
    bl = body_lines(text)
    lines, mlines, lo, hi = bl
    params = {p: t for p, t, _, _ in f[1]}
    pins = pinned_vars(text)
    want = []
    for name, _, s in pins:
        want.append(name)
        i = s[5] - 1
        for j in range(max(lo, i - 3), min(hi, i + 3) + 1):
            want += re.findall(r"[A-Za-z_]\w*", mlines[j])
    seen, out = set(), []
    for v in want:
        if v in seen:
            continue
        seen.add(v)
        cur = params.get(v)
        if cur is None:
            dl = decl_line_of(mlines, lo, hi, v)
            if dl is None:
                continue
            d = alloc_sim._declarators(alloc_sim.DECL_LINE.match(mlines[dl]).group("body"))
            if not d or d[0][2] or not (set(d[0][1]) & alloc_sim.SCALAR_WORDS):
                continue
            cur = " ".join(d[0][1])
            for ty in ("s16", "u16", "s32"):
                if ty == cur.split()[-1]:
                    continue
                out.append(("d:%s:%s->%s" % (v, cur, ty),
                            "\n".join(lines[:dl] + [re.sub(r"\b%s\b" % re.escape(cur), ty, lines[dl], count=1)] + lines[dl + 1:])))
        else:
            if "*" in cur or cur.split()[-1] not in ("s32", "u32", "s16", "u16"):
                continue
            for ty in ("s16", "u16", "s32"):
                if ty == cur.split()[-1]:
                    continue
                out.append(("d:param %s:%s->%s" % (v, cur, ty), retype(text, f[0], {v}, ty)))
        if len(out) >= 8:
            break
    return out


def erase_plans(text):
    """[(label, sites)] pin subsets to erase: everything, then the register pins alone."""
    s = sites_of(text)
    plans = [("all", s)]
    regs = [x for x in s if x[0] == "reg"]
    if regs and len(regs) != len(s):
        keep = [x for x in s if x[0] != "reg" and any(re.search(r"\b%s\b" % re.escape(n), x[2] or "")
                                                      for n, _, _ in pinned_vars(text))]
        plans.append(("regs", regs + keep))
    return plans


def candidates(text):
    """[(label, candidate text)] - lever texts with the pins erased, levers a, b, d in that order."""
    near = [s[5] - 1 for s in sites_of(text)]
    out, seen = [], set()
    er = erase_many(text, sites_of(text), clean_notes=True)
    bases = [("", text)] + ([("E:", er)] if er != text else [])
    levers = []
    for lv in (lever_a, lever_b, lever_d):
        for tag, base in bases:
            args = (base,) if lv is lever_a else (base, near)
            levers += [(tag + label, t) for label, t in lv(*args)]
    for label, t in levers:
        plans = erase_plans(t) if sites_of(t) else [("none", None)]
        for pl, sites in plans:
            if sites is not None and not sites:
                continue
            cand = erase_many(t, sites, clean_notes=True) if sites else t
            if len(sites_of(cand)) >= len(sites_of(text)):
                continue
            if cand in seen:
                continue
            seen.add(cand)
            out.append(("%s/%s" % (label, pl), cand))
            if len(out) >= MAX_CANDS:
                return out
    return out


# ------------------------------------------------------------------------- the simulator pre-gate

def name_targets(text, rd):
    """{name: hard register} retail's (pinned) build places, or None when the mapping is unsafe."""
    dm = alloc_sim.decl_pseudos(text, rd["first"])
    if not dm:
        return None
    inv = {p: n for n, p in dm["map"].items()}
    out = {}
    for name, regno, _ in pinned_vars(text):
        if name not in dm["map"] or dm["map"][name] in rd["order"]:
            return None                                # a pinned decl must NOT be an allocno
        out[name] = regno
    for p in rd["order"]:
        if p in inv and rd["disp"].get(p, -1) >= 0:
            out[inv[p]] = rd["disp"][p]
    return out


def name_dispositions(text, rd, disp):
    """{name: hard register} for a candidate's simulated dispositions, or None when unmappable."""
    dm = alloc_sim.decl_pseudos(text, rd["first"])
    if not dm:
        return None
    inv = {p: n for n, p in dm["map"].items()}
    return {inv[p]: r for p, r in disp.items() if p in inv and r >= 0}


def is_order_site(rd_p, rd_e, pins):
    """The study's APPEARS test, read off the two dumps.  (ok, why)"""
    op, oe = rd_p["order"], rd_e["order"]
    if not (0 < len(oe) - len(op) <= max(1, len(pins))):
        return False, "erased allocno count %d vs %d - not a missing-allocno site" % (len(oe), len(op))
    regs_p = sorted([rd_p["disp"].get(p, -1) for p in op] + [r for _, r, _ in pins])
    regs_e = sorted([rd_e["disp"].get(p, -1) for p in oe])
    if regs_p != regs_e:
        return False, "dispositions are not a permutation (%s vs %s)" % (regs_p, regs_e)
    contested = [p for p in op if p in oe and rd_p["disp"].get(p) != rd_e["disp"].get(p)]
    if not contested:
        return False, "no allocno changes register when the pins are erased"
    bad = [p for p in contested if not rd_e["stats"].get(p, {}).get("calls_crossed", 0)]
    if bad:
        return False, "contested allocnos %s cross no call - a preference site, not an order site" % bad
    return True, ""


def ldist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t85_allocorder"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        from common import parse_cfg
        if parse_cfg(row["cfg"])[0] not in alloc_sim.FIRST:
            return "cell has no FIRST_PSEUDO_REGISTER in the model"
        if not the_function(text):
            return "not a single function definition"
        pins = pinned_vars(text)
        if not pins:
            return "no callee-saved ASM_REG pin"
        f = the_function(text)
        names = {n for n, _, sc in alloc_sim.locals_in_order(text, f[2], f[3]) if sc} | {p for p, _, _, _ in f[1]}
        if not (names & {n for n, _, _ in pins}):
            return "the pinned register is not on a declared scalar"
        return None if candidates(text) else "no (a)/(b)/(d) lever candidate near the pin"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "dumps": 0, "gate_ok": 0, "gate_no": 0,
                "gate_unmapped": 0, "noop": 0, "tried": 0}
        target_listing = screen.compile_s(row, text)
        if target_listing is None:
            return None, dict(info, refused="pinned text does not build to a listing")
        rd_p = alloc_sim.read(row, text)
        info["dumps"] += 1
        if rd_p is None or rd_p["listing"] != target_listing:
            return None, dict(info, refused="untrusted dump reading (dumped listing != plain compile)")
        pins = pinned_vars(text)
        rd_e, why = None, "pin-erased text does not build"
        for pl, sites in erase_plans(text):
            rd = alloc_sim.read(row, erase_many(text, sites, clean_notes=True))
            info["dumps"] += 1
            if rd is None:
                continue
            ok, why = is_order_site(rd_p, rd, pins)
            if ok:
                rd_e, info["erasure"] = rd, pl
                break
        if rd_e is None:
            return None, dict(info, refused=why)
        target = name_targets(text, rd_p)
        if target is None:
            info["mapping"] = "unsafe"
        best, best_label, exacts = None, None, []
        for label, cand in candidates(text):
            if info["dumps"] >= MAX_DUMPS:
                info["cut"] = "dump budget"
                break
            rd = alloc_sim.read(row, cand)
            info["dumps"] += 1
            if rd is None:
                continue
            if alloc_sim.flow_vector(rd) == alloc_sim.flow_vector(rd_e):
                info["noop"] += 1                      # R6: the lever moved no allocator input
            verdict = "unmapped"
            if target is not None:
                pred = name_dispositions(cand, rd, alloc_sim.simulate(rd))
                if pred is None:
                    verdict = "unmapped"
                else:
                    common = [n for n in target if n in pred]
                    verdict = "ok" if common and all(pred[n] == target[n] for n in common) else "no"
            info["gate_" + {"ok": "ok", "no": "no", "unmapped": "unmapped"}[verdict]] += 1
            d = ldist(target_listing, rd["listing"])
            if best is None or d < best:
                best, best_label = d, label
            if d <= NEAR:                              # the listing screen is a heuristic, not a proof
                exacts.append((d, verdict != "ok", label, cand))
            elif verdict == "ok":
                info.setdefault("gate_ok_nonexact", []).append("%s d=%d" % (label, d))
        info["best"] = best
        info["best_label"] = best_label
        for d, late, label, cand in sorted(exacts):
            if info["tried"] >= MAX_VERIFY:
                break
            info["tried"] += 1
            if late and d == 0:
                info["gate_missed_exact"] = label       # the name mapping would have refused a winner
            if vf(cand).get("exact"):
                return cand, dict(info, step=label, listing_d=d, gate="no" if late else "ok",
                                  pins_out=len(sites_of(cand)))
        return None, info
