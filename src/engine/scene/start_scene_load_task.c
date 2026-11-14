#include "common.h"
#include "engine/scene.h"

/* Creates a task and, on success, updates the owner's existing task callback. */
void start_scene_load_task(SceneLoadBody *owner)
{
    void *new_task = create_deferred_resource_transition_task(1, 0x1E, load_scene_record, owner);

    if (new_task != 0) {
        owner->task->update_callback = propagate_task_flag_to_parent;
    }
}
