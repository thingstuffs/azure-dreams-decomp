#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 scene_event_buffer[];
/* Returns a pointer to D_8001DCD4. */
u8 *get_shared_event_data_buffer(void) {
    return scene_event_buffer;
}
