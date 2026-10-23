#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 scene_event_buffer[];
/* Returns a pointer to D_8001DCD4. */
u8 *get_event_data_pointer(void) {
    return scene_event_buffer;
}
