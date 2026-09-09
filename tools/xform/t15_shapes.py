"""T15: the lane recipes as a search.

Four lanes over the near band closed 21 of 50 rows, and three of the shapes that did it are
mechanical.  This plugin tries them, in cost order, against the row's fully stripped text.

  maskfold   a local declared wider than the load that fills it, with an explicit `& 0xFF` /
             `& 0xFFFF`, is a length defect: the mask folds away because `lbu`/`lhu` already
             zero-extend, so gcc emits one word fewer than retail.  Declaring the local at the
             load's width and dropping the mask makes gcc re-mask before the use.  (Two sibling
             rows fell to this unchanged in the length-drift lane.)
  narrow     a value-preserving *mode* change on one side of a copy.  gcc-2.7/2.8's cse collapses
             a plain `b = a;` into one pseudo whenever both stay live, and then the allocator has
             no choice left - that collapse is what most `reg-rename` pins stand in for.  A
             narrowing assignment is not a REG-REG set in RTL, so cse never merges the two.
  mask2cast  `E & 0xFFFF` at a use site becomes `(u16) E` - the same mode-change handle as
             `narrow`, applied at the use rather than the declaration (harvested from an Astra
             depin lane, which is why `maskfold`'s declaration-only rewrite had missed it).
  dup_if     the statement after an `if (...) { }` written into both arms instead (same source).
  fence      `do { stmt; } while (0)` is a zero-byte scheduling barrier: it pins a statement's
             definition point without emitting anything.  A bare block does NOT do this - only the
             loop note does - so it is scaffolding in C clothing and `census.py` counts it.  It is
             tried LAST, after the shapes that are real source, and the journal says when it fired.

**Why a mechanical search over types and fences is safe:** the verdict is byte equality against
retail.  A narrowing that changed the function's behaviour could not compile to retail's bytes, so
a semantic change cannot survive the gate.  The search may therefore be liberal; only the budget
limits it.
"""
import json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of

try:
    from .t12_stmtorder import strip_pins, mask, depths, movable, is_decl
except ImportError:                       # pragma: no cover - direct import
    from t12_stmtorder import strip_pins, mask, depths, movable, is_decl

BAND = 12          # strip damage a row must already be within
import os
BUDGET = int(os.environ.get("T15_BUDGET", "45"))   # verify runs per row (T15_BUDGET to raise)
ROUNDS = int(os.environ.get("T15_ROUNDS", "3"))    # greedy hill-climb rounds
NARROW = {"s32": ["s16", "s8"], "u32": ["u16", "u8"], "int": ["s16", "s8"],
          "unsigned": ["u16", "u8"], "s16": ["s8"], "u16": ["u8"]}
DECL_RE = re.compile(r"^(?P<i>[ \t]+)(?P<ty>u8|s8|u16|s16|u32|s32|int|unsigned)[ \t]+(?P<n>[A-Za-z_]\w*)[ \t]*;[ \t]*$")
MASK_RE = re.compile(r"\b(?P<n>[A-Za-z_]\w*)[ \t]*&[ \t]*0x(?P<m>[Ff]{2}|[Ff]{4})\b")

_STRIP = None


def strip_census():
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


def decls(text):
    """[(line index, indent, type, name)] for the plain scalar locals of the function."""
    out = []
    for i, ln in enumerate(text.splitlines()):
        m = DECL_RE.match(ln)
        if m:
            out.append((i, m.group("i"), m.group("ty"), m.group("n")))
    return out


def retype(text, idx, ty, name, newty):
    lines = text.splitlines(True)
    ln = lines[idx]
    nl = "\n" if ln.endswith("\n") else ""
    lines[idx] = re.sub(r"\b%s\b" % ty, newty, ln[:len(ln) - len(nl)], count=1) + nl
    return "".join(lines)


def maskfold_candidates(text):
    """Narrow a local to its mask width and delete the mask (`x & 0xFF` with `u8 x`)."""
    out = []
    masked = mask(text)
    for idx, ind, ty, name in decls(text):
        width = None
        for m in MASK_RE.finditer(masked):
            if m.group("n") != name:
                continue
            width = "u8" if len(m.group("m")) == 2 else "u16"
            break
        if width is None or ty == width:
            continue
        t = retype(text, idx, ty, name, width)
        t = MASK_RE.sub(lambda m: m.group("n") if m.group("n") == name else m.group(0), t)
        if t != text:
            out.append(("maskfold:%s->%s" % (name, width), t))
    return out


def narrow_candidates(text):
    out = []
    for idx, ind, ty, name in decls(text):
        for newty in NARROW.get(ty, []):
            out.append(("narrow:%s %s->%s" % (name, ty, newty), retype(text, idx, ty, name, newty)))
    return out


