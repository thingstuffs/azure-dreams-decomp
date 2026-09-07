#include "common.h"

typedef struct S_818D4A94_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_818D4A94_0;   /* arg1 in func_818D4A94 */

typedef struct S_818D4A94_1_pre {
    u16 unk_00;
} S_818D4A94_1_pre;   /* the 0x2 bytes before arg0 in func_818D4A94, addressed as arg0[-1] */

typedef struct S_818D4A94_1 {
    u8 pad_00[0x32];
    u16 unk_32;
    s16 unk_34;
    u8 pad_36[0x6];
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4A94_1;   /* arg0 in func_818D4A94 */



extern s16 D_80025118[5];
extern s32 D_800814A0[3];

/* Advance position and velocity, and flag completion near the target or when the countdown expires. */
void func_818D4A94(void *motion, S_818D4A94_0 *position)
{
    register s32 updated_value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across axis_value call/branch */
    register s32 axis_value ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 accel_z ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    s32 active_flag;
    s32 axis_step;

    updated_value = position->unk_00.at00.v;
    updated_value += ((S_818D4A94_1 *)motion)->unk_3C;
    position->unk_00.at00.v = updated_value;
    updated_value = position->unk_04;
    updated_value += ((S_818D4A94_1 *)motion)->unk_40;
    position->unk_04 = updated_value;
    updated_value = position->unk_08;
    updated_value += ((S_818D4A94_1 *)motion)->unk_44;
    position->unk_08 = updated_value;

    updated_value = ((S_818D4A94_1 *)motion)->unk_3C;
    axis_step = ((S_818D4A94_1 *)motion)->unk_48;
    axis_value = ((S_818D4A94_1 *)motion)->unk_4C;
    accel_z = ((S_818D4A94_1 *)motion)->unk_50;
    updated_value += axis_step;
    ((S_818D4A94_1 *)motion)->unk_3C = updated_value;
    updated_value = ((S_818D4A94_1 *)motion)->unk_40;
    axis_step = ((S_818D4A94_1 *)motion)->unk_44;
    updated_value += axis_value;
    axis_step += accel_z;
    ((S_818D4A94_1 *)motion)->unk_40 = updated_value;
    updated_value = ((S_818D4A94_1 *)motion)->unk_34;
    ASM_USE(updated_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_MEM_NV(axis_value, D_80025118[0]);   /* MATCH pin: keeps a statement from moving across axis_value call/branch */
    ASM_USE2_NV(axis_value, updated_value);   /* MATCH pin: keeps a statement from moving across axis_value call/branch */
    ((S_818D4A94_1 *)motion)->unk_44 = axis_step;
    axis_value = position->unk_00.at02.v;
    ASM_USE(axis_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    active_flag = 1;
    ASM_USE2_NV(axis_value, active_flag);   /* MATCH pin: retail schedule: same instructions, different order without it */
    updated_value -= axis_value;
    if (updated_value < 0) {
        updated_value = -updated_value;
    }
    updated_value = updated_value < 0x10;
    D_80025118[0] = active_flag;
    if (updated_value) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    updated_value = ((S_818D4A94_1 *)motion)->unk_32;
    updated_value -= 8;
    ((S_818D4A94_1 *)motion)->unk_32 = updated_value;
    updated_value <<= 16;
    if (updated_value <= 0) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
