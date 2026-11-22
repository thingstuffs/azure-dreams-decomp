#include "common.h"

#include "town/player/action_initializers.h"
#include "town/player.h"
extern void initialize_actor_movement_interaction_action(void *,void *,void *);
#include "town/scene/collision.h"
extern ColliderView town_actor_control;

/* Dispatch the actor's action using its cached entry or the entry lookup result. */
void begin_town_actor_interaction(void *actor, ObjectPosition *position, SpriteFrameState *sprite) {
    ColliderView *cached_entry;
    s32 action_result;

    cached_entry = *(ColliderView **)((u8 *)actor + 0x2C);
    if (cached_entry != 0) {
        town_actor_control.selected_entry = cached_entry;
        town_actor_control.selected_face = 0;
        initialize_actor_movement_interaction_action(actor, position, sprite);
    } else {
        action_result = select_adjacent_source_entry(actor, &town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, position, sprite);
            } else {
                initialize_scene_action_record(actor, position, sprite);
            }
        } else {
            initialize_scene_action_record(actor, position, sprite);
        }
    }
}
