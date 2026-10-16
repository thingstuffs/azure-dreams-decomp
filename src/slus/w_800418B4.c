#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK Control_CD(); /* extern */
M2C_UNK drainCdCommandQueue();                            /* extern */
extern s8 D_80080A89;
extern M2C_UNK D_80080C50;

/* Run initialization once and mark it complete. */
void loadSharedResourceOnce(void) {
    if (D_80080A89 == 0) {
        Control_CD(6, &D_80080C50, 0);
        drainCdCommandQueue();
        D_80080A89 = 1;
    }
}
