/* Selector 59, retail file [0x1990D44, 0x1990D98); complete callable clone. */
#include "common.h"

typedef struct LinkedMeshNode {
    u8 pad0[8];
    void *transform;
    void *object;
} LinkedMeshNode;

extern void func_8002406C(void *mesh, void *transform, void *object, s32 depth_bias);

/* Draw each linked mesh with zero depth bias; follow the node stored before its mesh. */
s32 func_80024544(void *initial_mesh, void *transform, void *object) {
    void *mesh = initial_mesh;
    void *node;

    for (;;) {
        func_8002406C(mesh, transform, object, 0);
        node = *((void **)mesh - 2);
        if (node == 0) {
            return 0;
        }
        mesh = (u8 *)node + 0x20;
        transform = ((LinkedMeshNode *)node)->transform;
        object = ((LinkedMeshNode *)node)->object;
    }
}
