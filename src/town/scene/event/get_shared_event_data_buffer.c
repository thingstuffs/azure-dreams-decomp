#include "common.h"
#include "town/scene/event.h"
#include "town/scene/event_buffer_data.h"

/* Returns the current value of scene_event_buffer. */
u8 *get_shared_event_data_buffer(void) {
    return scene_event_buffer;
}
