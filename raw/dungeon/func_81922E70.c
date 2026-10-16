#include "common.h"
typedef struct GapNode { u8 pad[8]; void *position; void *appearance; } GapNode;
extern void func_80024198(void *, void *, void *, s32);
/* Apply the renderer to each node in the linked object chain. */
s32 func_80024670(void *state, void *position, void *appearance) {
    GapNode *node;
    for (;;) {
        func_80024198(state, position, appearance, 0);
        node = *(GapNode **)((u8 *)state - 8);
        state = (u8 *)node + 0x20;
        if (node == 0) break;
        position = node->position;
        appearance = node->appearance;
    }
    return 0;
}
