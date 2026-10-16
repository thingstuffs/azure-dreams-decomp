#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1A0(M2C_UNK *, M2C_UNK *);        /* extern */
extern M2C_UNK D_8001791C;
extern M2C_UNK D_80017AAC;
extern M2C_UNK D_80017AB8;
extern M2C_UNK D_80017C14;

M2C_UNK *func_8001A6D0(s32 arg0) {
    M2C_FIELD(&D_80017C14, s32 *, 0x20) = (s32) *((arg0 * 0xC) + &D_8001791C);
    func_8001A1A0(&D_80017C14, &D_80017AAC);
    func_8001A1A0(&D_80017C14 + 0x14, &D_80017AB8);
    return &D_80017C14;
}
