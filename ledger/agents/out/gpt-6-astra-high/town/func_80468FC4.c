#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80019D60();                   /* extern */
extern M2C_UNK D_80017BA4;

/* Pass D_80017BA4 to func_80019D60. */
void func_80019FC4(void) {
    func_80019D60(&D_80017BA4);
}
