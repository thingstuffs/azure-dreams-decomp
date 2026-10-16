#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1DC(s32);                         /* extern */

void func_80019144(s32 arg0, s32 arg1) {
    func_8001A1DC(M2C_FIELD(((arg1 * 0x14) + M2C_FIELD(((arg0 * 0x14) + M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x24), s32 *, 0x6C)), s32 *, 0xC)), s32 *, 8));
}
