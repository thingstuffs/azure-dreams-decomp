#include "common.h"
#include "engine/menu.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "town/minigame/object.h"

typedef struct {
    s32 words[10];
} Record;



/* Allocate an object, copy its record, set its value, and pass it for initialization. */
void create_menu_line_object(void *object_value, void *record) {
    ObjectNodeHeader *object;

    object = allocate_list_node(1, &scene_object_list_anchor.next);
    if (object != 0) {
        *((Record *)NODE_BODY(object)) = *(Record *)record;
        object->update_callback = object_value;
        register_node(object, build_menu_line_tile_packets);
    }
}
