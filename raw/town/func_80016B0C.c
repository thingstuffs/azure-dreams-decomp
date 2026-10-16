#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D16D8;
extern M2C_UNK D_800D172C;

void func_800B426C(s32 arg0) {
    M2C_UNK *var_a2;
    s32 var_a3;

    var_a2 = &D_800D172C;
    var_a3 = arg0;
    if ((arg0 | (s32) &D_800D172C) & 3) {
        do {
            M2C_FIELD(var_a3, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 0));
            M2C_FIELD(var_a3, M2C_UNK *, 4) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 4));
            M2C_FIELD(var_a3, M2C_UNK *, 8) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 8));
            M2C_FIELD(var_a3, M2C_UNK *, 0xC) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 0xC));
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != (&D_800D172C + 0x30));
    } else {
        do {
            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
            M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
            M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
            M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != (&D_800D172C + 0x30));
    }
    M2C_FIELD(arg0, M2C_UNK *, 0x30) = M2C_UNALIGNED32(M2C_FIELD(&D_800D16D8, M2C_UNK *, 0));
    M2C_FIELD(arg0, M2C_UNK *, 0x34) = M2C_UNALIGNED32(M2C_FIELD(&D_800D16D8, M2C_UNK *, 4));
    M2C_FIELD(arg0, M2C_UNK *, 0x38) = M2C_UNALIGNED32(M2C_FIELD(&D_800D16D8, M2C_UNK *, 8));
}
