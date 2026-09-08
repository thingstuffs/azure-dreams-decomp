#include "common.h"

typedef struct S_800AEBC4_0_pre {
    s32 unk_00;
    u8 pad_04[0x1A24];
} S_800AEBC4_0_pre;   /* the 0x1A28 bytes before base0 in func_800AEBC4, addressed as base0[-1] */

typedef struct S_800AEBC4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AEBC4_0;   /* base0 in func_800AEBC4 */

typedef struct S_800AEBC4_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AEBC4_1;   /* arg2 in func_800AEBC4 */

typedef struct S_800AEBC4_2_pre {
    s32 unk_00;
    u8 pad_04[0x1A14];
} S_800AEBC4_2_pre;   /* the 0x1A18 bytes before base1 in func_800AEBC4, addressed as base1[-1] */

typedef struct S_800AEBC4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
} S_800AEBC4_2;   /* base1 in func_800AEBC4 */

typedef struct S_800AEBC4_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800AEBC4_3;   /* arg3 in func_800AEBC4 */

typedef struct S_800AEBC4_4 {
    s32 unk_00;
    union { void * s; s32 u; } unk_04;   /* accessed as both */
    void * unk_08;
} S_800AEBC4_4;   /* arg1 in func_800AEBC4 */

typedef struct S_800AEBC4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800AEBC4_5;   /* (void *)(u32)word in func_800AEBC4 */

typedef struct S_800AEBC4_6 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800AEBC4_6;   /* tail in func_800AEBC4 */



extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

void func_800AEBC4(void *arg0, S_800AEBC4_4 *arg1, S_800AEBC4_1 *arg2, S_800AEBC4_3 *arg3,
                   s32 arg4, s32 arg5) {
    S_800AEBC4_6 *tail = arg0;
    u8 *base0;
    u8 *base1;
    s32 word;
    s32 x;
    register s32 y ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 *stack = __builtin_frame_address(0);

    ASM_KEEP(tail);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    base0 = (u8 *)D_8002E5D8 + 0x1A28;
#else
    base0 = (u8 *)0x80030000;
#endif
    ASM_KEEP(base0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    word = ((S_800AEBC4_0_pre *)base0)[-1].unk_00;
#ifdef NON_MATCHING
    x = arg4;
#else
    x = stack[4];
#endif
    ASM_UNDEF(y);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    y = arg5;
#else
    y = stack[5];
#endif
    ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    base0 -= 0x1A28;
    arg2->unk_00 = word;

    word = ((S_800AEBC4_0 *)base0)->unk_04;
    arg2->unk_04 = word;

    word = ((S_800AEBC4_0 *)base0)->unk_08;
    ASM_UNDEF(base1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
    base1 = (u8 *)D_8002E5E8 + 0x1A18;
#else
    base1 = (u8 *)0x80030000;
#endif
    ASM_KEEP(base1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    arg2->unk_08 = word;

    word = ((S_800AEBC4_0 *)base0)->unk_0C;
    base0 = (u8 *)(u32)((S_800AEBC4_2_pre *)base1)[-1].unk_00;
    base1 -= 0x1A18;
    arg2->unk_0C = word;
    arg3->unk_00 = (s32)(u32)base0;

    word = ((S_800AEBC4_2 *)base1)->unk_04;
    arg3->unk_04 = word;
    word = ((S_800AEBC4_2 *)base1)->unk_08;
    arg3->unk_08 = word;

    arg1->unk_08 = arg3;
    ASM_UNDEF(base1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    base1 = arg3;
    ASM_KEEP(base1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    word = -0x400;
    arg1->unk_04.s = arg2;
    arg1->unk_00 = 0;
    ((S_800AEBC4_2 *)base1)->unk_02 = (s16)word;

    word = arg1->unk_04.u;
    ((S_800AEBC4_5 *)((void *)(u32)word))->unk_08 = (s16)x;
    word = arg1->unk_04.u;
    ((S_800AEBC4_5 *)((void *)(u32)word))->unk_0A = (s16)y;
    word = arg1->unk_04.u;
    base0 = (u8 *)0x400;
    ((S_800AEBC4_5 *)((void *)(u32)word))->unk_0C = (s16)(u32)base0;
    base1 = (u8 *)(u32)arg1->unk_04.u;
    word = 4;
    ((S_800AEBC4_2 *)base1)->unk_0F = (u8)word;

    tail->unk_0C = (s16)x;
    tail->unk_0E = (s16)y;
    tail->unk_10 = (s16)(u32)base0;
    ASM_KEEP(base0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    word = -0x60;
    if (x < 0) {
        word = 0x30;
    }
    word -= x;
    tail->unk_14 = (s16)word;
    word = -0x40 - y;
    tail->unk_16 = (s16)word;
    word = -0x200;
    tail->unk_18 = (s16)word;
}

/* MECHANISM: Frameless leaf with ABI stack words held in t1/t2 and arg0 held in t0.
   Explicit page-base lifetimes put the two template copies in a0/v1, while the
   post-copy hard-register boundary forces the retail a3-to-v1 secondary pointer. */
