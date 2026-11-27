#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/town_object.h"

#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "engine/node.h"
#include "town.h"

extern M2C_UNK D_800F8F68;

/* Clear the object state field and initialize its resource data and callback. */
void initialize_resource_object(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *context) {
    NODE_HEADER(object)->update_callback = &retire_object_or_animate_sprite;
    object->state_callback.as_s32 = 0;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F8F68), 0);
    register_node_if_unregistered(object, (project_sprite_chain));
}
