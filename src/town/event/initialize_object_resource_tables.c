#include "common.h"
#include "town/scene/list_setup.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"
#include "town/event/state.h"
#include "town/event.h"
#include "town/data.h"

extern s32 D_800D06AC[];
extern s32 D_800D0704[];
extern s32 D_800F8C44[];

/* Sets up an object's resource tables and associated state. */
void initialize_object_resource_tables(TownObjectRecord *object, ObjectPosition *init_arg, SpriteFrameState *state) {
    state->source = D_800F8C44;
    *(void **)((u8 *)object + 0x80) = D_800D0704;
    init_scene_list_node(object, init_arg, town_object_resource_table);
    initialize_optional_object_state(object, init_arg, state, D_800D06AC);
}
