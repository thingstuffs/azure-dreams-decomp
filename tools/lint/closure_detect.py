#!/usr/bin/env python3
"""Code detector for the ownership check: finds words that look like MIPS R3000 code in bytes that no compiled
function emits.

The detector decides nothing alone. Each hit must be matched by an acknowledgement line, or resolved by C, an
`own:code` line or a region line (docs/CLOSURE.md). It reads bytes handed to it and returns hits made of offsets,
sizes and rule names only; it never stores or prints the words it read.

Rules (the numbers are the ones the page uses):

    D1 return word      a `jr ra` word in the scan set, with the run of valid words behind it
    D2 frame, no return a stack-frame word with a saved return address and a run of valid words, no return in reach
    D3 call target      a `jal` or `j` in compiled code that lands in non-code bytes, or inside a function body
    D3B (report only)   an image with compiled code in which no local call lands on a function start
    D4 pointer to code  a word in the scan set that points exactly at the start of a D1 or D2 run
    D5 dense run        16 or more valid words with loads or stores and a branch or call
    D6 code stream      a compressed stream with a code signature that starts inside an `own:data` line
    D7 this-build calls in region other: a body whose calls all land on starts of the executable

Instruction validity is the R3000 table below (a word that no R3000 or its coprocessors decode is invalid).
"""
import bisect
import struct

JR = 0x03e00008
GTE = {1, 6, 12, 16, 17, 18, 19, 20, 22, 27, 28, 30, 32, 40, 41, 42, 45, 46, 48, 61, 62, 63}
LOAD = {32, 33, 34, 35, 36, 37, 38}
STORE = {40, 41, 42, 43, 46}
OKOP = {2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14} | LOAD | STORE | {50, 58}
ZERO_RUN_WORDS = 4
MAX_BACK_WORDS = 4096
RULES = ('D1', 'D2', 'D3', 'D3B', 'D4', 'D5', 'D6', 'D7', 'D8')
# A rule listed here prints its hits and counts them apart, and never counts as an open hit. D3B is a report by
# design. D5 is listed because the dry run measured it noisy: 370 hits in the 34 MB the bootstrap calls data, none
# containing a call target of compiled code (docs/CLOSURE.md).
REPORT_ONLY_RULES = frozenset({'D3B', 'D5', 'D8'})


def sg(x):
    return (x & 65535) - (65536 if x & 32768 else 0)


def valid(w):
    op = w >> 26
    rs = w >> 21 & 31
    rt = w >> 16 & 31
    rd = w >> 11 & 31
    sh = w >> 6 & 31
    fn = w & 63
    if op == 0:
        if fn in (0, 2, 3):
            return rs == 0
        if fn in (4, 6, 7, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43):
            return sh == 0
        if fn in (8, 9):
            return rt == 0 and sh == 0 and (fn == 9 or rd == 0)
        if fn in (12, 13):
            return True
        if fn in (16, 18):
            return not (rs or rt or sh)
        if fn in (17, 19):
            return not (rd or rt or sh)
        if fn in (24, 25, 26, 27):
            return not (rd or sh)
        return False
    if op == 1:
        return rt in (0, 1, 16, 17)
    if op in (6, 7):
        return rt == 0
    if op == 15:
        return rs == 0
    if op == 16:
        return w == 0x42000010 or (rs in (0, 4) and w & 0x7ff == 0) or (rs == 8 and rt in (0, 1))
    if op == 18:
        return (rs >= 16 and fn in GTE) or (rs in (0, 2, 4, 6) and w & 0x7ff == 0) or (rs == 8 and rt in (0, 1))
    return op in OKOP


def is_branch(w):
    return w >> 26 in (1, 4, 5, 6, 7) or (w >> 26 in (16, 18) and (w >> 21) & 31 == 8)


def is_frame(w):
    return w >> 16 == 0x27bd and sg(w) < 0 and sg(w) % 4 == 0


def spadj(w):
    return sg(w) if (w >> 16) == 0x27bd else 0


