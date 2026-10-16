#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018FC8(M2C_UNK *, M2C_UNK *, s32, M2C_UNK); /* extern */
extern M2C_UNK D_8001632C;
extern M2C_UNK D_800170FC;

void func_800172B8(s32 arg0, M2C_UNK arg2) {
    M2C_UNK sp10;
    M2C_UNK *var_a2;
    M2C_UNK *var_t0;

    var_t0 = &sp10;
    var_a2 = &D_800170FC;
    do {
        M2C_FIELD(var_t0, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_t0, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_t0, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_t0, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_t0 += 0x10;
    } while (var_a2 != (&D_800170FC + 0x20));
    M2C_FIELD(var_t0, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
    M2C_FIELD(var_t0, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
    func_80018FC8(&sp10, &D_8001632C, arg0, arg2);
}
