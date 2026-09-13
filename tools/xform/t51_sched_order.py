"""T51: current-text compiler-guided ordering and producer-lifetime experiments.

APPEARS: a live pin changes an optimized instruction order or producer.
RESOLVES: preserve unrelated constraints, expose surviving statement/expression
order or a single-set producer, and require vf(candidate)['exact'].

Fixed defaults: 256 compiler observations, 24 vf calls, 4 erased bases, 6
meaningful statement positions, 2 improving search steps. No atlas or row-name
lookup, flag mutation, added asm/volatile, or persistent/cache-file writes.
The trace helper reports evidence; it does not prove arbitrary C unreachable.

Built by the sched_astra lane (work/native_lane/sched_astra/REPORT.md, 2026-09-13): gcc 2.x schedules
backward with dynamic priorities (a single-set live producer is promoted), dependence class, then LUID
over the RTL that survives CSE/combine; an empty volatile asm is a full register+memory dependency cut.
Frozen held-out result: fence-lane rows 6/165 (7 pins, 0 ASM_SCHED_BARRIER), atlas order rows 4/60 (6 pins).
First full sweep (2026-09-13, the other 1,297 eligible rows, 55 min at 12 workers): 61 rows, 79 pins,
2 ASM_SCHED_BARRIER; by lever: move 28, single-set lifetime split 27, fuse 5, commute 1.
Split lifetimes are named <var>_2 (the lane named them t51_<var>; names do not change codegen).
"""
import collections
import os
from pathlib import Path
import re
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of, unscored_text, arm_labels, asm_blocker
from pin_sites import erase_many
from xform.t12_stmtorder import mask, depths, is_decl, movable
try:
    from .sched_trace import compile_text, distance, diagnose
except ImportError:
    from sched_trace import compile_text, distance, diagnose

COMPILER_BUDGET = int(os.getenv("T51_COMPILERS", "256"))
VERIFY_BUDGET = int(os.getenv("T51_VERIFY", "24"))
BASES = 4
SHIFT = 6
ID = r"[A-Za-z_]\w*"
ASSIGN = re.compile(r"^\s*(?P<lhs>.*?)\s*(?<![=!<>+*/%&|^\-])=(?!=)\s*(?P<rhs>.*?)\s*;\s*$", re.S)
IDENTS = re.compile(ID)
CALL = re.compile(r"\b(?!sizeof\b)(?:func_[A-Fa-f0-9]+|[A-Za-z_]\w*)\s*\(")
CONTROL = re.compile(r"\b(if|else|for|while|return|goto|case|switch|break|continue)\b")


def declarations(text):
    """Ordinary scalar/pointer locals, with an optional retained register pin."""
    out = {}
    pat = re.compile(r"^(?P<indent>[ \t]+)(?:register\s+)?(?P<type>(?:(?:unsigned|signed|const|struct)\s+)?" +
                     ID + r"[ \t]+(?:\*[ \t]*)*)(?P<var>" + ID + r")\s*(?:ASM_REG\([^\n;]*\))?\s*(?:=[^;\n]*)?;", re.M)
    for m in pat.finditer(text):
        if m["type"].strip() not in ("return", "goto", "extern"):
            out[m["var"]] = {"type": m["type"].strip(), "start": m.start(), "end": m.end(), "indent": m["indent"]}
    return out


def units(text):
    """Physical-line records; blank/comments do not count as statement slots.

    Multiline expressions are handled by fusion/substitution only when their
    complete statement occupies one line. This explicit boundary is reported.
    """
    lines = text.splitlines(True)
    ml = mask(text).splitlines(True)
    ds = depths(ml)
    labels = arm_labels(text)
    records = []
    for i, s in enumerate(ml):
        if not s.strip():
            continue
        ok = ds[i] > 0 and movable(s) and not CONTROL.search(s) and not s.lstrip().startswith("ASM_")
        records.append({"line": i, "depth": ds[i], "masked": s, "simple": ok,
                        "decl": is_decl(s), "arm": labels[i]})
    return lines, records


def access(s):
    m = ASSIGN.match(s)
    if not m:
        ids = set(IDENTS.findall(s))
        return ids, ids, True
    lhs, rhs = m["lhs"].strip(), m["rhs"]
    if re.fullmatch(ID, lhs):
        return {lhs}, set(IDENTS.findall(rhs)), False
    # Lvalue roots are read addresses, not assignments to the pointer itself.
    # Alias ordering is conservative below: memory writes do not cross each other.
    return set(), set(IDENTS.findall(lhs + " " + rhs)), True


