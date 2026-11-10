#include "town/player/init_movement_action.h"
#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/position_handlers.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "shared/sprite_frame_state.h"

/* Reset and initialize the record with its handler and a count of six. */
void init_movement_action(TownObjectRecord *record, void *unused, SpriteFrameState *sprite) {
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D0108, record, sprite);
    record->unk_00 = &update_actor_movement_actions;
    record->unk_0A = 6;
}
