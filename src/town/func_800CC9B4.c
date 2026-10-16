#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeReactionDataAndTimer10(void *);                            /* extern */

/* Pass the object to townInitializeReactionDataAndTimer10. */
void townForwardReactionObject(void *object) {
    townInitializeReactionDataAndTimer10(object);
}
