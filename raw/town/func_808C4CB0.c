#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000C8C();                            /* extern */
extern M2C_UNK D_00000730;
extern M2C_UNK D_00000758;
extern M2C_UNK D_00000E0C;

void func_80000CB0(void) {
    M2C_UNK *temp_a0;
    u8 *var_a0;

    if (*(s32 *)0xE48 != 0) {
        M2C_FIELD(*(void **)0xE68, M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x64)(&D_00000730, &D_00000758, 0x4B);
        M2C_FIELD(*(void *)0xE68, M2C_UNK (**)(M2C_UNK), 0x70)(1);
    }
    *(void *)0xE48 = 1;
    func_80000C8C();
    M2C_FIELD(*(void **)0xE5C, M2C_UNK **, 0x10) = &D_00000E0C;
    temp_a0 = M2C_FIELD(*(void *)0xE5C, M2C_UNK **, 0x10);
    if (M2C_FIELD(temp_a0, u8 *, 1) != 0x80) {
        var_a0 = temp_a0 + 1;
        do {
            M2C_FIELD(var_a0, s32 *, 0xB) = (s32) *((M2C_FIELD(var_a0, s32 *, 0xB) * 4) + *(s32 *)0xE64);
            var_a0 += 0x14;
        } while (*var_a0 != 0x80);
    }
}
