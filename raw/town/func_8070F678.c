#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016CC4();                            /* extern */

s32 func_80018678(void) {
    func_80016CC4();
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK, M2C_UNK), 0x2F8)(0xE, 0x200);
    return 0;
}
