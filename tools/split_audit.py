#!/usr/bin/env python3
"""Audit every tail-jump dependency in the tree against the retail bytes -> ledger/split_audit.jsonl.

Why (docs/FIDELITY.md, 2026-09-08 Psy-Q measurement): genuine cc1 emits `jal` for a
`__attribute__((noreturn))` call and genuine ASPSX never rewrites `jal` to `j`.  So a retail `j`
to something we treat as a separate function has no C producer: either our split put a boundary
through one real function (the `j` is an ordinary intra-function jump), or the target is a shared
tail fragment, or the row is hand-written asm.  A row carrying such a dependency is not honestly
"clean" until that is decided, so this audit is the evidence a level rule can read.

One record per (row, target):

  intra          target inside [true base, true base + size): a mis-split or a pseudo-call --
                 the `j` never left the function.  Blocks L3.
  extern-jal     target outside the row and reached by `jal` somewhere in the same container
                 image: a real, returning function, so a noreturn/sibcall membership for it is a
                 FALSE MEMBER -- a candidate config/noreturn_false_members.jsonl line is emitted
                 (to ledger/split_audit_false_members.candidates.jsonl; config/ is NOT touched).
  extern-j-only  target outside the row and only ever reached by `j`: a shared tail fragment,
                 i.e. most likely a mis-split function.  Every jumper's address is recorded.
  cross-segment  the target address is not inside the declaring row's OWN segment run under that
                 row's delta, so this container cannot say what code is there: a row links at
                 `foff + delta`, and that delta is only valid inside its own run.  Resolving the
                 target anyway lands on whatever occupies the arithmetic file offset in a FOREIGN
                 overlay segment, and every `j`/`jal` reported for it belongs to that other
                 module.  This is not a mis-split of this row, so it clears L3 like `extern-jal`
                 (and blocks L4 like every tail-jump dependency).  No jumpers are recorded --
                 recording them is precisely the bug this kind exists to stop (2026-09-22,
                 docs/evidence/split_fragments_20260922.md §3/§4/§5: the dungeon `extern-j-only`
                 verdicts were another segment's mirrored jumps 0x12000 away, and the town one
                 resolved onto Shift-JIS script text).
  cross-image    the target address is not inside the declaring container's image AT ALL under
                 that row's delta, and it is decided elsewhere: it is a function of the SLUS base
                 executable (`image: "slus"`, co-resident under every overlay), or retail CALLS it
                 with a `jal` -- in the row's own retail bytes, or at least inside the row's own
                 segment run -- while its code is on no image in the tree (`image: "absent"`), or
                 the target is a fixed PlayStation kernel RAM address and the row's OWN retail
                 bytes carry the `j`/`jal` that reaches it (`image: "kernel"`; images are
                 `slus | absent | kernel`).  A `jal` is a call and a call HAS a C producer; a
                 retail `j` is what has none, which is this audit's whole premise.  So the
                 dependency is a call OUT of this container, not a boundary drawn through one real
                 function: it clears L3 like `extern-jal` and blocks L4 like every tail-jump
                 dependency.
                 (2026-09-22, the three `func_8007BEF0` records.  That symbol is NOT a SLUS
                 function, despite docs/HANDOVER.md section 3.1 and the town `row_2714dc_804084dc`
                 rowbase proof: SLUS file offset 0x4F6F0 is the middle of the libgte string
                 "Error: Can't push matrix,stack(max 20) is full!", no `j`/`jal` anywhere in
                 baserom/slus_006.14 reaches it and no symbol names it.  It is the `exit` of the
                 DECLARING module's own linked runtime, whose text was never carved into the
                 container -- docs/evidence/konami_assertion_sites.md sections 7-8,
                 docs/evidence/void_callees_20260922.md.  Each of the three rows carries the `jal`
                 in its own retail bytes, at the offset of the C call.)
                 `image: "kernel"` (2026-09-22, the three town rows `func_808B8184`, `func_808B85F0`,
                 `func_808BB138`, four records): the target lies in [0x80000000, 0x80010000), the
                 fixed PlayStation BIOS/kernel RAM area -- never part of any overlay or of SLUS --
                 and the row's own retail bytes carry the `j`/`jal` that reaches it, at the offset
                 of a `__attribute__((noreturn))` extern declared and called in the row's own C.
                 Decoding a `j`/`jal` word needs only the top nibble of the PC, which is 0x8 at
                 EVERY candidate base for a row living in KSEG0-mapped overlay/RAM space, so this
                 verdict needs no rowbase record: it is checked before the `d is None` refusal.
  text-only      the target is inside the row's extent but NO `j`/`jal` word in the row's own
                 retail bytes targets it: the C dependency has no retail producer at all, so it is
                 not a mis-split.  `byte_verified` is false on exactly these.
  asm            the row is hand-written asm (pin_census.asm_blocker): no C producer is expected.
  unresolved     no rowbase record for the row (synthetic base), or the target address does not
                 land inside the container image and neither the base executable nor the row's own
                 retail bytes decide it (only a `j` reaches it, or nothing does).  `proof` says
                 which, and names every place that was looked.

Every `intra` record is BYTE-VERIFIED: the row's own retail slice is scanned for a `j`/`jal`
word whose absolute target is the record's `target_addr`, and `row_jump_offsets` / `proof` name
where it is.  Without that word the record is `text-only`, not `intra`.

The (row, target) pairs are levels.py's own `tail_jump_targets`, imported rather than re-derived,
so this file and the level ladder cannot disagree about what needs a record.

Address resolution is the same one the callee audit used (docs/evidence/void_callees_20260922.md):
a row links at `foff + rowbase.delta_for(family, foff)` and a `j`/`jal` field is absolute, so a
target address T in a segment with delta D is the image byte at `T - D`.  The index is keyed on
that FILE OFFSET, not on the address: overlay segments reuse names and addresses (town's
`func_80019988` is a `(void)` wrapper at foff 0x690988 and a two-argument function at foff
0x2AF188), so an address-keyed index would merge different functions.

Only code whose base is resolvable contributes to the index (inside a rowbase region, or inside a
registered row with a true name); the rest of a container is data and would only add noise.
Text is read with the `#ifdef NON_MATCHING` / `#if 0` arms blanked, the arms no build compiles.

    python3 tools/split_audit.py [--container town] [--limit N] [--out PATH]
"""
import argparse, bisect, json, re, struct, sys, time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parent / "gate"))
from common import ROOT, LEDGER, rows, raw_path
from pin_census import arm_labels, HAS_PP_RE, asm_blocker
# The demanded (row, target) pairs are levels.py's, so use ITS detector rather than a second copy:
# tail_jump_targets reads a definition-header-blanked, declaration-blanked, comment-stripped,
# port/dead-arm-blanked view (levels._call_text), so a row whose OWN name is on its container's
# noreturn/sibcall list no longer lists itself off its `void func_X(...) {` header, and a
# prototype is never a call.  A private copy here drifted from it once already.
from levels import tail_jump_targets
import rowbase as RB
RB.ROOT = ROOT                                    # the gate copy resolves config/ from its own root

