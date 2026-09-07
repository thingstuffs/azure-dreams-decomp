#include "common.h"

/* Walks the global singly-linked list headed by D_80081498. For every node
   with the 0x8000 flag bit set in field_1E, detaches it (func_80044A50,
   func_8003FFF0) and, unless the (now updated) field_1E has bit 0x80 set,
   frees it onto the freelist via func_80040044. */
typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern struct {
    Node *head;
    int pad[2];
} D_80081498;

extern void func_80044A50(Node *a0);
extern void func_8003FFF0(Node *a0);
extern void func_80040044(void *a0);

void func_800401FC(void)
{
    Node *node;
    Node *next;

    node = D_80081498.head;
    if (node != 0) {
        do {
            next = node->next;
            if (node->field_1E & 0x8000) {
                func_80044A50(node);
                func_8003FFF0(node);
                if (!(node->field_1E & 0x80)) {
                    func_80040044(node);
                }
            }
            node = next;
        } while (node != 0);
    }
}
