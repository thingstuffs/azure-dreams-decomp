#include "modules/town_door.h"

/* Updates the object's state and applies completion effects when it reaches zero. */
void update_door_completion_state(u8 *object, s32 unused, s32 state_id, s32 state_arg) {
    s16 state;

    state = initialize_object_items_in_reverse(D_80100B70, state_id, *(s16 *)(object + 0x90));
    *(s16 *)(object + 0x90) = state;
    if ((s32)(state << 0x10) == 0) {
        no_op_callback_a(D_80100B70, state_id, state_arg);
        *(void **)(object + 0x50) = advance_door_state_counter;
        load_indexed_resource_package(0);
        sound_set_cd_cue_parameters(0, D_8006CD58[0], 0x0600065E, 0x030008B6);
        SD_Call(0x300);
    }
}
