#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
s16 clamp_transform_coordinate_deltas(s32 x, s32 y, void *origin);
void forward_player_motion_state(void *state, s32 value, s32 mode);

/* Clears the object's slot flag and initializes its state pointer and lookup result. */
void initialize_indexed_object_and_lookup_value(void *object, s32 lookup_arg, s32 handler_param) {
    s32 saved_lookup_arg;

    call_the_handler_selects_nonzero_entry(movement_action_handler_table, object, handler_param);
    saved_lookup_arg = lookup_arg;
    object_index_slots[*(s32 *)((s8 *)object + 0x40)].unk_00 = 0;
    *(s32 **)((s8 *)object + 4) = &forward_player_motion_state;
    *(s16 *)((s8 *)object + 0x10) = clamp_transform_coordinate_deltas(*(s16 *)((s8 *)object + 0x36), *(s16 *)((s8 *)object + 0x38),
        saved_lookup_arg);
}