IMAGES = {
    "town":    ROOT / "build_ovl/work/s3_splat/extract/TOWN_TOWN.BIN",
    "dungeon": ROOT / "build_ovl/work/s3_splat/extract/DUNGEON_DUNGEON.BIN",
    "main":    ROOT / "build_ovl/work/s3_splat/extract/MAIN_MAIN.BIN",
    "ovmovie": ROOT / "build_ovl/work/s3_splat/extract/OVMOVIE.BIN",
}
KERNEL_LO, KERNEL_HI = 0x80000000, 0x80010000
# PS-X BIOS/kernel RAM: fixed at every candidate base (a `j`/`jal` word decodes with the PC's top
# nibble, which is 0x8 for any row living in KSEG0-mapped overlay/RAM space), so a row's own j/jal
# into this window is decided without a rowbase record at all.

SLUS = ROOT / "baserom/slus_006.14"
SLUS_VRAM, SLUS_OFF = 0x8002D000, 0x800
SLUS_DELTA = SLUS_VRAM - SLUS_OFF          # ONE fixed link address, so ONE constant delta
SLUS_YAML = ROOT / "config/slus_006.14.yaml"
SLUS_SYMS = ROOT / "config/slus_006.14.symbols.txt"
SLUS_CODE_TYPES = ("asm", "c", "hasm")
# `- [0x72a8, c, konami_runtime]` / `- [0x3e018, bin]` / `- [0x80000]`.  The `^\s*-\s*\[` anchor
# skips the commented-out subsegments (`# - [0x2d854, shiftjis, ...]`) on its own.
SLUS_SUBSEG_RE = re.compile(r"^\s*-\s*\[\s*(0x[0-9a-fA-F]+)\s*(?:,\s*([A-Za-z_]\w*))?")
SLUS_SYM_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9a-fA-F]+)\s*;(.*)$")

NORETURN_DECL = re.compile(r"\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*__attribute__\s*\(\s*\(\s*noreturn")
ASM_ALIAS = re.compile(r"(?:asm|__asm__)\s*\(\s*\"(func_[0-9A-F]{8})\"\s*\)")
CALL = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")


def compiled_text(text):
    """The arms the build actually compiles (drops `port` / `dead`)."""
    if not HAS_PP_RE.search(text):
        return text
    return "\n".join("" if lab in ("port", "dead") else ln
                     for ln, lab in zip(text.splitlines(), arm_labels(text)))


def sym_sets():
    """{family: set(symbols)} from config/sibcall_syms*.txt and config/noreturn_syms*.txt."""
    out = {}
    for p in sorted((ROOT / "config").glob("*_syms*.txt")):
        parts = p.stem.split(".")
        fam = parts[1] if len(parts) > 1 else "main"
        s = out.setdefault(fam, set())
        for line in p.read_text(errors="replace").splitlines():
            tok = line.split("#", 1)[0].strip()
            if re.fullmatch(r"func_[0-9A-F]{8}", tok):
                s.add(tok)
    return out


