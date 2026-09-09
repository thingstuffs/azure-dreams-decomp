#include "common.h"

typedef struct {
    u8 pad0[12];
    u8 *entries;
    u8 pad10[4];
} DungeonGroup;

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} DungeonRect;

typedef struct {
    u8 pad0[6];
    u8 px;
    u8 py;
    u8 pad8[16];
} DungeonSpot;

typedef struct {
    u8 kind;
    u8 f1;
    u8 f2;
    u8 f3;
} DungeonSlot;

extern void func_8009A21C(u8, u8, s32);
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);
extern DungeonGroup D_80073414[];
extern DungeonSlot D_800E3648[];
extern DungeonSpot D_800E39C8[];

/* Populate dungeon slots at random eligible positions within the rectangle. */
void func_8001D0F4(DungeonRect *rect)
{
    u16 tile_flags;
    s32 slot_limit_calc;
    register s32 slot_limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 item_kind ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 stored_kind;
    s32 special_roll;
    s32 slot_index;
    u32 kind_roll;
    u16 item_flags;
    DungeonGroup *item_category_table;
    u8 *spots_base;
    s32 spot_offset;
    register DungeonSpot *spot ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 x_offset;
    u32 y_offset;

    special_roll = func_800A6D30() & 0xFF;
    slot_limit_calc = ((rect->height * rect->width) >> 3) +
                 (func_800A6D30() & 7);
    slot_limit = slot_limit_calc;
    ASM_KEEP(slot_limit);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if ((s16)slot_limit_calc >= 29) {
        slot_limit = 28;
    }
    slot_index = (s16)slot_limit;

    if (slot_index >= 0) {
        item_category_table = D_80073414;
        ASM_USE2(item_category_table, special_roll);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        spots_base = (u8 *)D_800E39C8;
        spot_offset = slot_index * 24;
        spot = (DungeonSpot *)(spots_base + spot_offset);
        ASM_USE2(spot_offset, spots_base);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        do {
            x_offset = func_800A6DA4(0, (rect->width - 1) & 0xFFFF) & 0xFFFF;
            y_offset = func_800A6DA4(0, (rect->height - 1) & 0xFFFF) & 0xFFFF;
            func_8009A350((s16)(rect->x + x_offset - 1),
                          (s16)(rect->y + y_offset), 0, &tile_flags);
            if (!(tile_flags & 0x8820)) {
                spot->px = (u8)rect->x + x_offset;
                spot->py = (u8)rect->y + y_offset;
                if (special_roll == 0) {
                    D_800E3648[slot_index].kind = 7;
                } else {
                    kind_roll = func_800A6D30() & 0xFFFF;
                    item_kind = (kind_roll % 19) + 1;
                    ASM_KEEP(item_kind);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    item_flags = *(u16 *)(item_category_table[21].entries +
                                           ((s16)item_kind * 12));
                    stored_kind = item_kind;
                    if ((item_flags & 0x3000) == 0x3000) {
                        goto next_spot;
                    }
                    D_800E3648[slot_index].kind = stored_kind;
                       /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                }
                D_800E3648[slot_index].f1 = 0x15;
                D_800E3648[slot_index].f3 = 0x80;
                D_800E3648[slot_index].f2 = 0;
                func_8009A21C(spot->px, spot->py, 0x20);
            }
next_spot:
            spot--;
            slot_index--;
        } while (slot_index >= 0);
    }
}

/* MECHANISM (byte-exact @2.8.1-G0):
   1. The $s2 pointer (step -4) is NOT a source pointer: it is a compiler-made
      GIV from struct-array indexing `D_800E3648[count]` (24-/4-byte struct
      typing keeps both bases at +0, so retail's 6/7 and 0..3 displacements are
      addressing offsets, not rebases). The $s3 pointer (step -24) IS a source
      pointer -- that mix is what orders the two preheader inits (user code,
      then the giv init) and the two loop-bottom updates the way retail has
      them; making both givs emits the stride-4 pair first, both source
      pointers rebases $s3 to +7 and costs a word.
   2. `entry` is pinned to $s3 because the giv (7 weighted refs) otherwise
      outranks it; `off = count*24` + ASM_USE2(off, base) stops gcc computing
      the index inside the pinned destination, and ASM_USE2(groups,
      first_random) materialises the D_80073414 page first while keeping
      first_random's allocation priority at $s6.
   3. The 28-clamp: merge value pinned to $v0 with ASM_KEEP right after the
      copy -- the fence stops CSE feeding the copy back into the compare, which
      is what produces retail's `move v0,v1`, in-place `sll v0,v0,16` on both
      arms, and the single merged `sra s4,v0,16`.
   4. xoff/yoff MUST NOT be pinned: a hard-reg def makes gcc's scheduler hoist
      `andi sN,v0,0xffff` ahead of the next call's `move aN,zero`. Depinning
      them (they land in $s1/$s0 naturally) closed the last 6 words. */
