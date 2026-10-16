#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8001F6F8;
extern M2C_UNK D_80073414;

void func_8001E994(void) {
    s16 *var_t3;
    s16 var_t0;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_t1;
    u16 temp_v1;
    void *var_a3;

    var_t0 = 0;
    var_t1 = 1;
    var_t3 = &D_8001F6F8 + 2;
    var_a3 = &D_80073414 + 0x14;
    do {
        var_a2 = 1;
        if ((s32) M2C_FIELD(var_a3, u8 *, 2) > 1) {
            var_a1 = 0x14;
            do {
                temp_v1 = *(var_a1 + M2C_FIELD(var_a3, s32 *, 0xC));
                if (!(temp_v1 & 0x10) && (!(temp_v1 & 0x40) || (*(s32 *)0x80012090 == 2))) {
                    temp_v1_2 = ((s32) (*(var_a1 + M2C_FIELD(var_a3, s32 *, 0xC)) & 0x3000) / 4096) & 3;
                    var_a0 = 0x80;
                    if (temp_v1_2 != 0) {
                        var_a0 = 0x55;
                        if (temp_v1_2 != 1) {
                            var_a0 = 1;
                            if (temp_v1_2 == 2) {
                                var_a0 = 0x20;
                            }
                        }
                    }
                    var_t0 += var_a0;
                }
                var_a2 += 1;
                var_a1 += 0x14;
            } while (var_a2 < (s32) M2C_FIELD(var_a3, u8 *, 2));
        }
        *var_t3 = var_t0;
        var_t3 += 2;
        var_t1 += 1;
        var_a3 += 0x14;
    } while (var_t1 < 0x13);
    *((var_t1 * 2) + &D_8001F6F8) = var_t0;
}
