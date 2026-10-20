#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_reaction_data_and_timer_10(void *);                            /* extern */

/* Pass the object to initialize_reaction_data_and_timer_10. */
void forward_reaction_object(void *object) {
    initialize_reaction_data_and_timer_10(object);
}
