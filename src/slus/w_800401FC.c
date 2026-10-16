#include "common.h"

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern Node *D_80081498;

extern void func_80044A50(Node *a0);
extern void unlinkActiveNode(Node *a0);
extern void pushNodeOntoFreeList(void *a0);

/* Detaches nodes flagged 0x8000 from the global list and frees those without flag 0x80 after detachment. */
void removeMarkedActiveNodes(void)
{
    Node *node;
    Node *next;

    node = D_80081498;
    if (node != 0) {
        do {
            next = node->next;
            if (node->field_1E & 0x8000) {
                func_80044A50(node);
                unlinkActiveNode(node);
                if (!(node->field_1E & 0x80)) {
                    pushNodeOntoFreeList(node);
                }
            }
            node = next;
        } while (node != 0);
    }
}
