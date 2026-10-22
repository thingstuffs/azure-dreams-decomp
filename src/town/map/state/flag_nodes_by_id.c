#include "common.h"
#include "shared/object_flags.h"

typedef struct ListNode {
    struct ListNode *next;
    u8 pad_04[0xC];
    s32 id;
    u8 pad_14[0xA];
    u16 flags;
} ListNode;

typedef struct {
    ListNode *head;
    s32 pad[2];
} ListHead;

extern ListHead active_node_list_head;
extern s32 D_800814A0;

/* Set flag 0x8000 on nodes with the given ID and on the list status. */
void flag_nodes_by_id(s32 id)
{
    ListNode *node = active_node_list_head.head;

    if (node != 0) {
        do {
            if (node->id == id) {
                node->flags |= 0x8000;
                D_800814A0 |= OBJECT_REMOVE_PENDING;
            }
            node = node->next;
        } while (node != 0);
    }
}
