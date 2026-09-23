#include "common.h"
int abs(int);

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
    s32 updated_value;
    s32 countdown;

    position->unk_00.at00.v += ((S_818D4A94_1 *)motion)->unk_3C;
    position->unk_04 += ((S_818D4A94_1 *)motion)->unk_40;
    position->unk_08 += ((S_818D4A94_1 *)motion)->unk_44;
    ((S_818D4A94_1 *)motion)->unk_3C += ((S_818D4A94_1 *)motion)->unk_48;
    ((S_818D4A94_1 *)motion)->unk_40 += ((S_818D4A94_1 *)motion)->unk_4C;
    ((S_818D4A94_1 *)motion)->unk_44 += ((S_818D4A94_1 *)motion)->unk_50;
    updated_value = abs(((S_818D4A94_1 *)motion)->unk_34 - position->unk_00.at02.v);
    updated_value = updated_value < 0x10;
    D_80025118[0] = 1;
    if (updated_value) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    countdown = ((S_818D4A94_1 *)motion)->unk_32;
    countdown -= 8;
    ((S_818D4A94_1 *)motion)->unk_32 = countdown;
    countdown <<= 16;
    if (countdown <= 0) {
        ((S_818D4A94_1_pre *)motion)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
