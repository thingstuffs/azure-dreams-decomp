#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "slus/data.h"

/* Create the fade manager node in its static storage, install its step runner, and clear its step. */
void create_marked_callback_node(void) {
    ObjectNodeHeader *node;
    FadeManagerBody *manager;

    node = initialize_scene_object_in_buffer(0x15, &callback_node_storage, 0x49);
    node->update_callback = &run_node_callback_and_set_marker;
    manager = NODE_BODY(node);
    manager->step = 0;
}
