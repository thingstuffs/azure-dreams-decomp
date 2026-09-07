#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_8003ADF4(); /* extern */
extern s32 D_8006ADD4;
extern M2C_UNK D_800FC428;

void func_8008C2B8(void) {
    if (D_8006ADD4 == 0x13000C) {
        func_8003ADF4(0x360, 0x100, 0x20, 0x80, &D_800FC428);
    }
}
