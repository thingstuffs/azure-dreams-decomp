#include "common.h"
#include "town/player.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "engine/node.h"
#include "town/player/motion.h"

#include "town/player/initialize_record_with_handler_table_api.h"
#include "shared/sprite_frame_state.h"

/* Processes the object, clears its indexed flag, and invokes the next handler. */
void process_player_motion_state(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    register_node_if_unregistered(object, draw_entry_overlays);
    object_index_slots[object->unk_40].unk_00 = 0;
    initialize_record_with_handler_table(object, position, sprite);
}
