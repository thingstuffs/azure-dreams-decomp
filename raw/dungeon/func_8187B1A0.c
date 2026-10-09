#include "common.h"

typedef struct LinkedMeshNode {
    u8 pad0[8];
    void *context;
    void *data;
} LinkedMeshNode;

extern void func_800241A8(void *mesh, void *transform, void *object, s32 depth_bias);

/* Draw each linked mesh with zero depth bias; follow the node stored before its state. */
s32 func_800249A0(void *initial_state, void *context, void *data) {
    void *state = initial_state;
    void *next_node;

    for (;;) {
        func_800241A8(state, context, data, 0);
        next_node = *((void **)state - 2);
        if (next_node == 0) {
            return 0;
        }
        state = (u8 *)next_node + 0x20;
        context = ((LinkedMeshNode *)next_node)->context;
        data = ((LinkedMeshNode *)next_node)->data;
    }
}
