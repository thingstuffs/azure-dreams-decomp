#include "common.h"

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern Node *D_80081498;

extern void unlink_node(Node *a0);
extern void unlink_active_node(Node *a0);
extern void push_node_onto_free_list(void *a0);

/* Detaches nodes flagged 0x8000 from the global list and frees those without flag 0x80 after detachment. */
void remove_marked_active_nodes(void)
{
    Node *node;
    Node *next;

    node = D_80081498;
    if (node != 0) {
        do {
            next = node->next;
            if (node->field_1E & 0x8000) {
                unlink_node(node);
                unlink_active_node(node);
                if (!(node->field_1E & 0x80)) {
                    push_node_onto_free_list(node);
                }
            }
            node = next;
        } while (node != 0);
    }
}
