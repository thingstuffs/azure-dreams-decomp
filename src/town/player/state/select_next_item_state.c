#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/map/resource.h"
#include "town/player/state.h"

#include "town/player/action_initializers.h"
#include "town/player.h"
extern s32 town_item_menu_bag_full_message;

extern s32 *town_player_action_callback;
extern s32 town_interaction_pending;

/* Select the object's next state based on slot availability. */
void select_next_item_state(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *context) {
    if (get_item_chk() == -1) {
        write_resource_command(&town_item_menu_bag_full_message, 0x11);
        set_deferred_dispatch_handler(object, position, context);
        town_player_action_callback = initialize_scene_action_record;
        return;
    }
    init_timed_dispatch_action(object, position, context);
    town_interaction_pending = 0;
}
