#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003BAF8();                         /* extern */
s32 func_800B2834();                                /* extern */
extern M2C_UNK D_8006AFF4[];

void func_8003BA60(void) {
    func_8003BAF8(D_8006AFF4[func_800B2834()]);
}
