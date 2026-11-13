#include "common.h"
#include "town/scene/list_setup.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "town/scene.h"



/*
 * Initializes the scene-list record with the supplied values and sets its mode byte at offset 0x14
 * to 4.
 */
void init_scene_node_mode_4(void *record, void *position, void *bounds) {
    TownSceneListNode *node = record;
    init_scene_list_node(record, position, bounds);
    node->mode = 4;
}
