#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80017A48();                            /* extern */

/* Dispatch an object's indexed entry to the shared handler. */
void func_806972F4(void *object, s32 entry_index) {
    func_80017A48(object, entry_index);
}
