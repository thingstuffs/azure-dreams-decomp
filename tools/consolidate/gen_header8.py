"""gen_header8.py: write inc/shared/game_work.h - GameWork with the gameWork+0x18..0x1DB block as a named member
   (GameView view: header 0x000..0x0B3 + ViewSlot slot[4] at 0x0B4).  Field types/names come from the landed flat
   header; offsets are rebased (sub offset = gameWork offset - 0x18); slot fields come from slot 0's flat fields.
   Also writes tools/respell_map8.json: flat field name -> new member path (for respell8.py)."""
import re, json
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
src = (REPO / "include/shared/game_work.h").read_text()
F = []
for m in re.finditer(r"/\* 0x([0-9A-F]{3}) \*/ ([^\n]+?)[ \t]*;(?:[ \t]*(/\*[^\n]*?\*/))?[ \t]*\n", src):
    off = int(m.group(1), 16); decl = m.group(2).strip(); cm = m.group(3) or ""
    mm = re.match(r"(.*?)\s*\b(\w+)(\[0x[0-9A-F]+\])?$", decl)
    F.append((off, mm.group(1).strip(), mm.group(2), mm.group(3) or "", cm))
SUB0, SLOT0, SLOTN, SLOTSZ, END = 0x18, 0xCC, 4, 0x44, 0x1DC
SLOTNAMES = {0x00: "callback", 0x04: "unk_04", 0x24: "unk_24"}
def fl(off, ty, name, arr, cm, width=24):
    d = "%s %s%s;" % (ty, name, arr)
    return "    /* 0x%03X */ %-*s %s" % (off, width, d, cm)
top = [f for f in F if f[0] < SUB0 or f[0] >= END]
hdr = [f for f in F if SUB0 <= f[0] < SLOT0]
s0 = [f for f in F if SLOT0 <= f[0] < SLOT0 + SLOTSZ]
rmap = {}
out_hdr = []
for off, ty, name, arr, cm in hdr:
    so = off - SUB0
    if name.startswith("pad_"): nn = "pad_%03X" % so
    elif name == "viewAngle": nn = name
    else: nn = "unk_%03X" % so
    if not name.startswith("pad_"): rmap[name] = "view." + nn
    out_hdr.append(fl(so, ty, nn, arr, cm))
out_slot = []
slot_fields = {}
for off, ty, name, arr, cm in s0:
    so = off - SLOT0
    nn = ("pad_%02X" % so) if name.startswith("pad_") else SLOTNAMES.get(so, "unk_%02X" % so)
    if not name.startswith("pad_"): slot_fields[so] = nn
    out_slot.append(fl(so, ty, nn, arr, cm.replace("rows)", "rows, slot 0)") if cm else cm, 20))
# slot 1..3 flat fields (callbacks at +0): map onto slot[k]
for off, ty, name, arr, cm in F:
    if SLOT0 <= off < END and not name.startswith("pad_"):
        k, so = divmod(off - SLOT0, SLOTSZ)
        if so not in slot_fields: raise SystemExit("slot %d field +0x%02X (%s) has no slot-0 field" % (k, so, name))
        rmap[name] = "view.slot[%d].%s" % (k, slot_fields[so])
rmap["unk_018"] = "view.unk_000"
json.dump(rmap, open(LANE / "tools/respell_map8.json", "w"), indent=0, sort_keys=True)
H = """#ifndef SHARED_GAME_WORK_H
#define SHARED_GAME_WORK_H

/* ViewSlot: one of four 0x44-byte records at GameView+0xB4 (gameWork+0xCC/0x110/0x154/0x198).  One record type:
 * slus/w_8004D7A8 / w_8004D7E8 move whole records between slot 0 <-> 1 and 2 <-> 3 through func_8004D75C(dst, src);
 * slus/w_80040BB4 clears all four `callback` words.  `callback` (+0x00): code2 func_8004D0C8 / func_8004D110 store a
 * function there together with the record's data (+0x24 / +0x04); w_8004D294 hands &slot[0].unk_04 (position) and
 * &slot[2].unk_04 (rotation) to func_8004D1EC as transition targets.  Field widths are slot 0's retail accesses
 * (slots 1..3 are reached only at +0x00).  Other fields stay unk_. */
typedef struct ViewSlot {
%s
} ViewSlot;

/* GameView: gameWork+0x018..0x1DB (0x1C4 bytes; r78 phase 8, OPEN_ITEMS #2).  A real sub-object: retail keeps its
 * address (%%hi(D_80083160+24)) in a register across calls and passes it to func_800997FC / func_80042900
 * (dungeon/func_800C6654, func_800C1E70, func_800B2614: flat gameWork fields miss by 19-63 words), and
 * slus/w_8004D5D0's TU declares it on its own at 0x80083178 (it keeps that local extern, D_80083178).
 * "View": 0x094..0x0B3 are four x,y,z,pad short vectors (8 bytes each; slus/w_80044724 copies them as 8-byte
 * aggregates into D_80083CE8, game.h struct S_80083178State) from which slus/w_8004D4AC builds the GTE view
 * transform (RotMatrix of 0x09C and 0x0AC, RotTrans of 0x094 and of -0x0A4..0x0A8, CompMatrix, SetRotMatrix /
 * SetTransMatrix); w_8004D294 sets position (0x0A4) and rotation (0x0AC, 12-bit angles) targets through the
 * slots; w_8004D5D0 loads 0x0A4..0x0A8 from D_80083780's integer x/y/z.
 *   viewAngle (0x0B0 = vector 3's z = gameWork+0xC8): read-only in C (lh 1,134 sites):
 *   `(viewAngle + obj->angle + 0x100) >> 9 & 7` picks an object's 8-way directional sprite (0x1000 = one turn).
 *   0x090..0x092: three bytes read as an r, g, b triple into primitives and faded in/out by +-2/4 (unnamed).
 * gcc 2.7.2 has no anonymous structs, so every field here is spelled gameWork.view.<field>. */
typedef struct GameView {
%s
    /* 0x0B4 */ ViewSlot slot[4];
} GameView;

/* gameWork: the global work block at 0x80083160 (SLUS .bss), used by every binary (1,095 rows reference an address
 * in 0x80083160..0x8008335F).  ONE object: rows reach offsets 0x000..0x1FC from one lui/addiu base of 0x80083160
 * (census/g83160w.jsonl, r78 phase 3).  Field widths/signs are the retail access widths (lh => signed; an lhu-only
 * slot is unsigned; store-only slots default to signed).  Fields stay unk_ until their meaning is proven.
 *   0x000/0x008/0x010: pointers (lw; 0x000 is the "current state" pointer slus/w_80045340 follows to +0x8D0).
 *   0x018..0x1DB: `view` (GameView above; game.h's old struct S_80083178 described the same bytes).
 *   Union sites (a wider or narrower access than the field; reached through a view at the use): 0x004 (2 lbu),
 *   0x008 (1 lhu), view.0x090 (lw/sw over the three bytes), view.0x094/0x098/0x0AC/0x0B0 (a word copy).
 * Size: at least 0x200 (last access 0x1FC); never small data at any -G. */
typedef struct GameWork {
%s
    /* 0x018 */ GameView view;
%s
} GameWork;

extern GameWork gameWork;

#endif
""" % ("\n".join(x.rstrip() for x in out_slot), "\n".join(out_hdr), "\n".join(fl(*f) for f in top if f[0] < SUB0), "\n".join(fl(*f) for f in top if f[0] >= END))
(LANE / "inc/shared/game_work.h").write_text(H)
print(len(rmap), "respell entries")
