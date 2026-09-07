#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800D1A80_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D1A80_0;   /* arg0 in func_800D1A80 */

typedef struct S_800D1A80_1 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D1A80_1;   /* arg2 in func_800D1A80 */

typedef struct S_800D1A80_2_pre {
    u16 unk_00;
} S_800D1A80_2_pre;   /* the 0x2 bytes before arg3 in func_800D1A80, addressed as arg3[-1] */


typedef struct S_800D1A80_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D1A80_3;   /* var_a0 in func_800D1A80 */


#define M2C_BREAK() 0
#define M2C_SYNC() 0

extern s16 D_8008346A[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
void func_8009A028(void *arg0);
void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
void func_800A32A4(void *arg0);
void func_800A56E0(s32 arg0);
s32 func_80042900(void *arg0, s32 arg1);

s32 func_800D1A80(S_800D1A80_0 *arg0, void *arg1, S_800D1A80_1 *arg2, void *arg3) {
    s16 *flag = D_8008346A;
    s16 temp_a1;
    M2C_UNK var_a2;
    s16 temp_v0_2;
    s32 temp_v1_4;
    s32 *var_a0;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_a0_2;
    u8 temp_a1_2;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return 0;
        }
        goto block_6;
    }
    if (*flag == 0) {
        arg2->unk_10 = 0x20;
        arg2->unk_12 = (u16) (arg2->unk_12 - 0x80);
        arg2->unk_14 = (u16) (arg2->unk_14 | 0xC);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 | 0x10000000);
        func_800A56E0(0x805);
        arg2->unk_0C.at00.v = 0x808080;
        arg0->unk_96 = 0x10;
        arg0->unk_9B = (u8) (arg0->unk_9B + 1);
block_6:
        temp_v1_2 = arg2->unk_0C.at00u.v;
        temp_a1 = arg0->unk_96;
        arg2->unk_0C.at00u.v = (u8) (temp_v1_2 + ((s32) (0x20 - temp_v1_2) / temp_a1));
        temp_v1_3 = arg2->unk_0C.at01.v;
        temp_v0 = arg2->unk_0C.at02.v;
        temp_a1 = arg0->unk_96;
        arg2->unk_0C.at01.v = (u8) (temp_v1_3 + ((s32) (0x20 - temp_v1_3) / temp_a1));
        arg2->unk_0C.at02.v = (u8) (temp_v0 + ((s32) (0x20 - temp_v0) / (s16) arg0->unk_96));
        temp_v0_2 = (u16) arg0->unk_96 - 1;
        arg0->unk_96 = temp_v0_2;
        if (((temp_v0_2 << 0x10) > 0) && ((arg2->unk_14 & 0x8000) == 0)) {
            return 0;
        }
        var_a0 = D_80083460;
        {
            temp_v1_4 = ((S_800D1A80_3 *)var_a0)->unk_10;
            if (temp_v1_4 == (arg3 - 0x20)) {
                ((S_800D1A80_3 *)var_a0)->unk_10 = (s32) (temp_v1_4 & 0x7FFFFFFF);
            }
            func_800A32A4(arg3);
            if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                temp_a0_2 = arg2->unk_24;
                temp_a1_2 = arg2->unk_25;
                var_a2 = 0x3000;
                if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_a1_2, var_a2);
            }
            func_8009A028(arg3);
            ((S_800D1A80_2_pre *)arg3)[-1].unk_00 = (u16) (((S_800D1A80_2_pre *)arg3)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            return 1;
        }
        return 0;
    }
    return 0;
}