def is_ra_save(w):
    return w >> 16 == 0xafbf


def merge(iv):
    out = []
    for a, b in sorted((x[0], x[1]) for x in iv):
        if a >= b:
            continue
        if out and a <= out[-1][1]:
            out[-1][1] = max(b, out[-1][1])
        else:
            out.append([a, b])
    return out


def subtract(a, b):
    out = []
    b = merge(b)
    j = 0
    for s, e in merge(a):
        while j < len(b) and b[j][1] <= s:
            j += 1
        cur = s
        k = j
        while k < len(b) and b[k][0] < e:
            lo, hi = b[k]
            if lo > cur:
                out.append([cur, lo])
            cur = max(cur, hi)
            k += 1
            if cur >= e:
                break
        if cur < e:
            out.append([cur, e])
    return out


def intersect(a, b):
    return subtract(a, subtract(a, b))


def inside_merged(iv, starts, a, b):
    """True when [a, b) lies wholly inside the merged intervals `iv` (with `starts`, their start offsets)."""
    i = bisect.bisect_right(starts, a) - 1
    return i >= 0 and iv[i][0] <= a and b <= iv[i][1]


def aligned(a, b):
    """Word-aligned interior of [a, b)."""
    return (a + 3) & ~3, b & ~3


class Words:
    """Little-endian words of a bytes object, read lazily by interval."""

    def __init__(self, data):
        self.data = data

    def get(self, a, b):
        a, b = aligned(a, b)
        if b <= a:
            return a, ()
        return a, struct.unpack_from('<%dI' % ((b - a) // 4), self.data, a)


def table_run(words):
    """A D1 run that is a table of paired values: 4 or more words in which every aligned pair of words (word 0 and 1,
    2 and 3, ...) is two identical words, or 6 or more words in which fewer than 3 distinct words are neither the
    return word nor zero. Shorter runs (a bare return stub, a four-word accessor) are never table runs."""
    if len(words) < 4:
        return False
    plain = {w for w in words if w != JR and w != 0}
    paired = all(words[k] == words[k + 1] for k in range(0, len(words) - 1, 2))
    return paired or (len(words) >= 6 and len(plain) < 3)


def d1_hits(data, scan):
    """Every `jr ra` word in the scan set, with the run of valid words that ends at its delay slot."""
    pattern = struct.pack('<I', JR)
    hits = []
    for a, b in scan:
        base, ws = Words(data).get(a, b)
        if not ws:
            continue
        pos = data.find(pattern, base, base + 4 * len(ws))
        while pos != -1:
            if pos & 3 == 0:
                i = (pos - base) // 4
                start = i
                k = i - 1
                zeros = 0
                while k >= 0 and i - k <= MAX_BACK_WORDS:
                    w = ws[k]
                    if not valid(w):
                        break
                    if k >= 1 and ws[k - 1] == JR:
                        break
                    if w == 0:
                        zeros += 1
                        if zeros >= ZERO_RUN_WORDS:
                            break
                    else:
                        zeros = 0
                    start = k
                    k -= 1
                while start < i and ws[start] == 0:
                    start += 1
                end = min(i + 2, len(ws))
                if not table_run(ws[start:end]):
                    hits.append((base + 4 * start, base + 4 * end, 'D1'))
            pos = data.find(pattern, pos + 1, base + 4 * len(ws))
    return hits


def d2_hits(data, scan, covered=()):
    """A frame word with a saved return address and 6 or more valid words, with no return in the run."""
    hits = []
    blocked = merge(covered)
    blocked_starts = [x for x, _ in blocked]
    for a, b in scan:
        base, ws = Words(data).get(a, b)
        n = len(ws)
        i = 0
        while i < n:
            w = ws[i]
            if is_frame(w) and 8 <= -sg(w) <= 0x1000 and -sg(w) % 8 == 0:
                if any(is_ra_save(ws[j]) for j in range(i + 1, min(i + 9, n))):
                    j = i
                    zeros = 0
                    has_return = False
                    while j < n and valid(ws[j]) and j - i < MAX_BACK_WORDS:
                        if ws[j] == JR:
                            has_return = True
                            break
                        zeros = zeros + 1 if ws[j] == 0 else 0
                        if zeros >= ZERO_RUN_WORDS:
                            break
                        j += 1
                    if not has_return and j - i >= 6:
                        lo, hi = base + 4 * i, base + 4 * j
                        if not inside_merged(blocked, blocked_starts, lo, hi):
                            hits.append((lo, hi, 'D2'))
                        i = j
                        continue
            i += 1
    return hits


SJIS_LEAD = frozenset(list(range(0x81, 0xa0)) + list(range(0xe0, 0xfd)))
SJIS_SHARE = 0.4


def sjis_text(ws):
    """True when 40 % or more of the halfwords of the words carry a Shift-JIS lead byte (0x81-0x9F, 0xE0-0xFC)."""
    if not ws:
        return False
    carry = 0
    for w in ws:
        carry += (w & 0xff) in SJIS_LEAD or (w >> 8 & 0xff) in SJIS_LEAD
        carry += (w >> 16 & 0xff) in SJIS_LEAD or (w >> 24) in SJIS_LEAD
    return carry >= SJIS_SHARE * 2 * len(ws)


def d5_hits(data, scan, call_range=(0x80010000, 0x80800000), taken=(), rescue=None):
    """16 or more consecutive valid non-zero words with 2 or more loads or stores on a non-zero base register and
    a branch inside the run or a call into the call range. A run that reads as Shift-JIS text is not a hit, unless
    `rescue(first offset, end offset)` says it holds a call that lands on a known function start."""
    hits = []
    blocked = merge(taken)
    blocked_starts = [x for x, _ in blocked]
    for a, b in scan:
        base, ws = Words(data).get(a, b)
        n = len(ws)
        i = 0
        while i < n:
            if ws[i] == 0 or not valid(ws[i]):
                i += 1
                continue
            j = i
            while j < n and ws[j] != 0 and valid(ws[j]):
                j += 1
            if j - i >= 16:
                mem = 0
                reach = False
                for k in range(i, j):
                    w = ws[k]
                    op = w >> 26
                    if (op in LOAD or op in STORE) and (w >> 21) & 31:
                        mem += 1
                    if is_branch(w):
                        if i <= k + 1 + sg(w) < j:
                            reach = True
                    elif op in (2, 3):
                        target = 0x80000000 | ((w & 0x3ffffff) << 2)
                        if call_range[0] <= target < call_range[1]:
                            reach = True
                lo, hi = base + 4 * i, base + 4 * j
                if mem >= 2 and reach and (not sjis_text(ws[i:j]) or (rescue is not None and rescue(lo, hi))):
                    if not inside_merged(blocked, blocked_starts, lo, hi):
                        hits.append((lo, hi, 'D5'))
            i = j + 1
    return hits


D5_GROUNDED = 2
D8_LEAST_WORDS = 6


def grounded_memory_ops(ws):
    """Register dataflow of one run: the loads and stores whose base register holds an address the run itself can
    know: the stack or global pointer, an argument register not yet written in the run, a register built by `lui`,
    or a register derived from such a base by an add or a load. Random words read as code have arbitrary base
    registers; a function reads and writes through addresses it was given or built."""
    written, address, grounded = set(), set(), 0
    for w in ws:
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        if op in LOAD or op in STORE:
            if rs in (28, 29) or (4 <= rs <= 7 and rs not in written) or rs in address:
                grounded += 1
        if op == 15:
            written.add(rt)
            address.add(rt)
        elif op in LOAD or op in (8, 9, 10, 11, 12, 13, 14):
            written.add(rt)
            if (op in LOAD and rs in (28, 29)) or (op in (8, 9, 12, 13, 14) and (rs in address or rs in (28, 29))):
                address.add(rt)
            else:
                address.discard(rt)
        elif op == 0 and rd:
            written.add(rd)
            if (w & 63) in (32, 33, 37) and (rs in address or rt in address):
                address.add(rd)
            else:
                address.discard(rd)
    return grounded


def d8_hits(data, scan, taken=(), starts=None):
    """Report only. A function-shaped body without a return word: a run of 6 or more valid non-zero words that ends
    with a jump (`j`, or `jr` on a register that is not $31) and its delay slot, in which at least one load or store
    goes through a base register the run itself grounds (`grounded_memory_ops`). The tail-call and no-return
    endings that D1 cannot see. With `starts` (the load addresses of the known function starts) only a `j` whose
    target is a known start counts: on the real tree the loose form (any jump) opens 1,359 runs and none of them
    jumps to a known start."""
    hits = []
    blocked = merge(taken)
    blocked_starts = [x for x, _ in blocked]
    for a, b in scan:
        base, ws = Words(data).get(a, b)
        n = len(ws)
        i = 0
        while i < n:
            if ws[i] == 0 or not valid(ws[i]):
                i += 1
                continue
            j = i
            while j < n and ws[j] != 0 and valid(ws[j]):
                j += 1
            run = ws[i:j]
            # the jump is the run's last word (a nop in its delay slot is a zero word and ends the run) or its
            # second to last (a non-zero delay slot)
            for k in range(max(0, len(run) - 2), len(run)):
                w = run[k]
                if starts is None:
                    is_jump = w >> 26 == 2 or (w >> 26 == 0 and (w & 63) == 8 and (w >> 21) & 31 != 31)
                else:
                    is_jump = w >> 26 == 2 and (0x80000000 | ((w & 0x3ffffff) << 2)) in starts
                if is_jump and k >= D8_LEAST_WORDS - 1 and k + 2 >= len(run) and grounded_memory_ops(run[:k]):
                    lo, hi = base + 4 * i, base + 4 * (i + k + 2)
                    if not inside_merged(blocked, blocked_starts, lo, hi):
                        hits.append((lo, hi, 'D8'))
            i = j + 1
    return hits


def calls_in(data, a, b):
    """(position, instruction word) of every `jal` in [a, b)."""
    base, ws = Words(data).get(a, b)
    return [(base + 4 * k, w) for k, w in enumerate(ws) if w >> 26 == 3]


class Allocation:
    """One compiled allocation of an image: file offset, load address, size and the image extent it sits in."""

    __slots__ = ('foff', 'vma', 'size', 'start', 'end', 'image')

    def __init__(self, foff, vma, size, start, end, image=''):
        self.foff, self.vma, self.size, self.start, self.end, self.image = foff, vma, size, start, end, image


def d3_hits(data, allocations, funcs, classify, starts, resolve=None, cross=None):
    """Calls in compiled code. `funcs` is the sorted list of compiled-function extents of this file (one per
    function, not merged), `starts` the set of their start offsets, `classify(offset)` is 'c_code', 'noncode' (C data,
    own:data, own:padding, own:stream, own:untyped) or anything else for one byte of this file.

    A target maps to the file with the caller allocation's own delta and is kept only inside the same image
    extent. A target in a non-code byte is `call_into_noncode` (one hit per call word); a `jal` that lands inside another
    function's body, not at its start, is `call_midbody` (one hit per entry point, the target word; the note counts
    its call sites; a `j` inside its own function is a local jump). Everything else is counted,
    not judged. A call word seen through several images is reported once.

    `resolve(allocation, target address)` (optional) gives the file offset of a load address through the chunk of
    the image that is loaded there, or None when no chunk of the image is loaded at that address (the call is then
    counted as outside, not judged); without it the caller allocation's own delta is used. `cross(allocation, kind,
    target address)` (optional) is true when the target is a function start of a different program or image loaded
    at that address; such a call is counted as `cross_image` and not judged. `kind` is 'noncode' or 'midbody'.
    """
    seen, entries = {}, {}
    notes = dict(calls=0, to_start=0, outside=0, cross_image=0)
    begins = [a for a, b in funcs]
    per_image = {}
    for alloc in allocations:
        delta = alloc.vma - alloc.foff
        lo = bisect.bisect_left(begins, alloc.foff)
        stat = per_image.setdefault(alloc.image, [0, 0])
        for idx in range(lo, len(funcs)):
            a, b = funcs[idx]
            if a >= alloc.foff + alloc.size:
                break
            base, ws = Words(data).get(a, b)
            for k, w in enumerate(ws):
                op = w >> 26
                if op not in (2, 3):
                    continue
                pc = base + 4 * k
                target_vma = ((alloc.vma + (pc - alloc.foff) + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2)
                target = target_vma - delta if resolve is None else resolve(alloc, target_vma)
                notes['calls'] += 1
                stat[0] += 1
                if target is None or not alloc.start <= target < alloc.end:
                    notes['outside'] += 1
                    continue
                if target in starts:
                    notes['to_start'] += 1
                    stat[1] += 1
                    continue
                kind = classify(target)
                if kind == 'c_code':
                    if op == 3 and not a <= target < b:
                        if cross is not None and cross(alloc, 'midbody', target_vma):
                            notes['cross_image'] += 1
                        else:
                            entries.setdefault(target, set()).add(pc)
                elif kind == 'noncode':
                    if cross is not None and cross(alloc, 'noncode', target_vma):
                        notes['cross_image'] += 1
                    else:
                        seen.setdefault(pc, (pc, pc + 4, 'D3', 'call_into_noncode'))
    for target, sites in entries.items():
        # one hit per mid-body entry point (its word), however many call sites reach it
        seen.setdefault(('entry', target), (target, target + 4, 'D3', 'call_midbody:%d' % len(sites)))
    notes['midbody_sites'] = sum(len(v) for v in entries.values())
    weak = sorted(image for image, (calls, local) in per_image.items() if calls and not local)
    return sorted(seen.values()), notes, weak


def d4_hits(data, scan, run_starts, deltas_at, window=1):
    """A word in the scan set that, read as an address at one of the deltas of the images that contain it, is the
    start of a D1 or D2 run (`window` bytes: 1 means exactly the start)."""
    starts = sorted(run_starts)
    hits = []
    if not starts:
        return hits
    for a, b in scan:
        base, ws = Words(data).get(a, b)
        for k, w in enumerate(ws):
            if w & 3 or not (0x80010000 <= w < 0x80800000 or 0xa0010000 <= w < 0xa0800000):
                continue
            pos = base + 4 * k
            for delta in deltas_at(pos):
                t = (w & 0x1fffffff | 0x80000000) - delta
                i = bisect.bisect_left(starts, t)
                if i < len(starts) and starts[i] < t + window:
                    hits.append((pos, pos + 4, 'D4'))
                    break
    return hits


def d6_hits(streams, own_data, own_stream):
    """Code-signature streams (container, offset) that start inside own:data and not inside own:stream."""
    hits = []
    for container, offset, used in streams:
        data_iv, stream_iv = own_data.get(container, []), own_stream.get(container, [])
        if _inside(data_iv, offset) and not _inside(stream_iv, offset):
            hits.append((container, offset, offset + used, 'D6'))
    return hits


def _inside(iv, x):
    i = bisect.bisect_right([a for a, b in iv], x) - 1
    return i >= 0 and iv[i][0] <= x < iv[i][1]


def d7_hits(data, bodies, exe_range, exe_starts):
    """In region other: a body (a D1 extent) with 2 or more calls into the executable range, every one of them on
    the start of an executable function."""
    hits = []
    for a, b, _rule in bodies:
        base, ws = Words(data).get(a, b)
        calls = good = 0
        for w in ws:
            if w >> 26 == 3:
                target = 0x80000000 | ((w & 0x3ffffff) << 2)
                if exe_range[0] <= target < exe_range[1]:
                    calls += 1
                    good += target in exe_starts
        if calls >= 2 and good == calls:
            hits.append((a, b, 'D7'))
    return hits
