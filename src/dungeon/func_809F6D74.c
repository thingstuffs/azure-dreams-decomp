#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

typedef struct {
    u8 pad[0x13C];
    s32 value;
} Scratchpad;

typedef struct {
    u8 pad[0x5218];
    s16 value;
} GlobalPage;

extern s16 D_80175218[];
extern void func_800453E0(void *, s32, Entry *, s16);

s32 func_80174574(void *arg0, s32 arg1, Entry *arg2, s32 arg3)
{
    void *base = arg0;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;
    GlobalPage *global_page =
        (GlobalPage *)0x80170000;
    Entry *next;

    ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(global_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    for (;;) {
        scratch->value = global_page->value;

        if (!(arg2->unk14 & 0x80)) {
            func_800453E0(base, arg1, arg2, arg2->unk06);
        }

        next = *(Entry **)((u8 *)base - 8);
        if (next == 0) {
            return 0;
        }
        base = (u8 *)next + 0x20;
        arg1 = (s32)next->unk08;
        arg2 = next->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
   ASM_KEEP breaks absolute-page constant folding; the guarded s1 page pin plus kept
   scratch base preserves the retail 0x20-frame save/init order s0, s2, s1, ra. */
