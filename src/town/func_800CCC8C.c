#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townApplyObjectSetupAndUpdate(void *, M2C_UNK, M2C_UNK);                            /* extern */

/* Forward the object and parameters to townApplyObjectSetupAndUpdate. */
void townForwardReactionUpdate(void *object, M2C_UNK param_1, M2C_UNK param_2) {
    townApplyObjectSetupAndUpdate(object, param_1, param_2);
}
