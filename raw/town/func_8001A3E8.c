#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B7428(s16, s16, s32);               /* extern */
extern M2C_UNK D_800D17D8;

void func_800B7B48(s16 arg0, s16 arg1, s32 arg2) {
    func_800B7428(arg0, arg1, *(((arg2 & 0xFF) * 4) + &D_800D17D8));
}
