#include "common.h"
#include "frontend/card.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/server_aliases.h"

extern void assert_card_slot_and_set_high_bit(s32 value);

extern const char D_8040086C[];
extern const char D_80400894[];
extern s32 D_8008DAB0[4];

/* Processes the object's two handles and sets the object and global high-bit flags. */
void mark_card_dev_object_handles_dirty(void *object) {
    u16 object_flags;
    s32 global_flags;

    if (object == 0) {
        printf_8007C040(D_8040086C, D_80400894, 0x183);
        exit_8007BEF0(1);
    }

    card_dev_flag_object_dirty(*(void **)((u8 *)object + 0x40));
    assert_card_slot_and_set_high_bit(*(s32 *)((u8 *)object + 0x44));

    object_flags = *(u16 *)((u8 *)object + 0x1E);
    global_flags = card_ui_dirty_flags;
    object_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)((u8 *)object + 0x1E) = object_flags;
    D_8008DAB0[1] = global_flags;
}
