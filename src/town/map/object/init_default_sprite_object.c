#include "common.h"
#include "shared/object_node.h"
#include "town/map/object_setup.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "town/map/animated_prop.h"
#include "engine/node.h"
#include "slus.h"
#include "town/map/object.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/map/state.h"

extern u8 D_80089634[];

extern u8 D_800D20F4[];

/* Initializes the object with default data and updates its associated state. */
void init_default_sprite_object(void *object_arg, ObjectPosition *init_arg, SpriteFrameState *state)
{
    TownPropAnimationActor *object = object_arg;
    state->flags |= 0x1C;
    NODE_HEADER(object)->update_callback = cycle_prop_animation_until_done;
    object->unk_50 = 0;
    object->interaction_script = D_80089634;
    register_node(NODE_HEADER(object), project_sprite_chain);

    object->sources[0] = town_object_defaults[0];
    object->sources[1] = town_object_defaults[1];
    object->sources[2] = town_object_defaults[2];
    init_scene_node_mode_3(&object->scene, init_arg, D_800D20F4);
    select_record_entry_and_value(state, town_object_defaults[2], 0);
}
