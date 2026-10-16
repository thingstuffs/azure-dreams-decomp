#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018BE4(s32);                         /* extern */
M2C_UNK func_80018C58();                            /* extern */
M2C_UNK func_80018E70(void *);                      /* extern */
M2C_UNK func_80018F9C(void *);                      /* extern */

void func_80018FDC(void *arg0, s32 arg1) {
    s32 var_s1;
    void *var_s0;

    var_s0 = arg0;
    var_s1 = 0;
    if (M2C_FIELD(var_s0, u8 *, 1) != 0) {
        do {
            if ((M2C_FIELD(var_s0, u8 *, 3) & 0x20) && (M2C_FIELD(var_s0, u8 *, 1) != 0x18)) {
                if (arg1 == 0) {
                    func_80018E70(var_s0);
                    var_s0 += 4;
                } else {
                    func_80018F9C(var_s0);
                    func_80018BE4(var_s1);
                    goto block_7;
                }
            } else {
block_7:
                var_s0 += 4;
            }
            var_s1 += 1;
        } while (M2C_FIELD(var_s0, u8 *, 1) != 0);
    }
    func_80018C58();
}
