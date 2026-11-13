#include "common.h"
#include "shared/object_flags.h"
#include "town/map/door.h"
#include "town/map/state.h"
extern s32 D_800814A0;

/* Set flag 0x8000 on nodes with the given ID and on the list status. */
void flag_nodes_by_id(s32 id)
{
    Node *node = active_node_list_head.head;

    if (node != 0) {
        do {
            if (node->field_10 == id) {
                node->flags |= 0x8000;
                D_800814A0 |= OBJECT_REMOVE_PENDING;
            }
            node = node->next;
        } while (node != 0);
    }
}
