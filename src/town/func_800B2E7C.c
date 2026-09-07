#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK bzero();             /* extern */
s32 func_800AE500();                     /* extern */
s32 func_800AEFD8(); /* extern */
M2C_UNK func_800B06C4();                      /* extern */
extern M2C_UNK D_800B0490;

typedef struct S_800B05DC_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
} S_800B05DC_0;   /* temp_s0 in func_800B05DC */

typedef struct S_800B05DC_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B05DC_1;   /* var_s1 in func_800B05DC */

void *func_800B05DC(s32 arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_v0;
    s32 temp_v0_2;
    S_800B05DC_0 *temp_s0;
    void *var_s1;

    var_s1 = func_8003FC64(0);
    if (var_s1 != NULL) {
        temp_s0 = var_s1 + 0x20;
        temp_s0->unk_08 = arg0;
        temp_s0->unk_0C = arg4;
        temp_s0->unk_14 = arg1;
        bzero(temp_s0, 4);
        temp_v0 = func_800AE500(temp_s0, arg4);
        temp_s0->unk_18 = temp_v0;
        if (temp_v0 != 0) {
            ((S_800B05DC_1 *)var_s1)->unk_10 = &D_800B0490;
            temp_v0_2 = func_800AEFD8(var_s1, arg2, arg3, arg1, temp_s0->unk_18, temp_s0);
            temp_s0->unk_04 = temp_v0_2;
            if (temp_v0_2 == 0) {
                func_800B06C4(temp_s0);
                var_s1 = NULL;
            }
        }
    }
    return var_s1;
}
