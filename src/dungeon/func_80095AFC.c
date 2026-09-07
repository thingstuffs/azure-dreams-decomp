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
extern void *func_8009B368(void);
extern s32 func_800A41F0(Node *);

void *func_8009B25C(Node *head, s16 x, s16 y, s16 value) {
    u16 flags;
    Node *end;
    Owner *owner;
    s32 delta;
    u16 target_x;
    s16 target_value;

    target_x = x;
    target_value = value;
    if ((s16)func_8009A350((s16)(x - 1), y, 0, &flags) == 0) {
        return 0;
    }
    if (!(flags & 0x3300)) {
        func_8009B368();
        return 0;
    }
    end = head;
    head = (Node *)((u8 *)head->next + 0x20);
    while (head != end) {
        owner = *(Owner **)((u8 *)head - 0x14);
        if (owner->x == target_x && owner->y == (u16)y) {
            delta = head->value - target_value;
            if (delta < 0) {
                delta = -delta;
            }
            if (delta < 0x40 && (func_800A41F0(head) << 16) != 0) {
                return head;
            }
        }
        head = (Node *)((u8 *)head->next + 0x20);
    }
    return 0;
}

/* MECHANISM: A 0x38 frame falls from the separate flags slot, mutable s0 cursor,
   and s1 sentinel. Narrow s16 x/y formals order the s2 save/copy before s5.
   Explicit dispatcher call + null return fills its tail slot; <<16 tests low16. */
