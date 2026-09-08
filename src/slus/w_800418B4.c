#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003E4FC(); /* extern */
M2C_UNK func_8003F320();                            /* extern */
extern s8 D_80080A89;
extern M2C_UNK D_80080C50;

/* Run initialization once and mark it complete. */
void func_800418B4(void) {
    if (D_80080A89 == 0) {
        func_8003E4FC(6, &D_80080C50, 0);
        func_8003F320();
        D_80080A89 = 1;
    }
}
