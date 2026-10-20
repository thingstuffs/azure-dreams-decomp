#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8001DCD4[];
/* Returns a pointer to D_8001DCD4. */
u8 *get_shared_event_data_buffer(void) {
    return D_8001DCD4;
}
