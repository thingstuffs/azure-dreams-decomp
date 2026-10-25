#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"
#include "main.h"
#include "main/data.h"

extern s32 card_boot_load_save_and_clear_marker(s32, s32, s32);
extern void no_op_card_hook(s32);

/* Select a state pointer from the operation result and clear the trailing word. */
void card_boot_load_selected_slot(s8 *state) {
    s32 *next_state;
    s32 result;
    s8 *owner;

    result = card_boot_load_save_and_clear_marker(*(s32 *)(state + 0x28), 0x80010000, 1);
    owner = state - 0x20;
    if (result == 0) {
        next_state = build_install;
        *(s32 **)(state + 0x34) = next_state;
        card_boot_show_load_failure_notice(owner);
        next_state = (s32 *)0x80020000;
        next_state = card_boot_restore_saved_selection_callback;
    } else {
        no_op_card_hook(0x80010000);
        next_state = &D_800251A4;
    }
    *(s32 **)(state - 0x10) = next_state;
    card_boot_recheck_selected_channel();
    *(s32 *)(state + 0x40) = 0;
}