def independent(a, b):
    wa, ra, ma = access(a)
    wb, rb, mb = access(b)
    return not (wa & (rb | wb) or wb & ra or (ma and mb))


def binary_swaps(expr):
    """Whole-expression commutations, keeping the original parse grouping."""
    s = expr.strip()
    depth = 0
    ops = []
    for i, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif depth == 0 and c in "+*|&^":
            if i == 0 or s[i - 1] in "+-*/%&|^=!<>" or s[i + 1:i + 2] in (c, "="):
                continue
            ops.append((i, c))
    if not ops:
        return
    prec = {"|": 1, "^": 2, "&": 3, "+": 4, "*": 5}
    i, op = min(ops, key=lambda x: (prec[x[1]], -x[0]))
    a, b = s[:i].strip(), s[i + 1:].strip()
    if not a or not b or re.search(r"\+\+|--|(?<![=!<>])=(?!=)|\?|,", s) or CALL.search(s):
        return
    yield "(" + b + ") " + op + " (" + a + ")"


def later_dead(masked, var):
    """No read of local var before its next plain overwrite, or end of scope.

    Callers also restrict the edited lifetime to a straight-line block and
    reject address-taking. This is a pruning guard; vf still proves output.
    """
    m = re.search(r"\b" + re.escape(var) + r"\b", masked)
    if m is None:
        return True
    line = masked[m.start():].split(";", 1)[0]
    a = ASSIGN.match(line + ";")
    return bool(a and a["lhs"].strip() == var and not re.search(r"\b" + re.escape(var) + r"\b", a["rhs"]))


def candidates(text, focus_line, focus_var=None):
    """Yield mechanism-bearing rewrites, closest to the removed pin first."""
    lines, recs = units(text)
    decl = declarations(text)
    masked = mask(text)
    positions, off = [], 0
    for line in lines:
        positions.append(off)
        off += len(line)
    ranked = sorted(enumerate(recs), key=lambda z: (
        0 if focus_var and re.search(r"\b" + re.escape(focus_var) + r"\b", z[1]["masked"]) else 1,
        abs(z[1]["line"] - focus_line), z[1]["line"]))
    # First try producer lifetime/fusion and expression ordering.
    for ri, r in ranked:
        i, s = r["line"], r["masked"]
        if not r["simple"] or r["arm"] in ("port", "dead"):
            continue
        a = ASSIGN.match(s)
        if not a:
            continue
        lhs, rhs = a["lhs"].strip(), a["rhs"].strip()
        ind = re.match(r"\s*", lines[i])[0]
        for expr in binary_swaps(rhs):
            out = lines[:]
            out[i] = ind + lhs + " = " + expr + ";\n"
            yield "commute:%d" % (i + 1), "".join(out)
        if lhs not in decl or CALL.search(rhs) or "volatile" in rhs or re.search(r"\+\+|--", rhs):
            continue
        var = lhs
        if re.search(r"&\s*\b" + re.escape(var) + r"\b", masked):
            continue
        # Inline an otherwise dead producer into its next statement's sole use.
        if ri + 1 < len(recs):
            nxt = recs[ri + 1]
            j = nxt["line"]
            if nxt["simple"] and not nxt["decl"] and nxt["depth"] == r["depth"] and nxt["arm"] == r["arm"]:
                n = nxt["masked"]
                uses = list(re.finditer(r"\b" + re.escape(var) + r"\b", n))
                na = ASSIGN.match(n)
                if (len(uses) == 1 and na and uses[0].start() >= na.start("rhs") and
                        later_dead("".join(mask(x) for x in lines[j + 1:]), var)):
                    ty = decl[var]["type"]
                    # an rhs that is exactly the local's own cast of one simple operand is not cast twice
                    # (`(T)&sym`, `(T)p->f`); `(T)a * 2` casts only `a`, so it keeps the outer cast
                    already = re.fullmatch(r"\(\s*" + re.escape(ty).replace(r"\ ", r"\s*") +
                                           r"\s*\)\s*[&*]?\s*[A-Za-z_]\w*(?:(?:->|\.)\w+|\[[^\[\]]*\])*", rhs)
                    replacement = "(" + rhs + ")" if already else "((" + ty + ")(" + rhs + "))"
                    out = lines[:]
                    out[i] = ""
                    out[j] = re.sub(r"\b" + re.escape(var) + r"\b", lambda _: replacement, lines[j])
                    yield "fuse:%s:%d" % (var, i + 1), "".join(out)
        # Give a repeatedly set local one ordinary single-set lifetime. All uses
        # must be in a straight-line region and end before its next overwrite.
        end = ri + 1
        use_count = 0
        while end < len(recs) and end - ri <= 10:
            z = recs[end]
            if not z["simple"] or z["depth"] != r["depth"] or z["arm"] != r["arm"] or z["decl"]:
                break
            aa = ASSIGN.match(z["masked"])
            if aa and aa["lhs"].strip() == var:
                break
            use_count += len(re.findall(r"\b" + re.escape(var) + r"\b", z["masked"]))
            end += 1
        if use_count and end > ri + 1:
            after = recs[end]["line"] if end < len(recs) else len(lines)
            if later_dead(mask("".join(lines[after:])), var):
                name = var + "_2"
                if re.search(r"\b" + re.escape(name) + r"\b", text):
                    continue
                out = lines[:]
                for j in range(i, after):
                    out[j] = re.sub(r"\b" + re.escape(var) + r"\b", name, out[j])
                new = "".join(out)
                dp = decl[var]
                # After the declaration's whole line: its trailing comment (often a pin note) stays on it
                eol = new.find("\n", dp["end"])
                eol = len(new) if eol < 0 else eol + 1
                sep = "" if dp["type"].endswith("*") else " "      # `u8 *x_2`, not `u8 * x_2`
                new = new[:eol] + dp["indent"] + dp["type"] + sep + name + ";\n" + new[eol:]
                yield "single-set:%s:%d" % (var, i + 1), new

    # Move complete statements over up to six meaningful siblings. Comments
    # and blank lines stay in place; preprocessor/control boundaries are hard.
    for shift in range(1, SHIFT + 1):
        for ri, r in ranked:
            if not r["simple"] or r["decl"] or r["arm"] in ("port", "dead"):
                continue
            for direction in (-1, 1):
                rj = ri + direction * shift
                if not 0 <= rj < len(recs):
                    continue
                span = recs[min(ri, rj):max(ri, rj) + 1]
                if any(not x["simple"] or x["decl"] or x["depth"] != r["depth"] or
                       x["arm"] != r["arm"] for x in span):
                    continue
                if not all(independent(r["masked"], z["masked"]) for z in span if z is not r):
                    continue
                idx = [x["line"] for x in span]
                values = [lines[k] for k in idx]
                moving = values.pop(0 if direction == 1 else -1)
                values.insert(len(values) if direction == 1 else 0, moving)
                out = lines[:]
                for k, val in zip(idx, values):
                    out[k] = val
                yield "move:%d:%d" % (r["line"] + 1, recs[rj]["line"] + 1), "".join(out)

    # The declaration's 'register' hint changes allocation preferences without
    # constraining a hardware register. Test the erased REG's current variable.
    if focus_var in decl:
        d = decl[focus_var]
        segment = text[d["start"]:d["end"]]
        if "ASM_" not in segment and "register" not in segment:
            yield "register-hint:" + focus_var, text[:d["start"]] + d["indent"] + "register " + segment.lstrip() + text[d["end"]:]


