#include "common.h"
#include "shared/object_index_slots.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
s16 clamp_transform_coordinate_deltas(s32, s32, void *);
void forward_player_motion_state(void *state, s32 value, s32 mode);

/* Clears the object slot flag, sets its handler, and updates its position-dependent value. */
void set_player_handler_and_position_value(void *object, s32 value_arg, s32 handler_param) {
    s32 saved_value_arg;

    call_the_handler_selects_nonzero_entry(*(s32 **)(*(void **)((u8 *)object + 0x44) + 0x14), object, (void *)(handler_param));
    saved_value_arg = value_arg;
    *((s8 *)(D_80082660) + (*(s32 *)((u8 *)object + 0x40) * 8)) = 0;
    *(void **)((u8 *)object + 4) = &forward_player_motion_state;
    *(s16 *)((u8 *)object + 0x10) = clamp_transform_coordinate_deltas(
        *(s16 *)((u8 *)object + 0x36),
        *(s16 *)((u8 *)object + 0x38),
        (void *)(saved_value_arg));
}
