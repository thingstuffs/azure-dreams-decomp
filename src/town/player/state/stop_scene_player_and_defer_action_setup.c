#include "common.h"
#include "shared/object_node.h"
#include "town/player/object.h"
#include "town/player/state.h"
#include "town/player.h"
#include "town/scene/hooks.h"

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record,void *handler_param);

extern u8 scene_object_payload_alias[];


extern u8 town_scene_record_handlers[];
extern void *town_player_action_callback;

/*
 * Stops the scene player object for a minigame step: clears its velocity, reselects its scene record
 * handler, replaces its update callback with a no-op and queues initialize_scene_action_record as the
 * deferred player action.
 */
void stop_scene_player_and_defer_action_setup(void) {
    void *object;
    ObjectNodeHeader *object_header;
    s32 header_value;

    object = scene_object_payload_alias;
    object_header = NODE_HEADER(object);
    header_value = *(s32 *)&object_header->sprite;
    clear_object_velocity(*(s32 *)&object_header->position);
    dispatch_selected_entry_if_nonzero(town_scene_record_handlers, object, header_value);
    *(void **)scene_object_payload_alias = noop_at_8008_ffc_0;
    town_player_action_callback = initialize_scene_action_record;
}
