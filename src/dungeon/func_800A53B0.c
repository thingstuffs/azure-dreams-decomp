#include "common.h"
#include "m2c_compat.h"

s32 func_80042900(void *, s32);
s32 func_800A1C58(void *);
void func_800A1D4C(void *, s32);
void func_800A56E0(s32);
s32 func_800AAC8C(void);
void func_800C77D0(void *, s32, s32, s32);
extern u16 D_80013714;
extern s32 D_8007359C;
extern s8 D_80080A88;
extern s8 D_80080AA0;
extern M2C_UNK D_80083460;
extern s32 D_800E296C;


typedef struct S_800AAB10_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s32 unk_0C;
} S_800AAB10_0;   /* state in func_800AAB10 */

typedef struct S_800AAB10_1 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x1];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x34];
    s32 unk_54;
} S_800AAB10_1;   /* arg3 in func_800AAB10 */

typedef struct S_800AAB10_2_pre {
    u16 unk_00;
    u8 pad_02[0x12];
} S_800AAB10_2_pre;   /* the 0x14 bytes before ((temp_a0 * 0x14) + D_8007359C) in func_800AAB10, addressed as ((temp_a0 * 0x14) + D_8007359C)[-1] */

typedef struct S_800AAB10_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800AAB10_3;   /* &D_80083460 in func_800AAB10 */

s32 func_800AAB10(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, S_800AAB10_1 *arg3) {
    s32 var_s1;
    u8 temp_a0;
    u8 *state;

    var_s1 = 0;
    if (D_800E296C & 0x100000) {
        state = (u8 *)&D_80083460;
        if (((S_800AAB10_0 *)state)->unk_0C != 0) {
            if (((S_800AAB10_0 *)state)->unk_0C == arg3) {
                if (((S_800AAB10_0 *)state)->unk_0A == 0) {
                    if (!(((S_800AAB10_0 *)state)->unk_02 & 8)) {
                        func_800C77D0((void *)(arg0 - 0x20), arg1, 8, 0x300);
                        func_800A1D4C(arg3, 1);
                        func_800A56E0(0x201);
                        if (!(D_80013714 & 2)) {
                            D_80080AA0 = 1;
                            D_80080A88 = 0;
                        }
                        if (!(arg3->unk_54 & 0x800000) && (arg3->unk_14 & 0x4000)) {
                            temp_a0 = arg3->unk_13;
                            if ((((S_800AAB10_2_pre *)(((temp_a0 * 0x14) + D_8007359C)))[-1].unk_00 & 0x80) && (temp_a0 >= 2U) && ((u8) arg3->unk_11 >= 0x14U) && !(arg3->unk_1C & 0x228) && ((func_80042900(arg3, 0x18) << 0x10) == 0)) {
                                var_s1 = 1;
                            }
                        }
                        if ((func_800A1C58(arg3) << 0x10) == 0) {
                            goto clear_state;
                        }
                        goto tail_call;
                    }
                }
            }
            return 0;
        }
        goto tail_call;
    }
    goto return_result;
tail_call:
    func_800AAC8C();
    return 0;
clear_state:
    ((S_800AAB10_3 *)(&D_80083460))->unk_0C = 0;
return_result:
    return var_s1;
}

/* MECHANISM: cdk-G0 holds D_80083460 in $v1 with the retail 0x20 frame and s0/s1 saves.
   The four-argument copy call preserves arg1 while setting a2/a3 in the retail slots.
   Lexical tail/store/return labels select SHAPE-C and make the outer false edge skip the store. */
