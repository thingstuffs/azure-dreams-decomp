#include "shared/object_node.h"
#include "common.h"
#include "shared/sys_flags.h"

#include "common.h"



typedef struct S_80013714 {
    u16 flags;      /* 0x0 */
    u8 pad[8];      /* keep size > 8 to force %hi/%lo addressing */
} S_80013714;


extern void zero_words(int *p, int n);
extern void *evict_node_and_allocate(s32 a0, void *a1);

/* Allocates and initializes a node with the requested flags and links it at the list head. */
void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head)
{
    ObjectNodeHeader *node;
    ObjectNodeHeader *free_node;
    u8 *payload_cursor;

    if ((D_80013714 & 0x2) && (flags & 0x200)) {
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

        node->flags = (u16)(flags | 0x4000);

        payload_cursor = (u8 *)node + 0x124;
        if (flags & 0x100) {
            payload_cursor = (u8 *)node + 0xF4;
            node->unk_0C = payload_cursor;
        } else if (flags & 0x6) {
            payload_cursor = (u8 *)node + 0x100;
            node->unk_0C = payload_cursor;
        } else if (flags & 0x41) {
            payload_cursor = (u8 *)node + 0x10C;
            node->unk_0C = payload_cursor;
        }

        if (flags & 0x157) {
            payload_cursor = payload_cursor - 0x18;
            node->unk_08 = payload_cursor;
        }

        return node;
    }

    if (flags & 0x200) {
        return 0;
    }
    return evict_node_and_allocate(flags, list_head);
}
