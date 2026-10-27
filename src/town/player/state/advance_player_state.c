#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/scene_action_setup.h"

void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                      /* extern */


/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void advance_player_state(struct Rec_func_80094268_arg0 *context, EntityRec *state, void *updateData) {
    state->z.v = (s32) (state->z.v + state->flags14);
    add_hex_20000_s_signed_offset_hex_14(state);
    if (state->flags14 >= 0) {
        initialize_player_linked_record(context, state, updateData);
    }
}
