#include "common.h"
#include "town/scene/event.h"

extern u8 scene_event_buffer[];
/* Returns the current value of scene_event_buffer. */
u8 *get_shared_event_data_buffer(void) {
    return scene_event_buffer;
}
