#include "engine/effect/resource_transition.h"
#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "shared/object_node.h"

/* Registers the object's input handler and installs its update callback on success. */
void schedule_deferred_resource_transition(struct ResourceTransitionBody *object)
{
    if (create_deferred_resource_transition_task(1, 0x1E, dispatch_after_controller_release, object) != 0) {
        NODE_HEADER(object)->update_callback = load_transition_image_and_begin_data_read;
    }
}
