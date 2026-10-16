#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800AC82C(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AD9B4(void *, void *);                  /* extern */
extern M2C_UNK D_8015F4D4;
extern M2C_UNK D_801620E0;
extern M2C_UNK D_801620E8;
extern M2C_UNK D_80162158;

void func_80161E00(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK *temp_v1;
    M2C_UNK *var_a1;

    temp_v1 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    var_a1 = &D_801620E0;
    if (temp_v1 == &D_801620E0) {
        if (M2C_FIELD(arg2, u16 *, 4) == 0x103) {
            var_a1 = &D_801620E8;
            goto block_5;
        }
    } else if ((temp_v1 == &D_801620E8) && (M2C_FIELD(arg2, u16 *, 4) == 0x103)) {
block_5:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
    }
    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015F4D4;
        }
    } else if ((M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80162158) && !(M2C_FIELD(arg3, s32 *, 0x1C) & 0x208)) {
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801620E0;
        func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801620E0), 0);
    }
}
