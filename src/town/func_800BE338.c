#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BBA98_0 {
    u16 unk_00;
    u8 pad_02[0x48];
    s16 unk_4A;
    u8 pad_4C[0x2];
    union { s16 s; u16 u; } unk_4E;   /* accessed as both */
} S_800BBA98_0;   /* temp_a3 in func_800BBA98; pointer addresses record offset 0x2 */


typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    u16 f14;
} State;

typedef struct {
    u8 pad0[0xC];
    s32 fc;
    s16 f10;
    s16 f12;
    u16 f14;
} Arg2State;

void func_800478B8();
s32 rand(void);
void func_800BBBE0(void *);
extern s32 D_800814A0[3];

void func_800BBA98(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_a0;
    void *temp_a3;
    State *temp_s0;
    s32 var_a0;
    void *var_a1;
    register void *call_arg ASM_REG("$4") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *held_arg2 ASM_REG("$17") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    temp_a3 = arg0;
    temp_s0 = (State *)arg1;
    temp_v1 = ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4E.s;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return func_800BBBE0(call_arg);
        }
        goto type1;
    }
zero_state:
    temp_s0->f0 += (temp_s0->fc / (s16) ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4A);
    temp_s0->f4 += (temp_s0->f10 / (s16) ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4A);
    temp_v0_2 = (u16) ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4A - 1;
    ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4A = temp_v0_2;
    temp_v1 = 0x60;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((Arg2State *)held_arg2)->f10 = temp_v1;
        ((Arg2State *)held_arg2)->f14 |= 0xC;
        ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_4E.u += 1;
        return func_800BBBE0(call_arg);
    }
    goto zero_shared;
type1:
        temp_s0->f0 += temp_s0->fc;
        temp_s0->f4 += temp_s0->f10;
        temp_v1_2 = temp_s0->fc;
        var_a0 = temp_v1_2 >> 1;
        temp_s0->fc = temp_v1_2 - var_a0;
        temp_s0->f10 -= (temp_s0->f10 >> 1);
        var_a1 = (void *)0xFFEFEFF0;
        ((Arg2State *)held_arg2)->fc += (s32)var_a1;
        if ((u8) ((Arg2State *)held_arg2)->fc < 0x11U) {
            ((S_800BBA98_0 *)((u8 *)temp_a3 - 0x2))->unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        temp_v0 = (rand() & 7) << 0xF;
        temp_v1_3 = temp_s0->f8;
        temp_v1_3 -= temp_v0;
        temp_s0->f8 = temp_v1_3;
        func_800478B8(held_arg2);
        return;
zero_shared:
    temp_v0 = (rand() & 7) << 0xF;
    temp_v1_3 = temp_s0->f8;
    temp_v1_3 -= temp_v0;
    temp_s0->f8 = temp_v1_3;
    func_800478B8(held_arg2);
}
