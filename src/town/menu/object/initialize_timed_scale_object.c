#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_views.h"


   /* arg1 in initialize_timed_scale_object */

#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "town/menu/object.h"
#include "engine/node.h"
#include "town/menu.h"

extern void run_record_handler_if_active(void *record, s32 context, s32 update_data);
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void initialize_timed_scale_object(void *object, ObjectPosition *state, struct SpriteFrameState *context) {
    NODE_HEADER(object)->update_callback = &run_record_handler_if_active;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F842C), 0);
    register_node_if_unregistered(object, project_sprite_chain);
    state->z.w.i = 0;
    initialize_randomized_scale_timer(object, state, context);
}
