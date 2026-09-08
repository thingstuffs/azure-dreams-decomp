#include "common.h"

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

extern ListHead D_80081498;
extern s32 D_800814A0;

/* Set flag 0x8000 on nodes with the given ID and on the list status. */
void func_800B97D8(s32 id)
{
    ListNode *node = D_80081498.head;

    if (node != 0) {
        do {
            if (node->id == id) {
                node->flags |= 0x8000;
                D_800814A0 |= 0x8000;
            }
            node = node->next;
        } while (node != 0);
    }
}