class T:
    name = "t51_sched_order"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no live pins"
        why = asm_blocker(text)
        if why:
            return why
        if not row.get("cfg"):
            return "missing compiler recipe"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        pins = sites_of(text)
        usig = unscored_text(text)
        observations, scores, seen = {}, {}, set()
        nc = nv = 0
        log = {"pins_in": len(pins), "compiler_budget": COMPILER_BUDGET, "vf_budget": VERIFY_BUDGET,
               "steps": [], "diagnostics": [], "erasures": [], "screen_failures": 0}

        def observe(cand, dumps=False):
            nonlocal nc
            key = (sha_text(cand), dumps)
            if key not in observations:
                if nc >= COMPILER_BUDGET:
                    return None
                nc += 1
                observations[key] = compile_text(row, cand, dumps=dumps)
                if observations[key]["assembly"] is None:
                    log["screen_failures"] += 1
            return observations[key]

        def score(cand):
            nonlocal nv
            key = sha_text(cand)
            if key not in scores:
                if nv >= VERIFY_BUDGET:
                    return {"exact": False, "status": "budget"}
                nv += 1
                scores[key] = vf(cand)
            return scores[key]

        def allowed(cand):
            return len(sites_of(cand)) < len(pins) and unscored_text(cand) == usig

        target = observe(text, True)
        if target is None or target["assembly"] is None:
            return None, dict(log, error="baseline compiler failure", compiles=nc, tried=nv)
        baselines = []
        # All single-site erasures in a fixed budget, plus the joint fence set.
        order = sorted(enumerate(pins), key=lambda z: (z[1][1] != "ASM_SCHED_BARRIER", z[0]))
        for index, site in order[:40]:
            cand = erase_many(text, [site], clean_notes=True)
            if not allowed(cand):
                continue
            ob = observe(cand)
            if ob is None or ob["assembly"] is None:
                continue
            dist = distance(target["assembly"], ob["assembly"])
            var = site[6].split()[-1].lstrip("*") if site[0] == "reg" and site[6] else None
            log["erasures"].append({"site": index, "macro": site[1], "asm_distance": dist})
            baselines.append((dist, index, cand, site[5] - 1, var))
        fences = [s for s in pins if s[1] == "ASM_SCHED_BARRIER"]
        if len(fences) > 1:
            cand = erase_many(text, fences, clean_notes=True)
            if allowed(cand):
                ob = observe(cand)
                if ob and ob["assembly"] is not None:
                    baselines.append((distance(target["assembly"], ob["assembly"]), -1, cand, fences[0][5] - 1, None))
        baselines.sort(key=lambda x: (x[0], x[1]))
        best = None
        for dist, index, cand, line, var in baselines:
            if dist == 0 and score(cand).get("exact"):
                best = cand
                log["steps"].append("erase:%d" % index)
                break

        # Retain four nearest erasures, prioritizing their own source region.
        # Within each base a one-step strict assembly improvement may seed a
        # second pass. Assembly equality is scored immediately, never accepted.
        for dist, index, base, line, var in baselines[:BASES] if best is None else []:
            trace = observe(base, True)
            if trace:
                log["diagnostics"].append({"site": index, **diagnose(target, trace)})
            shortlist = []
            per_base = max(8, (COMPILER_BUDGET - nc) // max(1, BASES - len(log["diagnostics"]) + 1))
            start = nc
            for depth in range(2):
                improved = None
                menu = list(candidates(base, line, var))
                # Use observed scheduler decisions to choose the first lever.
                # Equal-rank candidates favor emission order; priority changes
                # favor ordinary producer formation. Location remains primary.
                ds = log["diagnostics"][-1] if log["diagnostics"] else {}
                dynamic = any(p.get("after_decision", {}).get("cause") == "dynamic-priority"
                              for ph in ds.get("phases", {}).values() for p in ph.get("inversions", []))
                preference = {k: n for n, k in enumerate(
                    ("single-set", "fuse", "move", "commute", "register-hint") if dynamic else
                    ("move", "fuse", "single-set", "commute", "register-hint"))}
                def rank(item):
                    tag = item[0]
                    nums = [int(x) for x in tag.split(":")[1:] if x.isdigit()]
                    gap = min((abs(x - line - 1) for x in nums), default=0)
                    return (gap // 10, preference.get(tag.split(":")[0], 9), gap, tag)
                menu.sort(key=rank)
                for tag, cand in menu:
                    h = sha_text(cand)
                    if h in seen or not allowed(cand):
                        continue
                    seen.add(h)
                    ob = observe(cand)
                    if ob is None:
                        break
                    d = distance(target["assembly"], ob["assembly"])
                    if ob["assembly"] is not None:
                        shortlist.append((d, tag, cand))
                        if d < dist and (improved is None or d < improved[0]):
                            improved = (d, tag, cand)
                        if d == 0 and score(cand).get("exact"):
                            best = cand
                            log["steps"].append("erase:%d+%s" % (index, tag))
                            break
                    if nc - start >= per_base or nv >= VERIFY_BUDGET:
                        break
                if best is not None or nc - start >= per_base or improved is None:
                    break
                dist, tag, base = improved
                log["steps"].append("screen-improvement:%s:%d" % (tag, dist))
            # Explicit fallback measures nonzero assembly differences, which
            # can converge after assembler/delay-slot scheduling.
            for d, tag, cand in sorted(shortlist, key=lambda z: (z[0], z[1]))[:4] if best is None else []:
                if score(cand).get("exact"):
                    best = cand
                    log["steps"].append("erase:%d+%s:assembler-convergence" % (index, tag))
                    break
            if best is not None:
                break

        if best is not None:
            # Greedy cleanup stays on a vf-proven base and only keeps exactness.
            i = 0
            while nv < VERIFY_BUDGET:
                live = sites_of(best)
                if i >= len(live):
                    break
                cand = erase_many(best, [live[i]], clean_notes=True)
                if unscored_text(cand) == usig and score(cand).get("exact"):
                    best = cand
                    log["steps"].append("cleanup:" + live[i][1])
                else:
                    i += 1
        log.update(compiles=nc, tried=nv, pins_out=len(sites_of(best)) if best else len(pins),
                   fences_removed=len(fences) - sum(s[1] == "ASM_SCHED_BARRIER" for s in sites_of(best)) if best else 0)
        return best, log
