#include "common.h"

void update_two_slots_using_selection_mapping(s32 slot_addr);
void card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected(s32 state, void *enabled, void *selected);
void initialize_child(s32);
void initialize_two_positioned_object_entries(s32 slot_addr);


extern u8 D_80408D54[];
extern u8 D_80408D5C[];

/* Run the slot setup sequence with the two shared data tables. */
void func_80020558(s32 slot_addr) {
    initialize_child(slot_addr);
    initialize_two_positioned_object_entries(slot_addr);
    card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected(slot_addr, D_80408D54, D_80408D5C);
    update_two_slots_using_selection_mapping(slot_addr);
}
