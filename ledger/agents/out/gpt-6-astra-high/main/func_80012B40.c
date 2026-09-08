#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80025B38();                            /* extern */

/* Set the object's field at offset 0x20 to the supplied value. */
void func_80025B40(void *object, s32 value) {
    func_80025B38(object, value);
}
