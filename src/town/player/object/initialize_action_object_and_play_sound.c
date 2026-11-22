#include "common.h"
#include "shared/town_handler_entries.h"
#include "slus.h"
#include "town/player/input.h"
#include "town/player/object.h"
#include "town/player.h"
#include "town/player/call_the_handler_selects_nonzero_entry_api.h" /* extern */
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                  /* extern */
#include "shared/entity.h"

/* Reset and initialize the record, then assign its handler. */
void initialize_action_object_and_play_sound(TownObjectRecord *record, ObjectPosition *unused_position, struct SpriteFrameState *sprite) {
    SD_Call(0x50B);
    store_input_angle(record);
    dispatch_selected_entry_if_nonzero(D_800D0110, record, sprite);
    record->unk_00 = update_actor_input_actions;
}
