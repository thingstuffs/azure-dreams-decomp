#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/position_handlers.h"
#include "town/player/motion.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "shared/sprite_frame_state.h"
#include "town/player/input.h"

/* Set up the entity state and motion, then install its handler table. */
void initialize_motion_action(TownObjectRecord *entity, void *motion, SpriteFrameState *sprite) {
    entity->unk_3E = 6;
    store_input_angle(entity);
    accelerate_toward_input_keep_speed(motion);
    dispatch_selected_entry_if_nonzero(approach_action_handler_table, entity, sprite);
    entity->unk_00 = dispatch_actor_input_actions;
}
