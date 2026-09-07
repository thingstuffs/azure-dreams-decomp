#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800962A4();                            /* extern */
s32 func_80096368();                           /* extern */
s32 func_80096440();                           /* extern */
M2C_UNK func_800966C8();                  /* extern */
M2C_UNK func_800966F8();                  /* extern */
extern s32 D_800FE5CC;

void func_80096208(s32 *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;

    if (D_800FE5CC > 0) {
        temp_a1 = func_80096368() << 0x10;
        if (*arg0 >= temp_a1) {
            func_800966C8(arg0, temp_a1);
            return;
        }
    } else {
        if (D_800FE5CC >= 0) {
            temp_a1_2 = func_80096368(arg0) << 0x10;
            if (*arg0 >= temp_a1_2) {
                func_800966C8(arg0, temp_a1_2);
            }
        }
        temp_a1_3 = (func_80096440(arg0) << 0x10) - 1;
        if (temp_a1_3 >= *arg0) {
            func_800966F8(arg0, temp_a1_3);
        }
    }
}
