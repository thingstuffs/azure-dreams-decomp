#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AA1F0();                            /* extern */

void func_8016BE40(void *arg0) {
    func_800AA1F0();
    M2C_FIELD(arg0, s16 *, 0xA2) = 0;
}
