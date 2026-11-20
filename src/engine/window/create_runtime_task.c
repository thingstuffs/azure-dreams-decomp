#include "common.h"
#include "shared/object_index_slots.h"

#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/scene.h"
#include "engine/window.h"
#include "sdk/libc.h"
#include "slus/window_node_list_data.h"

typedef struct RuntimeTask {
    u8 pad00[0x10];
    void (*sync)(MessageWindowLinks *);
    u8 pad14[0x0C];
    MessageWindowLinks links;
} RuntimeTask;

extern u8 D_80012D6E[9];

/* Create the runtime task and initialize its shared state and blocks. */
void initialize_message_window_runtime_task(void)
{
    RuntimeTask *task;
    MessageWindowLinks *links;
    ScriptController *controller;
    ScriptController *linked_controller;
    u8 *state_data;
    s32 index;

    task = initialize_scene_object_in_buffer(0, &window_node_list_storage, 0x49);
    links = &task->links;
    task->sync = sync_message_window_state;
    links->controller = &runtime_script_state;
    links->window = &runtime_script_state.window;

    for (index = 0; index < 107; index++) {
        memset(&object_index_slots[index], 0, sizeof(object_index_slots[index]));
    }

    for (index = 15; index >= 0; index--) {
        runtime_script_state.variables[index] = 0;
    }

    do {
        controller = &runtime_script_state;
    } while (0);
    state_data = message_window_state_data;
    controller->default_script = state_data;
    controller->script_start = 0;
    do {
        linked_controller = links->controller;
    } while (0);
    linked_controller->text_speed = D_80012D6E[0];
    init_message_window(links->controller, 3);
    links->window->skip_disabled = 0;
    links->window->active = 0;
    links->window->field86 = links->window->active;
}
