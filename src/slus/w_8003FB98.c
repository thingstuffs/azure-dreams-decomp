#include "common.h"

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern struct {
    Node *head;
    int pad[2];
} D_80081498;

extern void func_80044A50(void *a0);
extern void func_8003FFF0(void *a0);
extern void func_80040044(void *a0);
extern void *func_8003FD64(void *a0, void *a1);
extern void *func_8003FC64(void *a0);

/* Removes the first eligible active node other than excluded_node, then retries allocation. */
void *func_8003FB98(void *flags, void *excluded_node)
{
    Node *node;

    node = D_80081498.head;
    if (node != 0) {
        do {
            if ((node->field_1E & 0x200) && excluded_node != (void *)node) {
                func_80044A50(node);
                func_8003FFF0(node);
                if (!(node->field_1E & 0x80)) {
                    func_80040044(node);
                }
                if (excluded_node != 0) {
                    node = func_8003FD64(flags, excluded_node);
                } else {
                    node = func_8003FC64(flags);
                }
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
