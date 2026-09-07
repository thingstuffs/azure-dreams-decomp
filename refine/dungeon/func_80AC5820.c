#include "common.h"

typedef long long s64;

typedef struct S_80AC5820_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC5820_0;   /* arg1 in func_80AC5820 */

typedef struct S_80AC5820_1_pre {
    u16 unk_00;
} S_80AC5820_1_pre;   /* the 0x2 bytes before arg0 in func_80AC5820, addressed as arg0[-1] */

typedef struct S_80AC5820_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80AC5820_1;   /* arg0 in func_80AC5820 */

typedef struct S_80AC5820_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC5820_2;   /* other in func_80AC5820 */

typedef struct S_80AC5820_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80AC5820_3;   /* arg2 in func_80AC5820 */



extern void func_800478B8();
extern s32 func_80065420(void *, void *, void *, void *);

extern s32 D_800814A0 __attribute__((section(".data")));
extern s16 D_80083228 __attribute__((section(".data")));
extern s8 D_800DCECC[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

/* Updates the relative position value with an angle bias and flags countdown completion. */
void func_80AC5820(void *state, S_80AC5820_0 *position, S_80AC5820_3 *result)
{
    StackWork work;
    s16 ticks_left;
    s32 position_value;
    s32 reference_value;
    s8 *angle_bias;
    u32 angle_page;
    S_80AC5820_2 *reference_pos;

    work.xyz[0] = position->unk_02;
    work.xyz[1] = position->unk_06;
    work.xyz[2] = position->unk_0A;
    position_value = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

    reference_pos = ((S_80AC5820_1 *)state)->unk_A8;
    work.xyz[0] = reference_pos->unk_02;
    work.xyz[1] = reference_pos->unk_06;
    work.xyz[2] = reference_pos->unk_0A;
    reference_value = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);
    angle_page = 0x80080000;
    ASM_KEEP(angle_page);   /* MATCH pin: load-bearing for the whole function shape */
    angle_bias = &D_800DCECC[
        ((*(s16 *)(angle_page + 0x3228) +
          ((S_80AC5820_1 *)state)->unk_94 + 0x100) >> 9) & 7];
    result->unk_06 = position_value - reference_value - *angle_bias * 2;

    func_800478B8(result, angle_bias);
    ticks_left = ((S_80AC5820_1 *)state)->unk_96 - 1;
    ((S_80AC5820_1 *)state)->unk_96 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        register u32 flags_page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

        flags_page = 0x80080000;
        ASM_KEEP(flags_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_80AC5820_1_pre *)state)[-1].unk_00 |= 0x8000;
        *(s32 *)(flags_page + 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: StackWork fixes the 0x40 frame and the s2/s1/s0 stack-output roles.
   A retained 0x80080000 page base yields the displaced angle/global accesses.
   The table pointer stays in a1; only the tail page live range is pinned to v1. */
