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

extern void func_8001D2C4(void) __attribute__((noreturn));
extern void func_8009A21C(u8, u8, s32);
extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A6D30(void);
extern s32 func_800A6DA4(s32, s32);
extern DungeonGroup D_80073414[];
extern DungeonSlot D_800E3648[];
extern DungeonSpot D_800E39C8[];

void func_8001D0F4(DungeonRect *arg0)
{
    u16 tile;
    s32 count_calc;
    register s32 count_value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 stored_value;
    s32 first_random;
    s32 count;
    u32 random_value;
    u16 table_flags;
    DungeonGroup *groups;
    u8 *base;
    s32 off;
    register DungeonSpot *entry ASM_REG("$19");   /* MATCH pin: load-bearing for the whole function shape */
    u32 xoff;
    u32 yoff;

    first_random = func_800A6D30() & 0xFF;
    count_calc = ((arg0->height * arg0->width) >> 3) +
                 (func_800A6D30() & 7);
    count_value = count_calc;
    ASM_KEEP(count_value);   /* MATCH pin: retail register colouring depends on it */
    if ((s16)count_calc >= 29) {
        count_value = 28;
    }
    count = (s16)count_value;

    if (count >= 0) {
        groups = D_80073414;
        ASM_USE2(groups, first_random);   /* MATCH pin: keeps a statement from moving across a call/branch */
        base = (u8 *)D_800E39C8;
        off = count * 24;
        entry = (DungeonSpot *)(base + off);
        ASM_USE2(off, base);   /* MATCH pin: keeps a constant in a register as retail does */
        do {
            xoff = func_800A6DA4(0, (arg0->width - 1) & 0xFFFF) & 0xFFFF;
            yoff = func_800A6DA4(0, (arg0->height - 1) & 0xFFFF) & 0xFFFF;
            func_8009A350((s16)(arg0->x + xoff - 1),
                          (s16)(arg0->y + yoff), 0, &tile);
            if (!(tile & 0x8820)) {
                entry->px = (u8)arg0->x + xoff;
                entry->py = (u8)arg0->y + yoff;
                if (first_random == 0) {
                    D_800E3648[count].kind = 7;
                    func_8001D2C4();
                }

                random_value = func_800A6D30() & 0xFFFF;
                value = (random_value % 19) + 1;
                ASM_KEEP(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                table_flags = *(u16 *)(groups[21].entries +
                                       ((s16)value * 12));
                stored_value = value;
                if ((table_flags & 0x3000) != 0x3000) {
                    D_800E3648[count].kind = stored_value;
                    ASM_KEEP(stored_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    D_800E3648[count].f1 = 0x15;
                    D_800E3648[count].f3 = 0x80;
                    D_800E3648[count].f2 = 0;
                    func_8009A21C(entry->px, entry->py, 0x20);
                }
            }
            entry--;
            count--;
        } while (count >= 0);
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
