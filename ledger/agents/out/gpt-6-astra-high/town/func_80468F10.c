#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK *D_80017B90;
/* Passes the global pointer's address to func_80019CE0. */
void func_80019F10(void) {
    func_80019CE0(&D_80017B90);
}
