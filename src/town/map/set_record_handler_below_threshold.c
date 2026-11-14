#include "common.h"
#include "engine/resource.h"
#include "town/map.h"
#include "town/map/object_callbacks_api.h"

extern u8 town_position_reference_state[];


/* Set the record parameter and handler when the global value check is below 0xE0000. */
void set_record_handler_below_threshold(void *record) {
    u8 *base = town_position_reference_state;

    if (estimate_vector_length(*(s32 *) (base + 0xC), *(s32 *) (base + 0x10)) <= 0xDFFFF) {
        *(s16 *) ((u8 *) record + 4) = 0x400;
        *(void **) ((u8 *) record + 0x1C) = select_title_object_handler;
    }
}