class Segments:
    """foff -> link delta, from rowbase records first, then registered rows with a true name."""

    def __init__(self, family, rowlist):
        spans = [(r["start"], r["end"], r["delta"]) for r in RB._records(family)]
        for r in rowlist:
            if r.get("foff") is None or not r.get("true_name"):
                continue
            m = re.match(r"func_([0-9A-F]{8})$", r["true_name"])
            if not m:
                continue
            d = (int(m.group(1), 16) - r["foff"]) & 0xFFFFFFFF
            spans.append((r["foff"], r["foff"] + r["size"], d))
        spans.sort()
        # Rows of ONE module share a delta, so a gap between two same-delta spans is that module's
        # own un-split code (or its rodata): extend across it, otherwise only the decompiled 5-24%
        # of an image contributes jumpers and an `extern-j-only` verdict would be an artefact of
        # what happens to be split.  A run ends the moment a different delta appears.
        runs = []
        for st, en, d in spans:
            if runs and runs[-1][2] == d and st >= runs[-1][0]:
                runs[-1][1] = max(runs[-1][1], en)
            else:
                runs.append([st, en, d])
        self.known = spans                                  # rows / rowbase records only
        self.kstarts = [x[0] for x in spans]
        self.starts = [r[0] for r in runs]
        self.spans = [tuple(r) for r in runs]

    def in_known(self, foff):
        i = bisect.bisect_right(self.kstarts, foff) - 1
        while i >= 0 and self.kstarts[i] + 0x200000 > foff:
            st, en, _ = self.known[i]
            if st <= foff < en:
                return True
            i -= 1
        return False

    def run(self, foff):
        """The merged same-delta run holding this file offset, as (start, end, delta), or None.
        A row's delta is only meaningful inside its own run: outside it the same address belongs
        to a different overlay segment (see the `cross-segment` kind in the module docstring)."""
        i = bisect.bisect_right(self.starts, foff) - 1
        while i >= 0 and self.starts[i] + 0x200000 > foff:      # overlapping rowbase/row spans
            s, e, d = self.spans[i]
            if s <= foff < e:
                return (s, e, d)
            i -= 1
        return None

    def delta(self, foff):
        r = self.run(foff)
        return None if r is None else r[2]