def fence_candidates(text):
    """Wrap one simple statement in `do { ... } while (0);` - a zero-byte scheduling barrier."""
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    dep = depths(masked)
    for i, ln in enumerate(lines):
        if not movable(masked[i]) or is_decl(masked[i]):
            continue
        nl = "\n" if ln.endswith("\n") else ""
        body = ln[:len(ln) - len(nl)]
        ind = re.match(r"[ \t]*", body).group(0)
        new = f"{ind}do {{\n{ind}    {body.strip()}\n{ind}}} while (0);{nl}"
        out.append(("fence:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 1:])))
    for i, ln in enumerate(lines):
        s = masked[i].strip()
        if not s.startswith("return") or not s.endswith(";"):
            continue
        nl = "\n" if ln.endswith("\n") else ""
        body = ln[:len(ln) - len(nl)]
        ind = re.match(r"[ \t]*", body).group(0)
        new = f"{ind}do {{\n{ind}    {body.strip()}\n{ind}}} while (0);{nl}"
        out.append(("fence-return:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 1:])))
    return out


USE_MASK_RE = re.compile(r"(?P<e>\b[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+)*)\s*&\s*0x(?P<m>[Ff]{2}|[Ff]{4})\b")


def mask2cast_candidates(text):
    """`E & 0xFFFF` at a USE site becomes `(u16) E`.

    Harvested from an Astra depin lane: the mask and the cast compute the same value, but a cast is
    a mode change in RTL where the AND is an ordinary binary op, so cse cannot fold the two pseudos
    together - the same handle as `narrow`, applied at the use instead of the declaration.  t15's
    `maskfold` only ever retyped the *declaration*, which is why it missed these.
    """
    out = []
    masked = mask(text)
    for m in USE_MASK_RE.finditer(masked):
        ty = "u8" if len(m.group("m")) == 2 else "u16"
        expr = text[m.start("e"):m.end("e")]
        cand = text[:m.start()] + f"({ty}) {expr}" + text[m.end():]
        out.append(("mask2cast:%s->%s" % (expr[:20], ty), cand))
    return out


IF_RE = re.compile(r"^(?P<i>[ \t]*)\}[ \t]*$")


def dup_after_if_candidates(text):
    """The statement after an `if (...) { ... }` written into BOTH arms instead.

    Also harvested from an Astra depin lane.  gcc's cross-jumping merges the duplicates back, but
    the duplication changes which block owns the store - and a value written in both arms is what
    fills a branch delay slot.  Only the simple shape is generated: a closing brace at some indent,
    no `else`, followed by one movable simple statement at the same indent.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i, ln in enumerate(masked):
        m = IF_RE.match(ln.rstrip("\n"))
        if not m or i + 1 >= len(lines):
            continue
        if masked[i + 1].strip().startswith("else"):
            continue
        if not movable(masked[i + 1]) or is_decl(masked[i + 1]):
            continue
        ind = m.group("i")
        if masked[i + 1][:len(ind) + 1] != ind + masked[i + 1].strip()[0]:
            continue                       # the statement must sit at the brace's own indent
        stmt = lines[i + 1].strip()
        new = (f"{ind}    {stmt}\n{ind}}} else {{\n{ind}    {stmt}\n{ind}}}\n")
        out.append(("dup_after_if:%d" % (i + 1),
                    "".join(lines[:i] + [new] + lines[i + 2:])))
    return out


class T:
    name = "t15_shapes"
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
        t = rec.get("total")
        if t is None or t > BAND:
            return f"strip damage {t} above band {BAND}"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        """Greedy hill-climb over the shape menu.

        The single-shot sweep left 39 rows whose residue a *single* candidate improved without
        closing - the mechanism was right and the row needed more than one edit.  So each round
        keeps the best improving candidate and searches again from there, up to ROUNDS rounds or
        the budget.  A round that improves nothing stops the climb: the menu has nothing left to
        say about that row, and its `best_label` names what came closest for the lane that follows.
        """
        base = strip_pins(text)
        pins_in = len(sites_of(text))
        tried = 0
        v = verify_fn(base)
        tried += 1
        if v.get("exact"):
            return base, {"step": "strip", "tried": tried, "pins_in": pins_in, "pins_out": 0}
        strip_total = v.get("total")
        cur, cur_total, steps = base, strip_total, []
        best_label = "strip"
        seen = {sha_text(base)}
        for rnd in range(ROUNDS):
            cands = (maskfold_candidates(cur) + mask2cast_candidates(cur)
                     + dup_after_if_candidates(cur) + narrow_candidates(cur) + fence_candidates(cur))
            round_best = None
            for label, cand in cands:
                if tried >= BUDGET:
                    break
                h = sha_text(cand)
                if h in seen:
                    continue
                seen.add(h)
                v = verify_fn(cand)
                tried += 1
                if v.get("exact"):
                    steps.append(label)
                    return cand, {"step": "+".join(steps), "tried": tried, "rounds": rnd + 1,
                                  "pins_in": pins_in, "pins_out": 0,
                                  "fence": any(x.startswith("fence") for x in steps)}
                t = v.get("total")
                if t is not None and t < (cur_total if cur_total is not None else 1e9):
                    if round_best is None or t < round_best[0]:
                        round_best = (t, label, cand)
            if round_best is None or tried >= BUDGET:
                break
            cur_total, best_label, cur = round_best[0], round_best[1], round_best[2]
            steps.append(round_best[1])
        return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in,
                      "best_total": cur_total, "best_label": best_label, "strip_total": strip_total,
                      "climb": "+".join(steps) or None,
                      "moved": (strip_total - cur_total) if (cur_total is not None and strip_total is not None) else None,
                      "stopped": "budget" if tried >= BUDGET else "no-improvement"}
