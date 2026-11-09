#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "engine/node.h"
#include "town/menu/object.h"

#include "town/system/clear_object_status_and_dispatch_target_api.h" /* extern */
void finalize_checked_object_or_fallback(void *object, void *check_data, void *fallback_data);
extern M2C_UNK D_800F838C;

/* Initialize the object with its state, resource data, and callback. */
void initialize_effect_object(void *object, ObjectPosition *unused, struct SpriteFrameState *context) {
    NODE_HEADER(object)->update_callback = &finalize_checked_object_or_fallback;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F838C), 0);
    register_node_if_unregistered(object, project_sprite_chain);
}
