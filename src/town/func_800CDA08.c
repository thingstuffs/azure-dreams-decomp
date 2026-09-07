#include "common.h"

typedef struct {
    u8 field0;
    u8 pad1;
    u8 field2;
    u8 pad3[5];
} S_80082660;

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern S_80082660 D_80082660[];
extern u8 D_800CB0F0[];
extern u8 D_800D68D4[];

void func_800CB168(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, D_800D68D4);
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].field0 = 0;
    *(void **)((u8 *)arg0 + 0x54) = D_800CB0F0;
    *(s16 *)((u8 *)arg0 + 0x6C) = 6;
    *(u8 *)((u8 *)arg0 + 0x96) = D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].field2;
}

/* MECHANISM: The three-argument ABI keeps the live value in incoming $a2 despite the unused middle parameter.
   GCC then moves $a2 to call argument $a1 and materializes D_800D68D4 through $v0, closing all three residues.
   The struct-array accesses preserve retail's 24-byte frame, sole $s0 hold, and reused D_80082660 base. */
