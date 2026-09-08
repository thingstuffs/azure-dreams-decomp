#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80019928();                            /* extern */

/* Forward the context and entry index to the shared handler. */
void func_80016480(s32 context, s32 entry_index) {
    func_80019928(context, entry_index);
}
