#include "town/player/carry_item.h"
#include "shared/object_node.h"
#include "town/player.h"

extern s32 scene_object_payload_alias;

/* Run plt_carry_on_chk_ext using the global record and its context values. */
void *plt_carry_on_chk_ext(void) {
    void *record = &scene_object_payload_alias;
    ObjectNodeHeader *node = NODE_HEADER(record);


    return get_linked_carry_item_data(record, node->position, node->sprite);
}
