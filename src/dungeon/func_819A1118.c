#include "common.h"
#include "m2c_compat.h"

typedef struct S_819A1118_0_pre {
    u16 unk_00;
} S_819A1118_0_pre;   /* the 0x2 bytes before arg0 in func_819A1118, addressed as arg0[-1] */

typedef struct S_819A1118_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u8 pad_40[0x14];
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    s16 unk_76;
} S_819A1118_0;   /* arg0 in func_819A1118 */

typedef struct S_819A1118_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_819A1118_1;   /* var_a0 in func_819A1118 */


extern s16 D_800261B0[];
extern s32 D_800814A0;

void func_819A1118(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    u16 temp_v0;
    void *var_a0;

    temp_v0 = ((S_819A1118_0 *)arg0)->unk_3A - 1;
    D_800261B0[0] = 1;
    temp_a0 = ((S_819A1118_0 *)arg0)->unk_3E;
    ((S_819A1118_0 *)arg0)->unk_3A = temp_v0;
    temp_v1 = ((S_819A1118_0 *)arg0)->unk_3C - (s16) temp_v0;
    if (temp_a0 >= temp_v1) {
        ((S_819A1118_0 *)arg0)->unk_54 = (s16) (((S_819A1118_0 *)arg0)->unk_60 + ((s32) (((S_819A1118_0 *)arg0)->unk_6C * temp_v1) / temp_a0));
        ((S_819A1118_0 *)arg0)->unk_56 = (s16) (((S_819A1118_0 *)arg0)->unk_62 + ((s32) (((S_819A1118_0 *)arg0)->unk_6E * (((S_819A1118_0 *)arg0)->unk_3C - (s16) ((S_819A1118_0 *)arg0)->unk_3A)) / (s16) ((S_819A1118_0 *)arg0)->unk_3E));
        ((S_819A1118_0 *)arg0)->unk_58 = (s16) (((S_819A1118_0 *)arg0)->unk_64 + ((s32) (((S_819A1118_0 *)arg0)->unk_70 * (((S_819A1118_0 *)arg0)->unk_3C - (s16) ((S_819A1118_0 *)arg0)->unk_3A)) / (s16) ((S_819A1118_0 *)arg0)->unk_3E));
        ((S_819A1118_0 *)arg0)->unk_5A = (s16) (((S_819A1118_0 *)arg0)->unk_66 + ((s32) (((S_819A1118_0 *)arg0)->unk_72 * (((S_819A1118_0 *)arg0)->unk_3C - (s16) ((S_819A1118_0 *)arg0)->unk_3A)) / (s16) ((S_819A1118_0 *)arg0)->unk_3E));
        ((S_819A1118_0 *)arg0)->unk_5C = (s16) (((S_819A1118_0 *)arg0)->unk_68 + ((s32) (((S_819A1118_0 *)arg0)->unk_74 * (((S_819A1118_0 *)arg0)->unk_3C - (s16) ((S_819A1118_0 *)arg0)->unk_3A)) / (s16) ((S_819A1118_0 *)arg0)->unk_3E));
        ((S_819A1118_0 *)arg0)->unk_5E = (s16) (((S_819A1118_0 *)arg0)->unk_6A + ((s32) (((S_819A1118_0 *)arg0)->unk_76 * (((S_819A1118_0 *)arg0)->unk_3C - (s16) ((S_819A1118_0 *)arg0)->unk_3A)) / (s16) ((S_819A1118_0 *)arg0)->unk_3E));
    }
    var_a1 = 0;
    var_a0 = arg0;
    do {
        ((S_819A1118_1 *)var_a0)->unk_0C = (s8) ((s32) (((S_819A1118_1 *)var_a0)->unk_1C * (s16) ((S_819A1118_0 *)arg0)->unk_3A) / (s16) ((S_819A1118_0 *)arg0)->unk_3C);
        ((S_819A1118_1 *)var_a0)->unk_0D = (s8) ((s32) (((S_819A1118_1 *)var_a0)->unk_1D * (s16) ((S_819A1118_0 *)arg0)->unk_3A) / (s16) ((S_819A1118_0 *)arg0)->unk_3C);
        var_a1 += 1;
        ((S_819A1118_1 *)var_a0)->unk_0E = (s8) ((s32) (((S_819A1118_1 *)var_a0)->unk_1E * (s16) ((S_819A1118_0 *)arg0)->unk_3A) / (s16) ((S_819A1118_0 *)arg0)->unk_3C);
        var_a0 += 4;
    } while (var_a1 < 4);
    if ((s16) ((S_819A1118_0 *)arg0)->unk_3A <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_819A1118_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
