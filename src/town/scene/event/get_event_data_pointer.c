#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 scene_event_buffer[];
/* Returns the current value of scene_event_buffer. */
u8 *get_event_data_pointer(void) {
    return scene_event_buffer;
}
