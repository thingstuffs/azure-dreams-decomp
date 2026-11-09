#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "shared/object_node.h"

/* Registers the object's input handler and installs its update callback on success. */
void schedule_deferred_resource_transition(void *object)
{
    void *handler_object = object;

    if (create_deferred_resource_transition_task(1, 0x1E, dispatch_after_controller_release, handler_object) != 0) {
        NODE_HEADER(handler_object)->update_callback = load_transition_image_and_begin_data_read;
    }
}
