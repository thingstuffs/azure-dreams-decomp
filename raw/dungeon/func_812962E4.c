#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098DDC(s32);                         /* extern */
M2C_UNK func_8015AA48();                            /* extern */
extern s32 D_8015B710;

void func_8015AAE4(void) {
    s16 var_s0;
    s16 var_v0_2;
    s32 temp_a0;
    s32 var_v0;
    void *temp_v1;

    var_s0 = 0;
    temp_v1 = D_8015B710 + 0x20;
    M2C_FIELD(temp_v1, u16 *, 0x46) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x46) & 0x7FFF);
    func_8015AA48();
    var_v0 = 0 << 0x10;
    do {
        temp_a0 = M2C_FIELD(((var_v0 >> 0xE) + *(s32 *)0x800E397C), s32 *, 0xAC);
        var_v0_2 = var_s0 + 1;
        if (temp_a0 != 0) {
            func_80098DDC(temp_a0 - 0x20);
            var_v0_2 = var_s0 + 1;
        }
        var_s0 = var_v0_2;
        var_v0 = var_s0 << 0x10;
    } while (var_v0_2 < 2);
}
