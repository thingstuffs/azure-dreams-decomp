#include "town/player.h"
#include "common.h"
#include "shared/town_object.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"




void dispatch_selected_entry_if_nonzero(s32 *entries, TownObjectRecord *record, void *ptr2);



/* Initialize the record from linked data and apply its update parameters. */
void initialize_player_motion_parameters(void *record, ObjectPosition *update_value, SpriteFrameState *sprite) {
    dispatch_selected_entry_if_nonzero(((TownObjectRecord *)record)->handler_entries[9], record, sprite);
    set_player_travel_timing(record, update_value, sprite);
}
