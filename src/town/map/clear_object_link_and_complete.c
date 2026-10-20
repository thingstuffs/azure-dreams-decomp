#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void clear_object_link_and_mark_complete(void *, s32);                            /* extern */

/* Forward the object and value to clear_object_link_and_mark_complete. */
void clear_object_link_and_complete(void *object, s32 value) {
    clear_object_link_and_mark_complete(object, value);
}
