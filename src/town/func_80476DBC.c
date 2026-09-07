#include "common.h"

typedef struct S_80017DBC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} S_80017DBC_0;   /* var_s0 in func_80017DBC */

typedef struct S_80017DBC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80017DBC_1;   /* var_s2 in func_80017DBC */

typedef struct S_80017DBC_2 {
    u8 pad_00[0xA2];
    s16 unk_A2;
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80017DBC_2;   /* var_s4 in func_80017DBC */



extern s32 func_800198D0();
extern s32 D_80016470;
extern s32 D_80016608;
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017DBC(void)
{
    s32 var_s1;
    s32 var_s3;
    void *var_s0;
    void *var_s2;
    void *var_s4;
    s32 offset;

    if (D_80019BB0 == 2) {
        do { var_s1 = 1; } while (0);
        var_s3 = 0x400;
        var_s4 = &D_80016608;
        var_s2 = var_s4 + 0x14;
        do {
            offset = 0xC;
            var_s0 = (u8 *)&D_80016470 + offset;
        } while (0);
loop_2:
        if (func_800198D0(((S_80017DBC_0 *)var_s0)->unk_04) != 0) {
            if (((S_80017DBC_0 *)var_s0)->unk_08 != 0) {
                ((S_80017DBC_1 *)var_s2)->unk_02 = var_s3;
                if (var_s1 == 1) {
                    ((S_80017DBC_2 *)var_s4)->unk_A2 = var_s3;
                    goto block_11;
                }
                ((S_80017DBC_2 *)var_s4)->unk_B6 = var_s3;
                goto block_11;
            }
            if (D_80019BB4 == var_s1) {
                ((S_80017DBC_1 *)var_s2)->unk_02 = var_s3;
            }
        }
block_11:
        var_s2 += 0x14;
        var_s1 += 1;
        var_s0 += 0xC;
        if (var_s1 >= 8) {
            return 0;
        }
        goto loop_2;
    }
    return 1;
}
