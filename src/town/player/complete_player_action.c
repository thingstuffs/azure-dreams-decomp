#include "town/player/initialize_record_with_handler_table_api.h"
#include "town/player/record.h"
#include "common.h"
#include "shared/object_index_slots.h"
#include "engine/node.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"


/* Clean up the actor, clear its indexed flag, and complete its current action. */
void complete_player_action(void *actor_arg, ObjectPosition *motionState, SpriteFrameState *sprite) {
    TownPlayerRecord *actor = actor_arg;

    unlink_node_if_registered(actor);
    *(((actor->slot) * 8) + ((u8 *)object_index_slots)) = 0;
    initialize_record_with_handler_table(actor, motionState, sprite);
}
