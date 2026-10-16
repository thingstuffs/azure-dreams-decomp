#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008FD48(s32);                         /* extern */
extern M2C_UNK D_800C28E8;
extern M2C_UNK D_800D4F88;

void func_800C2890(void *arg0) {
    func_8008FD48(*((M2C_FIELD(arg0, u8 *, 0x94) * 4) + &D_800D4F88));
    M2C_FIELD(arg0, s8 *, 0x14) = 1;
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800C28E8;
}
