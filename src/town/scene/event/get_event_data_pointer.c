#include "common.h"
#include "town/scene/event.h"

extern u8 scene_event_buffer[];
/* Returns the current value of scene_event_buffer. */
u8 *get_event_data_pointer(void) {
    return scene_event_buffer;
}
