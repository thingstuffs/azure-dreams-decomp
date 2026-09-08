#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80017A48();                            /* extern */

/* Forward an object and its entry index to func_80017A48. */
void func_8069723C(void *object, s32 entry_index) {
    func_80017A48(object, entry_index);
}
