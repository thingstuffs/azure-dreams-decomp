#include "common.h"
#include "shared/town_handler_entries.h"
#include "town/player.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"              /* extern */
#include "shared/sprite_frame_state.h"

/* Initialize the record from fixed data and apply its update parameters. */
void initialize_record_with_update_parameters(TownObjectRecord *record, ObjectPosition *update_value, SpriteFrameState *sprite) {
    call_the_handler_selects_nonzero_entry(D_800D0130, record, sprite);
    set_player_travel_timing(record, (update_value), sprite);
}
