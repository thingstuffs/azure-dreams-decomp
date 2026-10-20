#include "common.h"

extern void func_8007BEF0(s32 value) __attribute__((noreturn));
extern void func_8007C040(void *ptr, void *ptr2, s32 value);
extern void update_two_slots_using_selection_mapping(s32 slot_state_addr);

extern s32 D_804007A4[];
extern s32 D_804007CC[];

/* Assert a valid card slot, store its value, and process its embedded state. */
void card_dev_set_slot_value_checked(s32 slot_addr, s32 slot_value) {
    s32 slot_state_addr;

    slot_state_addr = slot_addr + 0x20;
    if (slot_addr == 0) {
        func_8007C040(D_804007A4, D_804007CC, 0x153);
        func_8007BEF0(1);
    }
    *(s32 *)(slot_addr + 0x44) = slot_value;
    update_two_slots_using_selection_mapping(slot_state_addr);
}
