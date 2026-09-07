#include "common.h"

extern u16 D_80083462;
extern s32 D_800E296C;

extern s32 func_800A2B5C(void *);
extern void func_800A4ACC(void *);

void func_801754AC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 *page;
    s32 global_flags;
    u16 actor_flags;

    *(u8 *)((u8 *)arg3 + 0x71) &= 0x7F;
    if (!(D_80083462 & 0x2000) &&
        (func_800A2B5C(arg3) << 16) == 0 &&
        (func_800A2B5C(arg3) << 16) == 0) {
        *(s32 *)((u8 *)arg0 + 0x8C) = 0;
        *(u8 *)((u8 *)arg0 + 0x9A) = 0x17;
        *(u8 *)((u8 *)arg0 + 0x9B) = 0;
        *(s16 *)((u8 *)arg0 + 0x96) = 0;
        *(u8 *)((u8 *)arg0 + 0xB3) = 0;
        *(u8 *)((u8 *)arg0 + 0xB1) = 0;
        *(u8 *)((u8 *)arg0 + 0xB2) = 0;
        *(s32 *)((u8 *)arg3 + 0x1C) &= 0xFFFBFFFF;
        page = (s32 *)0x800E0000;
        global_flags = page[0x296C / 4];
        actor_flags = *(u16 *)((u8 *)arg0 + 0x98);
        global_flags |= 0x40;
        actor_flags |= 8;
        page[0x296C / 4] = global_flags;
        *(u16 *)((u8 *)arg0 + 0x98) = actor_flags;
        func_800A4ACC(arg3);
        *(u8 *)((u8 *)arg3 + 0x6D) -= 1;
    }
}

/* MECHANISM: The true one-argument callee ABI frees a1 for the 0x800E0000 page base.
   Separate global_flags and actor_flags loads overlap the memory reads, eliminating
   the rematerialized page word and load-delay nop that caused the branch cascade. */
