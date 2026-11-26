/* Recovered retail twin. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "slus.h"
#include "town.h"
#include "town/player/state.h"


/* Plays sound 0x511, selects counted_action_handler_table, and installs update_actor_with_interaction_state with count six. */
void initialize_action_object_with_counter(TownObjectRecord *record, ObjectPosition *unused_position, struct SpriteFrameState *sprite) {
    SD_Call(0x511);
    dispatch_selected_entry_if_nonzero(counted_action_handler_table, record, sprite);
    record->unk_00 = update_actor_with_interaction_state;
    record->unk_0A = 6;
}
