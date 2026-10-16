#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townApplyObjectSetupAndUpdate(void *, M2C_UNK, M2C_UNK);                            /* extern */

/* Forward the object and update arguments to townApplyObjectSetupAndUpdate. */
void func_800CE538(void *object, M2C_UNK context, M2C_UNK update_data) {
    townApplyObjectSetupAndUpdate(object, context, update_data);
}
