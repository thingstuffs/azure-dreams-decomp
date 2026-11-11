#include "common.h"
#include "frontend/card/slot_assert_words.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"





/* Asserts a valid card slot and sets its local and global status flags. */
void card_dev_flag_slot_dirty(s32 card_slot) {
    u16 slot_flags;
    s32 global_flags;
    if (card_slot == 0) {
        func_8007C040(card_slot_assert_format, card_slot_filename, 0x14B);
        func_8007BEF0(1);
    }
    slot_flags = *(u16 *)(card_slot + 0x1E);
    global_flags = card_ui_dirty_flags;
    slot_flags |= 0x8000;
    global_flags |= 0x8000;
    *(u16 *)(card_slot + 0x1E) = slot_flags;
    card_ui_dirty_flags = global_flags;
}
