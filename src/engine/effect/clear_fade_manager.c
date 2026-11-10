#include "common.h"

#include "engine/effect.h"
#include "engine/node.h"
#include "engine/resource.h"

/* Clears the fade manager's step, ends the fade on its sprite, and unlinks the manager node. */
void clear_fade_manager(void) {
    fade_manager_state.step = 0;
    runtime_clear_record_field_04(&fade_manager_state, NODE_HEADER(&fade_manager_state)->sprite);
    unlink_node_if_registered(&fade_manager_state);
}
