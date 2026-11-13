#include "common.h"
#include "town/person/object_setup.h"
#include "town/event/object_setup.h"
#include "town/scene/list_setup.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person.h"
#include "town/event/state.h"
#include "shared/object_node.h"
#include "town/data.h"
#include "town/person/object.h"

extern s32 D_800D11D0[];
extern s32 D_800D11EC[];


/* Initialize the object's resources, animation state, and callback table. */
void initialize_person_resources(TownObjectRecord *object, ObjectPosition *transform, SpriteFrameState *anim_state) {
    init_scene_node_mode_2(object, transform, &town_object_resource_table);
    initialize_optional_object_state(object, transform, anim_state, &D_800D11D0);
    initialize_object_entries(object, anim_state, D_800D11EC);
    NODE_HEADER(object)->update_callback = update_person_object;
}
