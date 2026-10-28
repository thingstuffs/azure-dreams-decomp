#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/state.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"


#define FIELD32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define FIELDP(base, offset) (*(void **)((u8 *)(base) + (offset)))

/* Selects the parent handler and initializes state based on the indexed table value. */
void card_boot_begin_selected_slot_load(void *state)
{
    s32 enabled;
    void *parent;

    parent = (u8 *)state - 0x20;
    if (card_save_slot_metadata[FIELD32(state, 0x28)].words[0] != 0) {
        enabled = 1;
        FIELD32(state, 0x3C) = enabled;
        card_boot_show_loading_progress(parent, (u8 *)state + 0x40);
        FIELD32(state, 0x40) = enabled;
        FIELDP(state, -0x10) = card_boot_wait_before_loading_slot;
    } else {
        FIELDP(state, 0x34) = build_install;
        card_boot_show_no_saved_game_notice(parent);
        FIELDP(state, -0x10) = card_boot_poll_status_and_dismiss_dialog;
    }
}
