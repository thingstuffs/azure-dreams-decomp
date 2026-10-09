/* Selector 72, retail file [0x19DF834, 0x19DF888); complete callable clone. */
#include "common.h"

typedef struct LinkedMeshNode {
    u8 pad0[8];
    void *transform;
    void *object;
} LinkedMeshNode;

extern void func_80024BF4(void *mesh, void *transform, void *object, s32 depth_bias);

/* Draw each linked mesh with zero depth bias; follow the node stored before its mesh. */
s32 func_80025034(void *initial_mesh, void *transform, void *object) {
    void *mesh = initial_mesh;
    void *node;

    for (;;) {
        func_80024BF4(mesh, transform, object, 0);
        node = *((void **)mesh - 2);
        if (node == 0) {
            return 0;
        }
        mesh = (u8 *)node + 0x20;
        transform = ((LinkedMeshNode *)node)->transform;
        object = ((LinkedMeshNode *)node)->object;
    }
}
