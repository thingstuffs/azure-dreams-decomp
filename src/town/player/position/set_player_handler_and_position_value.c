#include "common.h"
#include "shared/object_index_slots.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/person/position.h"
#include "town/player/motion.h"
#include "town/player/position.h"
#include "shared/sprite_frame_state.h"

/* Clears the object slot flag, sets its handler, and updates its position-dependent value. */
void set_player_handler_and_position_value(TownObjectRecord *object, s32 value_arg, SpriteFrameState *handler_param) {
    s32 saved_value_arg;

    dispatch_selected_entry_if_nonzero(object->handler_entries[5], object, (void *)(handler_param));
    saved_value_arg = value_arg;
    *((s8 *)(object_index_slots) + (object->unk_40 * 8)) = 0;
    object->unk_04 = &forward_player_motion_state;
    object->unk_10 = clamp_transform_coordinate_deltas(
        *(s16 *)((u8 *)object + 0x36),
        *(s16 *)((u8 *)object + 0x38),
        (void *)(saved_value_arg));
}
