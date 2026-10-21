#include "common.h"

extern void func_8007BEF0(s32 value);
extern void func_8007C040(void *ptr0, void *ptr1, s32 value);
extern void func_80404DBC(s32 value);
extern void assert_card_slot_and_set_high_bit(s32 value);

extern u8 D_8040086C[];
extern u8 D_80400894[];
extern s32 card_ui_dirty_flags[3];
extern s32 D_8008DAB0[4];

/* Processes the object's two handles and sets the object and global high-bit flags. */
void register_object_handles_and_flag(void *object) {
    u16 object_flags;
    s32 global_flags;

    if (object == 0) {
        func_8007C040(D_8040086C, D_80400894, 0x183);
        func_8007BEF0(1);
    }

    func_80404DBC(*(s32 *)((u8 *)object + 0x40));
    assert_card_slot_and_set_high_bit(*(s32 *)((u8 *)object + 0x44));

    object_flags = *(u16 *)((u8 *)object + 0x1E);
    global_flags = card_ui_dirty_flags[0];
    object_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)((u8 *)object + 0x1E) = object_flags;
    D_8008DAB0[1] = global_flags;
}
