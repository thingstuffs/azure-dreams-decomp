#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4(s32, M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
extern M2C_UNK D_8008926C;

void func_800B3598(s32 arg0) {
    M2C_UNK sp10;
    M2C_UNK *var_a2;
    M2C_UNK *var_a3;

    var_a2 = &D_8008926C;
    var_a3 = &sp10;
    if ((s32) &D_8008926C & 3) {
        do {
            M2C_FIELD(var_a3, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 0));
            M2C_FIELD(var_a3, M2C_UNK *, 4) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 4));
            M2C_FIELD(var_a3, M2C_UNK *, 8) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 8));
            M2C_FIELD(var_a3, M2C_UNK *, 0xC) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 0xC));
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != (&D_8008926C + 0x20));
    } else {
        do {
            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
            M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
            M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
            M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != (&D_8008926C + 0x20));
    }
    M2C_FIELD(var_a3, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 0));
    M2C_FIELD(var_a3, M2C_UNK *, 4) = M2C_UNALIGNED32(M2C_FIELD(var_a2, M2C_UNK *, 4));
    M2C_FIELD(var_a3, s8 *, 8) = (s8) M2C_FIELD(var_a2, s8 *, 8);
    func_800491F4(arg0, &sp10, 0x28, var_a3);
}
