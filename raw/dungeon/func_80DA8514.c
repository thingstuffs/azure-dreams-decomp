#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_8015B87C;

void func_80159D14(void *arg0, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x10;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s16 *, 0xA4) = 8;
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015B87C;
    func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015B87C), 0);
}
