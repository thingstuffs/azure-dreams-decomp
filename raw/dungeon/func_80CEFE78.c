#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_8016FE9C;
extern M2C_UNK D_8016FEA4;
extern M2C_UNK D_8016FEAC;

void func_8016D678(void *arg0, void *arg2, void *arg3) {
    M2C_UNK *var_a1;
    u8 temp_v1;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0x10;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    temp_v1 = M2C_FIELD(arg3, u8 *, 0x48);
    switch (temp_v1) {                              /* irregular */
    case 13:
        var_a1 = &D_8016FE9C;
block_9:
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != var_a1) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
        }
        return;
    case 14:
        var_a1 = &D_8016FEA4;
        goto block_9;
    case 15:
        var_a1 = &D_8016FEAC;
        goto block_9;
    }
}
