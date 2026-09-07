#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

void func_800AEBC4(void *arg0, void *arg1, void *arg2, void *arg3,
                   s32 arg4, s32 arg5) {
    register void *tail ASM_REG("$8") = arg0;
    register u8 *base0 ASM_REG("$4");
    register u8 *base1 ASM_REG("$3");
    register s32 word ASM_REG("$2");
    register s32 x ASM_REG("$9");
    register s32 y ASM_REG("$10");
    s32 *stack = __builtin_frame_address(0);

    ASM_KEEP(tail);
    ASM_UNDEF(base0);
#ifdef NON_MATCHING
    base0 = (u8 *)D_8002E5D8 + 0x1A28;
#else
    base0 = (u8 *)0x80030000;
#endif
    ASM_KEEP(base0);
    ASM_UNDEF(word);
    word = FIELD(base0, s32, -0x1A28);
    ASM_UNDEF(x);
#ifdef NON_MATCHING
    x = arg4;
#else
    x = stack[4];
#endif
    ASM_KEEP(x);
    ASM_UNDEF(y);
#ifdef NON_MATCHING
    y = arg5;
#else
    y = stack[5];
#endif
    ASM_KEEP(y);
    base0 -= 0x1A28;
    ASM_KEEP(base0);
    FIELD(arg2, s32, 0) = word;

    word = FIELD(base0, s32, 4);
    ASM_KEEP(word);
    FIELD(arg2, s32, 4) = word;

    word = FIELD(base0, s32, 8);
    ASM_UNDEF(base1);
#ifdef NON_MATCHING
    base1 = (u8 *)D_8002E5E8 + 0x1A18;
#else
    base1 = (u8 *)0x80030000;
#endif
    ASM_KEEP(base1);
    FIELD(arg2, s32, 8) = word;

    word = FIELD(base0, s32, 0xC);
    ASM_UNDEF(base0);
    base0 = (u8 *)(u32)FIELD(base1, s32, -0x1A18);
    base1 -= 0x1A18;
    ASM_KEEP(base1);
    FIELD(arg2, s32, 0xC) = word;
    FIELD(arg3, s32, 0) = (s32)(u32)base0;

    word = FIELD(base1, s32, 4);
    ASM_KEEP(word);
    FIELD(arg3, s32, 4) = word;
    word = FIELD(base1, s32, 8);
    ASM_KEEP(word);
    FIELD(arg3, s32, 8) = word;

    FIELD(arg1, void *, 8) = arg3;
    ASM_UNDEF(base1);
    base1 = arg3;
    ASM_KEEP(base1);
    word = -0x400;
    FIELD(arg1, void *, 4) = arg2;
    FIELD(arg1, s32, 0) = 0;
    FIELD(base1, s16, 2) = (s16)word;

    word = FIELD(arg1, s32, 4);
    ASM_KEEP(word);
    FIELD((void *)(u32)word, s16, 8) = (s16)x;
    word = FIELD(arg1, s32, 4);
    ASM_KEEP(word);
    FIELD((void *)(u32)word, s16, 0xA) = (s16)y;
    ASM_KEEP(y);
    word = FIELD(arg1, s32, 4);
    ASM_KEEP(word);
    base0 = (u8 *)0x400;
    ASM_KEEP(base0);
    FIELD((void *)(u32)word, s16, 0xC) = (s16)(u32)base0;
    base1 = (u8 *)(u32)FIELD(arg1, s32, 4);
    ASM_KEEP(base1);
    word = 4;
    FIELD(base1, u8, 0xF) = (u8)word;

    FIELD(tail, s16, 0xC) = (s16)x;
    FIELD(tail, s16, 0xE) = (s16)y;
    FIELD(tail, s16, 0x10) = (s16)(u32)base0;
    ASM_KEEP(base0);
    word = -0x60;
    if (x < 0) {
        word = 0x30;
    }
    word -= x;
    FIELD(tail, s16, 0x14) = (s16)word;
    word = -0x40 - y;
    FIELD(tail, s16, 0x16) = (s16)word;
    word = -0x200;
    ASM_KEEP(word);
    FIELD(tail, s16, 0x18) = (s16)word;
}

/* MECHANISM: Frameless leaf with ABI stack words held in t1/t2 and arg0 held in t0.
   Explicit page-base lifetimes put the two template copies in a0/v1, while the
   post-copy hard-register boundary forces the retail a3-to-v1 secondary pointer. */
