#include "common.h"
typedef struct GapNode { u8 pad[8]; void *position; void *appearance; } GapNode;
extern void func_8002404C(void *, void *, void *, s32);
/* Render each linked effect, using its appearance field as the draw parameter. */
s32 func_80024898(void *state, void *position, void *appearance) {
    GapNode *node;
    for (;;) {
        func_8002404C(state, position, appearance, *(s16 *)((u8 *)appearance + 6));
        node = *(GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
