#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800177C4();                     /* extern */

/* Call func_800177C4 for IDs 0x58E and 0x596 in order. */
void func_8054FBD0(void) {
    func_800177C4(0x58E);
    func_800177C4(0x596);
}
