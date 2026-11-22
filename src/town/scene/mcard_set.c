#include "common.h"
#include "town/scene/script_hooks.h"
#include "shared/object_node.h"

#include "slus/resource_transition_task.h"
#include "town/scene.h"

/* Set up mcard_func_set after clearing flag bit 0x2000. */
void *mcard_func_set(void) {
    scene_object_list_anchor.flags &= 0xDFFF;
    return create_resource_transition_card(&scene_object_list_anchor);
}
