#include "shared/object_node.h"
#include "common.h"
#include "shared/sys_flags.h"

#include "common.h"
#include "engine/node.h"
#include "slus.h"

/* Allocates and initializes a node with the requested flags and links it at the list head. */
void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head)
{
    ObjectNodeHeader *node;
    ObjectNodeHeader *free_node;
    u8 *payload_cursor;

    if ((system_update_flags & 0x2) && (flags & 0x200)) {
        return 0;
    }

    {
        extern ObjectNodeHeader *free_node_list_head;
        free_node = free_node_list_head;
    }
    if (free_node != 0) {
        node = free_node;
        {
            extern ObjectNodeHeader *free_node_list_head;
            free_node_list_head = node->next;
        }
        zero_words((int *)node, 0x49);

        node->next = *list_head;
        *list_head = node;
        node->pprev = list_head;
        if (node->next != 0) {
            node->next->pprev = (ObjectNodeHeader **)node;
        }

        node->flags = (u16)(flags | NODE_ACTIVE);

        payload_cursor = (u8 *)node + 0x124;
        if (flags & 0x100) {
            payload_cursor = (u8 *)node + 0xF4;
            node->sprite = payload_cursor;
        } else if (flags & 0x6) {
            payload_cursor = (u8 *)node + 0x100;
            node->sprite = payload_cursor;
        } else if (flags & 0x41) {
            payload_cursor = (u8 *)node + 0x10C;
            node->sprite = payload_cursor;
        }

        if (flags & 0x157) {
            payload_cursor = payload_cursor - 0x18;
            node->position = payload_cursor;
        }

        return node;
    }

    if (flags & 0x200) {
        return 0;
    }
    return evict_node_and_allocate(flags, list_head);
}
