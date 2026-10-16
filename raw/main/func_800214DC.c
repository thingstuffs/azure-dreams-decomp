#include "common.h"

typedef struct { u8 pad[0x1E]; u16 flags; u8 pad20[0x20]; void *work; void *other; } Node;
extern void func_8007C040(void *, void *, s32);
extern void func_8007BEF0(s32);
extern u8 D_8040086C[], D_80400894[];
extern void func_80404DBC(void *);
extern void func_804077D4(void *);
extern s32 D_8008DAB4;
/* Release the devkit node's two allocations and flag its completion. */
void func_804084DC(Node *node) {
    if (node == 0) {
        func_8007C040(D_8040086C, D_80400894, 0x183);
        func_8007BEF0(1);
    }
    func_80404DBC(node->work);
    func_804077D4(node->other);
    node->flags |= 0x8000;
    D_8008DAB4 |= 0x8000;
}
