#include "common.h"

typedef struct Node {
    u8 pad0[4];
    struct Node *next;
    s32 field8;
    s32 fieldC;
    u8 pad10[4];
    u8 type;
    u8 active;
    s16 angle;
} Node;

extern s32 func_8008FD9C();
extern s32 func_8008FE78();

/* Finds the first eligible active node in the circular list. */
Node *func_8008FE90(Node *origin) {
    s32 node_field_c;
    s32 node_field_8;
    s32 origin_field_8;
    s32 origin_field_c;
    Node *node;

    node = origin->next;
    origin_field_c = origin->fieldC;
    origin_field_8 = origin->field8;
    if (node != origin) {
        do {
            node_field_8 = node->field8;
            node_field_c = node->fieldC;
            if (node->active != 0) {
                if (((u32)(node->type - 2) >= 2U) ||
                    (func_8008FE78(node->angle, origin->angle) != 0)) {
                    if (func_8008FD9C(origin_field_c, origin_field_8, node_field_c, node_field_8) != 0) {
                        return node;
                    }
                }
            }
            node = node->next;
            if (node == origin) {
                break;
            }
        } while (1);
    }
    return 0;
}
