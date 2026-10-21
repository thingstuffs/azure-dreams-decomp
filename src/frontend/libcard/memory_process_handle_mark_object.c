#include "common.h"

typedef struct { u8 pad[0x1E]; u16 flags; u8 pad20[0x20]; void *work; void *other; } Node;
extern void func_8007C040(void *, void *, s32);
extern void func_8007BEF0(s32);
extern u8 D_8040086C[], D_80400894[];
extern void func_80404DBC(void *);
extern void assert_card_slot_and_set_high_bit(void *);
extern s32 card_ui_dirty_flags;
/* Release the devkit node's two allocations and flag its completion. */
void memory_process_handles_and_mark_object(Node *node) {
    if (node == 0) {
        func_8007C040(D_8040086C, D_80400894, 0x183);
        func_8007BEF0(1);
    }
    func_80404DBC(node->work);
    assert_card_slot_and_set_high_bit(node->other);
    node->flags |= 0x8000;
    card_ui_dirty_flags |= 0x8000;
}