def index_image(path, segs):
    """{target file offset: ([`j` source addrs], [`jal` source addrs])} for the whole image."""
    data = path.read_bytes()
    n = len(data) // 4
    words = struct.unpack("<%dI" % n, data[:n * 4])
    idx = {}
    for i, w in enumerate(words):
        op = w >> 26
        if op != 2 and op != 3:
            continue
        foff = i * 4
        d = segs.delta(foff)
        if d is None:
            continue
        src = (foff + d) & 0xFFFFFFFF
        tgt = ((src + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
        toff = (tgt - d) & 0xFFFFFFFF
        if toff >= len(data):
            continue
        e = idx.get(toff)
        if e is None:
            e = idx[toff] = ([], [])
        e[0 if op == 2 else 1].append(src)
    return idx, len(data)


_ROWJ = {}
def row_jumps(fam, r, base):
    """{absolute target: [(op, source address)]} for every `j`/`jal` word INSIDE this row's own
    retail slice.  A text dependency on a target inside the row's extent is only a mis-split if
    retail really jumps there; without this check a pseudo-call the compiler never produced (or a
    stale m2c spelling) counts as one.  Cached per row."""
    key = r["id"]
    if key not in _ROWJ:
        out = {}
        img = IMAGES.get(fam)
        if img is not None and r.get("foff") is not None:
            data = _image(img)
            sl = data[r["foff"]:r["foff"] + r["size"]]
            for i in range(len(sl) // 4):
                w = int.from_bytes(sl[i * 4:i * 4 + 4], "little")
                op = w >> 26
                if op != 2 and op != 3:
                    continue
                src = (base + i * 4) & 0xFFFFFFFF
                tgt = ((src + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                out.setdefault(tgt, []).append(("j" if op == 2 else "jal", src))
        _ROWJ[key] = out
    return _ROWJ[key]


_IMG = {}
def _image(path):
    if path not in _IMG:
        _IMG[path] = path.read_bytes()
    return _IMG[path]


def slus_segment():
    """(t_addr, t_size) of the PS-X EXE's single loadable segment, read from its header."""
    data = _image(SLUS)
    if data[:8] != b"PS-X EXE":
        return None
    t_addr, t_size = struct.unpack("<2I", data[0x18:0x20])
    return t_addr, t_size


def slus_code_spans():
    """[(start foff, end foff)] of the executable's CODE subsegments (`asm`/`c`/`hasm`), from
    config/slus_006.14.yaml.  The rest of the resident segment is data, and indexing data as code
    is not a theoretical worry here: 0x8007BEF0 is SLUS file offset 0x4F6F0, the middle of the
    libgte string "Error: Can't push matrix,stack(max 20) is full!" inside the `bin` resident-data
    block at 0x3E018 -- ASCII that decodes as perfectly good `j`/`jal` words."""
    if not SLUS_YAML.exists():
        return []
    entries = []
    for line in SLUS_YAML.read_text(errors="replace").splitlines():
        m = SLUS_SUBSEG_RE.match(line)
        if m:
            entries.append((int(m.group(1), 16), (m.group(2) or "").lower()))
    entries.sort()
    out = []
    for i, (st, typ) in enumerate(entries):
        if typ not in SLUS_CODE_TYPES:
            continue
        en = entries[i + 1][0] if i + 1 < len(entries) else st
        if en > st:
            out.append((st, en))
    return out


def slus_symbols():
    """{address: name} from config/slus_006.14.symbols.txt: function symbols only, and WITHOUT the
    `// overlay self-define` stub lines.  Those stubs exist so an overlay TU can be linked against
    an address in its OWN bank (`func_8007BFE0 = 0x8007BFE0; // overlay self-define (func_80019E34
    callee)`); reading one as evidence of SLUS code is precisely the false positive this audit has
    to avoid."""
    out = {}
    if not SLUS_SYMS.exists():
        return out
    for line in SLUS_SYMS.read_text(errors="replace").splitlines():
        m = SLUS_SYM_RE.match(line)
        if not m:
            continue
        name, addr, comment = m.group(1), int(m.group(2), 16), m.group(3)
        if "overlay self-define" in comment or "type:func" not in comment:
            continue
        out[addr] = name
    return out


_SLUSIDX = {}
def slus_index():
    """{absolute target address: ([`j` source addrs], [`jal` source addrs])} over the executable's
    CODE subsegments.  An ADDRESS key is sound here and only here: the executable links at one
    fixed base, so a file offset has exactly one link address (an overlay file offset has several,
    which is why index_image keys on the file offset instead)."""
    if "idx" not in _SLUSIDX:
        idx = {}
        if SLUS.exists():
            data = _image(SLUS)
            for st, en in slus_code_spans():
                for foff in range(st, min(en, len(data) - 3), 4):
                    w = int.from_bytes(data[foff:foff + 4], "little")
                    op = w >> 26
                    if op != 2 and op != 3:
                        continue
                    src = (foff + SLUS_DELTA) & 0xFFFFFFFF
                    tgt = ((src + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                    e = idx.get(tgt)
                    if e is None:
                        e = idx[tgt] = ([], [])
                    e[0 if op == 2 else 1].append(src)
        _SLUSIDX["idx"] = idx
    return _SLUSIDX["idx"]


def slus_lookup(ta):
    """What baserom/slus_006.14 -- the base executable, resident under EVERY overlay -- says about
    the absolute address `ta`.  Pure data, no verdict:

      resident  `ta` is inside the loaded PS-X EXE segment [t_addr, t_addr + t_size)
      foff      its SLUS file offset (SLUS_OFF-based) when resident, else None
      in_text   that file offset is inside a CODE subsegment, not .rodata/data
      js/jal    source addresses in SLUS code that reach it
      symbol    its name in config/slus_006.14.symbols.txt (self-define stubs excluded)
      decided   in_text AND (a `jal` reaches it OR a function symbol names it): a real function of
                the co-resident base executable
    """
    seg = slus_segment() if SLUS.exists() else None
    out = {"resident": False, "seg": seg, "foff": None, "in_text": False,
           "js": [], "jal": [], "symbol": None, "decided": False}
    if seg is None:
        return out
    t_addr, t_size = seg
    if not (t_addr <= ta < t_addr + t_size):
        return out
    out["resident"] = True
    out["foff"] = foff = ta - SLUS_DELTA
    out["in_text"] = any(st <= foff < en for st, en in slus_code_spans())
    js, jal = slus_index().get(ta, ([], []))
    out["js"] = sorted(set(js)); out["jal"] = sorted(set(jal))
    out["symbol"] = slus_symbols().get(ta)
    out["decided"] = bool(out["in_text"] and (out["jal"] or out["symbol"]))
    return out


def slus_note(slus):
    """The SLUS half of an off-image proof, in one clause, whatever the lookup found."""
    if slus.get("seg") is None:
        return "the SLUS base executable was not available to check"
    t_addr, t_size = slus["seg"]
    where = f"the resident SLUS segment [0x{t_addr:08X}, 0x{t_addr + t_size:08X})"
    if not slus["resident"]:
        return f"the address is not inside {where} either"
    bits = [f"the address IS inside {where}, at SLUS file offset 0x{slus['foff']:X}",
            "in a code subsegment" if slus["in_text"] else
            "but in a DATA subsegment of it, not code (config/slus_006.14.yaml)",
            f"reached there by {len(slus['jal'])} jal and {len(slus['js'])} j site(s) in SLUS code",
            f"named {slus['symbol']} in config/slus_006.14.symbols.txt" if slus["symbol"] else
            "and named by no function symbol in config/slus_006.14.symbols.txt (its `overlay "
            "self-define` stub lines, which name OVERLAY addresses, are excluded)"]
    return ", ".join(bits)


def offimage_verdict(fam, ta, d, toff, imgsize, own_hits, run, run_jal, run_js, slus):
    """Decide a target that does NOT land inside the declaring container's image under the row's
    own delta.  PURE (no filesystem, no images) so it is directly unit-testable
    (tools/tests/test_split_audit_cross_image.py):

      own_hits  row_jumps()[ta] for the declaring row -- [(op, source addr)] in its OWN bytes
      run       the row's merged segment run (start, end, delta), or None
      run_jal   `jal` source addresses inside that run that reach `ta`
      run_js    `j` source addresses inside that run that reach `ta`
      slus      a slus_lookup() dict

    Returns the record fields to merge.  Two ways to decide, both `cross-image`:

      image "slus"    the target is a function of the co-resident base executable.
      image "absent"  retail CALLS it -- there is a `jal` to it, in the row's own retail bytes or
                      at least inside the row's own segment run -- but its code is on no image in
                      the tree.  A `jal` is a call and a call HAS a C producer, which is this
                      audit's whole premise (a retail `j` is what has none), so the dependency is
                      a call OUT of this container, not a boundary drawn through one real
                      function.  2026-09-22: `func_8007BEF0` / `func_8007C040` are the `exit` /
                      `printf` of the DECLARING module's own linked runtime, whose text was never
                      carved into the container -- docs/evidence/konami_assertion_sites.md
                      sections 7-8, docs/evidence/void_callees_20260922.md.

    Anything else stays `unresolved`, and the proof names every place that was looked.  Only a
    decided verdict clears L3; every kind here blocks L4, like all tail-jump dependencies."""
    own_jal = sorted({src for op, src in own_hits if op == "jal"})
    own_j = sorted({src for op, src in own_hits if op == "j"})
    run_jal = sorted(set(run_jal)); run_js = sorted(set(run_js))
    head = (f"target 0x{ta:08X} is outside {fam}'s image: under this row's delta 0x{d:08X} it "
            f"would be foff 0x{toff:X}, past the image end 0x{imgsize:X}")
    runtxt = (f"the row's own segment run [0x{run[0]:X}, 0x{run[1]:X}) delta 0x{run[2]:08X}"
              if run is not None else "the row's own segment run (unrecorded)")
    if slus["decided"]:
        # byte-verified only when a real `jal` word was decoded: a symbol-only decision (the name
        # is in config/slus_006.14.symbols.txt, nothing reaches it) rests on the symbol file, not
        # on bytes, and must not claim otherwise.
        return {"kind": "cross-image", "image": "slus", "byte_verified": bool(slus["jal"]),
                "target_foff": hex(slus["foff"]),
                "jal_callers": [hex(x) for x in slus["jal"]],
                "jumpers": [hex(x) for x in slus["js"]],
                "proof": (f"{head}. It IS a function of the SLUS base executable "
                          f"(baserom/slus_006.14), co-resident with every overlay: "
                          f"{slus_note(slus)}. So the retail j/jal from this row is an inter-image "
                          f"call into the base executable, not a mis-split of this row. Clears L3, "
                          f"blocks L4.")}
    if own_jal or run_jal:
        return {"kind": "cross-image", "image": "absent", "byte_verified": bool(own_jal),
                "target_foff": None,
                "jal_callers": [hex(x) for x in sorted(set(run_jal) | set(own_jal))],
                "jumpers": [hex(x) for x in sorted(set(run_js) | set(own_j))],
                "proof": (f"{head}, and it is not SLUS code either ({slus_note(slus)}). But retail "
                          f"CALLS it: "
                          + ("the row's OWN retail bytes carry jal 0x%08X at " % ta
                             + ", ".join("0x%08X" % s for s in own_jal) + "; " if own_jal else "")
                          + f"{len(run_jal)} jal site(s) inside {runtxt} reach it"
                          + (" (e.g. 0x%08X)" % run_jal[0] if run_jal else "")
                          + f", against {len(run_js)} j site(s) there. A `jal` is a call and a call "
                            f"has a C producer -- a retail `j` is what has none, which is why this "
                            f"audit exists -- so this dependency is a call OUT of this container, "
                            f"into code that is on no image in the tree. Not a mis-split of this "
                            f"row. Clears L3, blocks L4.")}
    return {"kind": "unresolved", "byte_verified": False,
            "proof": (f"{head}; {slus_note(slus)}; and inside {runtxt} retail reaches it by "
                      f"{len(run_js)} j and {len(run_jal)} jal site(s)"
                      + (", the row's own bytes included (" +
                         ", ".join("%s at 0x%08X" % (op, s) for op, s in own_hits) + ")"
                         if own_hits else "")
                      + ". A `j` with no `jal` anywhere, and no image in which to read the "
                        "target's bytes, decides nothing: the target may be a real function of an "
                        "image we do not hold, or this row may be mis-split. Stays unresolved.")}


def kernel_verdict(ta, base, hits, foff):
    """Decide a target inside the fixed PlayStation kernel RAM window [KERNEL_LO, KERNEL_HI).
    PURE (no filesystem, no images, no `d`/segment delta at all) so it is directly unit-testable
    (tools/tests/test_split_audit_cross_image.py) and runs even where the row has no rowbase
    record -- decoding a `j`/`jal` word only needs the row's link address's top nibble, which is
    fixed (0x8) at every candidate base for a row living in KSEG0-mapped overlay/RAM space, so the
    decode does not depend on which base is right.

      hits  row_jumps(fam, r, base)[ta] for the declaring row -- [(op, source addr)] in its OWN
            bytes.  Only the row's OWN bytes are used: unlike the `absent` cross-image kind this
            needs no SLUS lookup and no run-level jumpers (those need `d`, which this verdict does
            not have).

    A `j` reaching the window is enough on its own here (unlike `absent`, a `jal` is not
    required): the window itself is the evidence -- BIOS/kernel RAM is never part of any overlay
    or of SLUS, so any retail transfer into it is decided by address alone, not by call-vs-jump.
    No hits: `unresolved` -- a kernel-range target with nothing in the row's own bytes reaching it
    decides nothing (2026-09-22, `hits` never comes back empty for the three real town rows this
    kind exists for: func_808B8184, func_808B85F0, func_808BB138)."""
    if not hits:
        return {"kind": "unresolved", "byte_verified": False,
                "proof": (f"target 0x{ta:08X} is inside the fixed PlayStation kernel RAM window "
                          f"[0x{KERNEL_LO:08X}, 0x{KERNEL_HI:08X}), but no j/jal word in the row's "
                          f"own retail bytes targets it: nothing decides this dependency. Stays "
                          f"unresolved.")}
    return {"kind": "cross-image", "image": "kernel", "byte_verified": True,
            "row_jump_offsets": [f"{op}@row+0x{src - base:X}" for op, src in hits],
            "proof": (
                f"target 0x{ta:08X} is a fixed PlayStation kernel address (BIOS/kernel RAM, "
                f"[0x{KERNEL_LO:08X}, 0x{KERNEL_HI:08X})), never part of any overlay or of SLUS, "
                f"reached by "
                + ", ".join(f"{op} at row +0x{src - base:X} (file 0x{foff + (src - base):X})"
                            for op, src in hits)
                + ". The word is base-independent: its top nibble is fixed at every candidate "
                  "base for this row. Not a mis-split of this row. Clears L3, blocks L4.")}


_RUNIDX = {}
def run_jumps(fam, run):
    """{absolute target: ([`j` srcs], [`jal` srcs])} for ONE merged segment run of a container.
    Address-keyed, which is sound inside a run and only inside a run: one run has one delta, so
    every word there links where the run says and its `j`/`jal` field decodes to an unambiguous
    absolute target.  Across a whole container the same address belongs to several overlay
    segments -- the very thing index_image's file-offset key exists to prevent -- so this is never
    called for anything but the DECLARING row's own run.  Cached per (family, run)."""
    key = (fam, run)
    if key not in _RUNIDX:
        idx = {}
        img = IMAGES.get(fam)
        if img is not None and run is not None:
            data = _image(img)
            st, en, d = run
            for foff in range(st, min(en, len(data) - 3), 4):
                w = int.from_bytes(data[foff:foff + 4], "little")
                op = w >> 26
                if op != 2 and op != 3:
                    continue
                src = (foff + d) & 0xFFFFFFFF
                tgt = ((src + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                e = idx.get(tgt)
                if e is None:
                    e = idx[tgt] = ([], [])
                e[0 if op == 2 else 1].append(src)
        _RUNIDX[key] = idx
    return _RUNIDX[key]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--container"); ap.add_argument("--limit", type=int)
    ap.add_argument("--out", default=str(LEDGER / "split_audit.jsonl"))
    a = ap.parse_args()
    t0 = time.time()
    allrows = list(rows())
    bycont = {}
    for r in allrows:
        bycont.setdefault(r["container"], []).append(r)
    syms = sym_sets()
    now = time.strftime("%Y-%m-%dT%H:%M:%S")

    segs, index, imgsize = {}, {}, {}
    for fam, p in IMAGES.items():
        if a.container and fam != a.container:
            continue
        if not p.exists():
            continue
        segs[fam] = Segments(fam, bycont.get(fam, []))
        index[fam], imgsize[fam] = index_image(p, segs[fam])
        print(f"{fam}: indexed {len(index[fam])} targets in {time.time()-t0:.0f}s", flush=True)

    out, cand = [], {}
    already = set()
    fm = ROOT / "config/noreturn_false_members.jsonl"
    if fm.exists():
        for line in fm.read_text(errors="replace").splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                try:
                    j = json.loads(line); already.add((j.get("family"), j.get("func")))
                except json.JSONDecodeError:
                    pass
    todo = [r for r in allrows if not a.container or r["container"] == a.container]
    if a.limit:
        todo = todo[:a.limit]
    for r in todo:
        fam = r["container"]
        cp = ROOT / "src" / fam / Path(r["c_path"]).name
        p = cp if cp.exists() else raw_path(r)
        if not p.exists():
            continue
        raw = p.read_text(errors="replace")
        text = compiled_text(raw)
        deps = set(tail_jump_targets(r, raw))
        fam_syms = syms.get(fam, set()) | (syms.get("main", set()) if fam in ("main", "slus") else set())
        if not deps:
            continue
        hand_asm = asm_blocker(text)
        m = re.match(r"func_([0-9A-F]{8})$", r.get("true_name") or r["func"] or "")
        d = segs[fam].delta(r["foff"]) if (fam in segs and r.get("foff") is not None) else None
        base = (r["foff"] + d) & 0xFFFFFFFF if d is not None else (int(m.group(1), 16) if m else None)
        for t in sorted(deps):
            ta = int(t[5:], 16)
            rec = {"schema": "azure-clean.split-audit.v1", "id": r["id"], "target": t,
                   "target_addr": hex(ta), "kind": None, "jumpers": [], "jal_callers": [],
                   "true_base": hex(base) if base is not None else None, "proof": "", "at": now}
            if hand_asm:
                rec["kind"] = "asm"; rec["proof"] = f"hand-written asm row ({hand_asm}); no C producer expected"
            elif base is not None and base <= ta < base + r["size"]:
                # a text dependency is not a mis-split unless the row's RETAIL BYTES really jump
                # there: find a j/jal word inside this row whose absolute target is `ta`
                hits = row_jumps(fam, r, base).get(ta, [])
                rec["byte_verified"] = bool(hits)
                if hits:
                    rec["kind"] = "intra"
                    rec["row_jump_offsets"] = [f"{op}@row+0x{src - base:X}" for op, src in hits]
                    rec["proof"] = (f"target 0x{ta:08X} lies inside the row's own extent "
                                    f"[0x{base:08X}, 0x{base + r['size']:08X}) (+0x{ta - base:X} of "
                                    f"{r['size']} B) AND the row's own retail bytes jump there: "
                                    + ", ".join(f"{op} at row +0x{src - base:X} "
                                                f"(file 0x{r['foff'] + (src - base):X})" for op, src in hits))
                else:
                    rec["kind"] = "text-only"
                    rec["proof"] = (f"target 0x{ta:08X} lies inside the row's own extent "
                                    f"[0x{base:08X}, 0x{base + r['size']:08X}) (+0x{ta - base:X}), but NO "
                                    f"j/jal word in the row's own retail bytes targets it: the C "
                                    f"dependency has no retail producer, so it is not a mis-split")
            elif base is not None and KERNEL_LO <= ta < KERNEL_HI:
                # A fixed PlayStation kernel RAM address, decided by the row's OWN retail bytes --
                # no rowbase record needed (base-independent: see KERNEL_LO/KERNEL_HI and
                # kernel_verdict() above), so this check runs even where `d` (the rowbase/segment
                # delta) is None.
                rec.update(kernel_verdict(ta, base, row_jumps(fam, r, base).get(ta, []), r["foff"]))
            elif d is None:
                rec["kind"] = "unresolved"
                rec["proof"] = ("no rowbase record and no registered true_name for "
                                f"{fam} foff 0x{r['foff']:X}: the row links at its synthetic base, "
                                "so the target address cannot be placed in the image")
            else:
                toff = (ta - d) & 0xFFFFFFFF
                run = segs[fam].run(r["foff"])
                if toff >= imgsize.get(fam, 0):
                    # Outside this container's image under the row's own delta.  Before giving up,
                    # look where the answer can still be: (a) the SLUS base executable, resident
                    # under EVERY overlay, and (b) what retail itself does at the call site -- a
                    # `jal` is a call, and a call has a C producer, which is exactly what a retail
                    # `j` lacks and what this audit exists to test.  Sources are taken only from
                    # the row's OWN segment run; address-keying a whole container is the
                    # cross-segment bug.  See offimage_verdict().
                    rjs, rjal = (run_jumps(fam, run).get(ta, ([], [])) if run is not None
                                 else ([], []))
                    own = row_jumps(fam, r, base).get(ta, []) if base is not None else []
                    rec.update(offimage_verdict(fam, ta, d, toff, imgsize.get(fam, 0),
                                                own, run, rjal, rjs, slus_lookup(ta)))
                elif run is not None and not (run[0] <= toff < run[1]):
                    # the row's delta stops at its own run; past it the file offset belongs to a
                    # different overlay segment linking at a different base, so neither the bytes
                    # nor the j/jal sites there are this target's.  Record the verdict, not them.
                    other = segs[fam].run(toff)
                    rec["kind"] = "cross-segment"
                    rec["byte_verified"] = False
                    rec["target_foff"] = hex(toff)
                    rec["row_run"] = [hex(run[0]), hex(run[1]), f"0x{run[2]:08X}"]
                    rec["proof"] = (
                        f"target 0x{ta:08X} is outside the declaring row's own segment run "
                        f"{fam} foff [0x{run[0]:X}, 0x{run[1]:X}) delta 0x{run[2]:08X}. Under that "
                        f"delta it would be foff 0x{toff:X}, which lies "
                        + (f"in a DIFFERENT run [0x{other[0]:X}, 0x{other[1]:X}) whose delta is "
                           f"0x{other[2]:08X}, where the code links at 0x{(toff + other[2]) & 0xFFFFFFFF:08X}, "
                           f"not 0x{ta:08X}" if other is not None else
                           "in no registered run at all (un-split code or data)")
                        + ". A row's delta is only valid inside its own run, so this container "
                          "cannot say what is at that address and no j/jal site found there "
                          "belongs to this target. Not a mis-split of this row.")
                else:
                    js, jals = index[fam].get(toff, ([], []))
                    rec["jumpers"] = [hex(x) for x in sorted(set(js))]
                    rec["jal_callers"] = [hex(x) for x in sorted(set(jals))]
                    rec["byte_verified"] = bool(js or jals)
                    if jals:
                        known = sum(1 for x in set(jals) if segs[fam].in_known((x - d) & 0xFFFFFFFF))
                        rec["kind"] = "extern-jal"
                        rec["proof"] = (f"target 0x{ta:08X} = {fam} foff 0x{toff:X}, outside the row; "
                                        f"retail reaches it by jal from {len(set(jals))} site(s) "
                                        f"({known} inside a registered row, the rest in un-split code "
                                        f"of the same module; e.g. {hex(sorted(set(jals))[0])}) -- a "
                                        f"returning function, so a noreturn/sibcall membership for it "
                                        f"is a false member")
                    elif js:
                        rec["kind"] = "extern-j-only"
                        rec["proof"] = (f"target 0x{ta:08X} = {fam} foff 0x{toff:X}, outside the row; "
                                        f"retail reaches it only by j, from {len(set(js))} site(s) "
                                        f"-- a shared tail fragment, most likely a mis-split function")
                    else:
                        rec["kind"] = "unresolved"
                        rec["proof"] = (f"target 0x{ta:08X} = {fam} foff 0x{toff:X}: no j and no jal "
                                        "reaches it from any base-resolvable code in the image")
            out.append(rec)
            if rec["kind"] == "extern-jal" and t in fam_syms and (fam, t) not in already:
                k = (fam, t)
                if k in cand:
                    cand[k]["declarers"].append(r["id"])
                else:
                    js_l = sorted(set(js)); jal_l = sorted(set(jals))
                    cls = ("CLASS 1 (BOTH-WAYS CONFLICT)" if js_l else
                           "JAL-ONLY (no tail `j` exists anywhere in the image)")
                    cand[k] = {"schema": "azure-clean.noreturn-false-member.v1", "family": fam, "func": t,
                               "declarers": [r["id"]],
                               "proof": (
                                   f"{cls}. RETAIL BYTE DECODE {now} (tools/split_audit.py over "
                                   f"{IMAGES[fam].name}; every address resolved through its own source's "
                                   f"config/overlays/{fam}.rowbase.jsonl delta and the index keyed on "
                                   f"target FILE OFFSET, so same-named code in another segment is never "
                                   f"counted): retail reaches {t} (= {fam} file 0x{toff:X}) by `jal` from "
                                   f"{len(jal_l)} site(s) [{', '.join(hex(x) for x in jal_l[:8])}"
                                   f"{', ...' if len(jal_l) > 8 else ''}] and by `j` from {len(js_l)} "
                                   f"site(s) [{', '.join(hex(x) for x in js_l[:8])}"
                                   f"{', ...' if len(js_l) > 8 else ''}], over the base-resolvable code of "
                                   f"the whole container. A `jal` is a call whose result the caller may "
                                   f"use; the family-wide maspsx LEAD 18 jal->j rewrite would turn it into "
                                   f"a tail jump, and a name-keyed census cannot distinguish the two. Each "
                                   f"declaring TU keeps its own noreturn attribute, so its own tail call is "
                                   f"unaffected. Declaring row(s) ")}
    Path(a.out).write_text("".join(json.dumps(x) + "\n" for x in out))
    cp = Path(a.out).with_name("split_audit_false_members.candidates.jsonl")
    lines = []
    for k in sorted(cand):
        v = cand[k]
        d = sorted(set(v.pop("declarers")))
        v["proof"] += ", ".join(d) + ". NOT applied: candidate only, config/ is not edited here."
        lines.append(json.dumps(v))
    cp.write_text("".join(x + "\n" for x in lines))
    cand = lines
    import collections
    c = collections.Counter((x["id"].split("/")[0], x["kind"]) for x in out)
    print(f"{len(out)} records over {len({x['id'] for x in out})} rows in {time.time()-t0:.0f}s -> {a.out}")
    for k in sorted(c): print(f"  {k[0]:9s} {k[1]:14s} {c[k]}")
    print(f"{len(cand)} candidate false-member lines -> {cp} (config/ NOT touched)")


if __name__ == "__main__":
    main()
