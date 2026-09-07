#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019438;
s32 func_80016B20();              /* extern */
extern M2C_UNK D_80019440;

void func_80480468(void) {
    D_80019438 = func_80016B20(&D_80019440, 1);
}
