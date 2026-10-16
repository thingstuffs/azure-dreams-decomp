#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 D_80082680;
void townInitializeMotherEventDefaults(void *);                            /* extern */

/* Clear D_80082680 and pass the object to townInitializeMotherEventDefaults. */
void townResetMotherEventGlobalState(void *object) {
    D_80082680 = 0;
    townInitializeMotherEventDefaults(object);
}
