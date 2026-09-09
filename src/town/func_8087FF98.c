#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700C54(s32, s32, s32, s32);                            /* extern */
extern s32 D_80700A18[];
__asm__(".set D_80700A18, 0x80700A18");

s32 func_8087FF98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80700C54(arg0, arg1, arg2, arg3);
    return D_80700A18[arg0];
}
