#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003E4FC();    /* extern */
M2C_UNK func_8003F320();                            /* extern */
extern u8 D_800DF3EC[];

/* Submit the indexed eight-byte entry and finalize the operation. */
void func_800BD184(s32 entry_index) {
    func_8003E4FC(6, ((s32) (entry_index << 0x10) >> 0xD) + D_800DF3EC, 0);
    func_8003F320();
}
