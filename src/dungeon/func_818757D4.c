#include "common.h"

typedef struct LinkedRenderNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedRenderNode;

extern void func_80024758(void *state, void *position, void *material, u16 depth_bias);

/* Render the initial state and each linked node with zero depth bias. */
s32 func_80024FD4(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        func_80024758(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((LinkedRenderNode *)next_node)->context;
        data = ((LinkedRenderNode *)next_node)->data;
    }
}
