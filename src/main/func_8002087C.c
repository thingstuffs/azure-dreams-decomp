#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_804072CC();                         /* extern */

/* Passes the input value plus 0x20 to func_804072CC. */
void func_8002087C(s32 value) {
    func_804072CC(value + 0x20);
}
