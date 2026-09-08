#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B6BC4();                         /* extern */
extern s32 D_80100AF4;

/* Passes D_80100AF4 to func_800B6BC4 and returns zero. */
s32 func_8009E348(void) {
    func_800B6BC4(D_80100AF4);
    return 0;
}
