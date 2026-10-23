#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 mother_event_reset_byte;
void initialize_mother_event_defaults(void *);                            /* extern */

/* Clear D_80082680 and pass the object to initialize_mother_event_defaults. */
void reset_mother_event_global_state(void *object) {
    mother_event_reset_byte = 0;
    initialize_mother_event_defaults(object);
}
