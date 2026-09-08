#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018A64();                     /* extern */

/* Call func_80018A64 with IDs 0x1476 and 0x5C3 in sequence. */
void func_8051EAD0(void) {
    func_80018A64(0x1476);
    func_80018A64(0x5C3);
}
