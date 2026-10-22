#include "common.h"
#include "frontend/card/slot_assert_words.h"
#include "frontend/card.h"

extern void func_8007BEF0(s32 value) __attribute__((noreturn));
extern void func_8007C040(void *ptr, void *ptr2, s32 value);
extern void update_two_slots_using_selection_mapping(s32 slot_state_addr);




/* Assert a valid card slot, store its value, and process its embedded state. */
void card_dev_set_slot_value_checked(s32 slot_addr, s32 slot_value) {
    s32 slot_state_addr;

    slot_state_addr = slot_addr + 0x20;
    if (slot_addr == 0) {
        func_8007C040(card_slot_assert_format, card_slot_filename, 0x153);
        func_8007BEF0(1);
    }
    *(s32 *)(slot_addr + 0x44) = slot_value;
    update_two_slots_using_selection_mapping(slot_state_addr);
}
