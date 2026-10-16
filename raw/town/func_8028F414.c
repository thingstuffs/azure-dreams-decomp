#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001AD60(s16);                         /* extern */
extern s32 D_8001C370;

void func_80019C14(void) {
    func_8001AD60(M2C_FIELD(((M2C_FIELD(*(void **)0x80016000, s32 *, 0x14) * 0x1C) + D_8001C370), s16 *, 0x18));
}
