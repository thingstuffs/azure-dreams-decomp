#include "common.h"

typedef struct S_80099A1C_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0xB2];
    u16 unk_B8;
    u8 pad_BA[0x6];
    s32 unk_C0;
} S_80099A1C_0;   /* scratch in func_80099A1C */

typedef struct S_80099A1C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80099A1C_1;   /* arg1 in func_80099A1C */

typedef struct S_80099A1C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80099A1C_2;   /* arg2 in func_80099A1C */

typedef struct S_80099A1C_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80099A1C_3_pre;   /* the 0x8 bytes before arg0 in func_80099A1C, addressed as arg0[-1] */

typedef struct S_80099A1C_3 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    s16 unk_0C;
} S_80099A1C_3;   /* arg0 in func_80099A1C */

typedef struct S_80099A1C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80099A1C_4;   /* next in func_80099A1C */



extern s32 func_800644B8(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800C96E8(void *, void *);

s32 func_80099A1C(void *arg0, S_80099A1C_1 *arg1, S_80099A1C_2 *arg2)
{
    u8 *scratch;
    void *next;
    s32 value;

    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

loop:
    ((S_80099A1C_0 *)scratch)->unk_00 = arg1->unk_02;
    ((S_80099A1C_0 *)scratch)->unk_02 = arg1->unk_06;
    ((S_80099A1C_0 *)scratch)->unk_04 = arg1->unk_0A;

    value = func_80065420(
        scratch,
        scratch + 0xB8,
        scratch + 0x90,
        scratch + 0x94);
    ((S_80099A1C_0 *)scratch)->unk_C0 = value - arg2->unk_06;

    {
        s32 delta;
        u16 accum;

        delta = ((S_80099A1C_3 *)arg0)->unk_00;
        accum = ((S_80099A1C_0 *)scratch)->unk_B8;
        delta = (delta << 16) >> 17;
        ASM_KEEP(delta);   /* MATCH pin: retail register colouring depends on it */
        accum -= delta;
        ((S_80099A1C_0 *)scratch)->unk_B8 = accum;
    }
    ((S_80099A1C_0 *)scratch)->unk_B8 +=
        (func_800644B8(
            (((S_80099A1C_3 *)arg0)->unk_0C << 8) +
            (((S_80099A1C_3 *)arg0)->unk_08 << 7)) *
         (((S_80099A1C_3 *)arg0)->unk_08 >> 2)) >> 9;

    func_800C96E8(arg0, scratch);

    next = ((S_80099A1C_3_pre *)arg0)[-1].unk_00;
    arg0 = (u8 *)next + 0x20;
    if (next != 0) {
        arg1 = ((S_80099A1C_4 *)next)->unk_08;
        arg2 = ((S_80099A1C_4 *)next)->unk_0C;
        goto loop;
    }
    return 0;
}

/* MECHANISM: Recover the true-space back-edge as a local loop, keeping the current
   object/state in s1/s2 and the 0x1F800000 scratch base in pinned s0.
   Use the real four-argument scratch offsets and a word store at +0xC0; a scoped
   v0 delta pin closes the final v0/v1 allocation swap in the halfword update. */
