#include "common.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F074_arg0.h"
#include "town/scene.h"



/*
 * Initializes the scene-list record with the supplied values and sets its mode byte at offset 0x14
 * to 1.
 */
void init_scene_node_mode_1(void *record, void *position, void *bounds) {
    TownSceneListNode *node = record;
    init_scene_list_node(record, position, bounds);
    node->mode = 1;
}
