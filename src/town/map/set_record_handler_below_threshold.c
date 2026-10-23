#include "common.h"

extern u8 town_position_reference_state[];
extern s32 map_fallback_handler_address;

extern s32 runtime_estimate_vector_length(s32 a0, s32 a1);

/* Set the record parameter and handler when the global value check is below 0xE0000. */
void set_record_handler_below_threshold(void *record) {
    u8 *base = town_position_reference_state;

    if (runtime_estimate_vector_length(*(s32 *) (base + 0xC), *(s32 *) (base + 0x10)) <= 0xDFFFF) {
        *(s16 *) ((u8 *) record + 4) = 0x400;
        *(void **) ((u8 *) record + 0x1C) = &map_fallback_handler_address;
    }
}
