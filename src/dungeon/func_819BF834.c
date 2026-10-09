/* Selector 72, retail file [0x19DF834, 0x19DF888); complete callable clone. */
#include "common.h"
#include "shared/object_node.h"

extern void func_80024BF4(void *mesh, void *transform, void *object, s32 depth_bias);

/* Draw each linked mesh with zero depth bias; follow the node stored before its mesh. */
s32 func_80025034(void *initial_mesh, void *transform, void *object) {
    void *mesh = initial_mesh;
    ObjectNodeHeader *node;

    for (;;) {
        func_80024BF4(mesh, transform, object, 0);
        /* the preceding header's +0x18 holds the next node */
        node = *(ObjectNodeHeader **)&((ObjectNodeHeader *)mesh - 1)->unk_18;
        if (node == 0) {
            return 0;
        }
        mesh = node + 1;
        transform = node->unk_08;
        object = node->unk_0C;
    }
}
