#include "common.h"
#include "shared/object_node.h"
#include "town/map/object_setup.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800CFCB4.h"
#include "engine/node.h"
#include "slus.h"
#include "town/map/object.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/map/state.h"

extern u8 D_80089634[];

extern u8 D_800D20F4[];

/* Initializes the object with default data and updates its associated state. */
void initialize_object_with_default_data(void *object_arg, ObjectPosition *init_arg, SpriteFrameState *state)
{
    Rec_D_800CFCB4 *object = object_arg;
    s32 *defaults;

    state->flags |= 0x1C;
    NODE_HEADER(object)->update_callback = copy_record_state_to_destination;
    object->unk_50 = 0;
    object->unk_48 = D_80089634;
    register_node(NODE_HEADER(object), project_sprite_chain);

    defaults = town_object_defaults;
    object->unk_A0 = defaults[0];
    object->unk_A4 = defaults[1];
    object->unk_A8 = defaults[2];
    init_scene_node_mode_3(object, init_arg, D_800D20F4);
    select_record_entry_and_value(state, defaults[2], 0);
}
