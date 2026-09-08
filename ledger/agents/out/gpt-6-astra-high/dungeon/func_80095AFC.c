#include "common.h"

typedef struct Node Node;
typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Owner;

struct Node {
    u8 pad0[0x5C];
    Node *next;
    u8 pad60[0x28];
    s16 value;
};

extern s32 func_8009A350(s16, s16, s32, u16 *);
extern s32 func_800A41F0(Node *);

/* Finds an eligible node at the target coordinates with a value difference below 64. */
void *func_8009B25C(Node *node, s16 x, s16 y, s16 value) {
    u16 flags;
    Node *sentinel;
    Owner *owner;
    s32 value_gap;
    u16 target_x;
    s16 target_value;

    target_x = x;
    target_value = value;
    if ((s16)func_8009A350((s16)(x - 1), y, 0, &flags) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        return 0;
    }
    sentinel = node;
    node = (Node *)((u8 *)node->next + 0x20);
    while (node != sentinel) {
        owner = *(Owner **)((u8 *)node - 0x14);
        if (owner->x == target_x && owner->y == (u16)y) {
            value_gap = node->value - target_value;
            if (value_gap < 0) {
                value_gap = -value_gap;
            }
            if (value_gap < 0x40 && (func_800A41F0(node) << 16) != 0) {
                return node;
            }
        }
        node = (Node *)((u8 *)node->next + 0x20);
    }
    return 0;
}

