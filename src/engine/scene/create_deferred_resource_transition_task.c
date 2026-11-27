#include "shared/object_node.h"
#include "common.h"

#include "engine/resource.h"
#include "engine/scene.h"
#include "slus/node_update_data.h"

typedef struct TaskPayload {
    void *(*field_0)(void *);
    void *resource;
    s16 slot_index;
    s16 state;
    s16 slot_argument;
} TaskPayload;

typedef struct Task {
    u8 pad_00[0x10];
    void (*callback)(void *);
    u8 pad_14[0x0C];
    TaskPayload payload;
} Task;

/* Creates a task with a mode-dependent lookup result and the supplied payload values. */
Task *create_deferred_resource_transition_task(s16 mode, s16 lookup_id, void *(*handler)(void *), void *context)
{
    TaskPayload *payload;
    Task *task;

    task = allocate_flagged_object_node(0);
    if (task != 0) {
        task->callback = update_deferred_resource_transition_task;
        payload = &task->payload;
        if (mode == 1) {
            payload->slot_index = reserve_transition_slot(6, lookup_id);
        } else if (mode == 0) {
            payload->slot_index = reserve_transition_slot(5, lookup_id);
            unflag_all_active_nodes();
            node_update_mode = 0;
        }
        payload->resource = context;
        payload->state = mode;
        payload->slot_argument = lookup_id;
        payload->field_0 = handler;
    }
    return task;
}
