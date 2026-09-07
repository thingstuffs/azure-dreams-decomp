#include "common.h"

extern void func_800C2E84();
extern void func_800C4174();
extern u8 D_80082660;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_800C70B8(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, FIELD(FIELD(arg0, void *, 0x80), s32, 4));
    *(&D_80082660 + (FIELD(arg0, s32, 0x60) * 8)) = 0;
    FIELD(arg0, s16, 0x72) = 0x200;
    func_800C4174(arg0, arg1, arg2);
}

/* MECHANISM: The three incoming values remain live across the first call, forcing
   the 0x20 frame and s0/s2/s1 holds; the first call keeps its real three-argument ABI.
   D_80082660 is byte-wide, so the indexed table clear emits sb rather than sw. */
