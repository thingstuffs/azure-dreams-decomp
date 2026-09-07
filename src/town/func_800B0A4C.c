#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_800ADFE8();                      /* extern */
M2C_UNK func_800AE0F4();                      /* extern */
M2C_UNK func_800AE2A4();                      /* extern */
s32 func_800B14B0(); /* extern */
s32 func_800B1BEC();        /* extern */
extern M2C_UNK D_800AE090;

typedef struct S_800AE1AC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    s32 unk_2C;
} S_800AE1AC_0;   /* temp_s0 in func_800AE1AC */

typedef struct S_800AE1AC_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800AE1AC_1;   /* var_s1 in func_800AE1AC */

void *func_800AE1AC(M2C_UNK arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    S_800AE1AC_0 *temp_s0;
    void *var_s1;

    var_s1 = func_8003FC64(0);
    if (var_s1 != NULL) {
        temp_s0 = var_s1 + 0x20;
        temp_s0->unk_20 = arg3;
        temp_s0->unk_18 = arg1;
        temp_s0->unk_1C = arg2;
        temp_s0->unk_14 = 6;
        func_800ADFE8(temp_s0);
        ((S_800AE1AC_1 *)var_s1)->unk_10 = &D_800AE090;
        temp_s0->unk_28 = func_800B14B0(var_s1, temp_s0->unk_04, temp_s0->unk_08, temp_s0->unk_0C, temp_s0->unk_10, temp_s0->unk_20, arg1);
        temp_v0 = func_800B1BEC(var_s1, 0x48, -0xC);
        temp_s0->unk_2C = temp_v0;
        if ((temp_s0->unk_28 == 0) || (temp_v0 == 0)) {
            func_800AE2A4(temp_s0);
            var_s1 = NULL;
        }
        func_800AE0F4(temp_s0);
    }
    return var_s1;
}
