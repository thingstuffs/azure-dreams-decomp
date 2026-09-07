#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E4FC();    /* extern */
M2C_UNK func_8003F320();                            /* extern */
extern u8 D_800DF3EC[];

void func_800BD184(s32 arg0) {
    func_8003E4FC(6, ((s32) (arg0 << 0x10) >> 0xD) + D_800DF3EC, 0);
    func_8003F320();
}
