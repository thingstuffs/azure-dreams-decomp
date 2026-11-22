#include "shared/object_node.h"
#include "shared/audio_commands.h"
#include "common.h"

#include "slus.h"
#include "town/shop.h"
#include "town/shop/object.h"
#include "town/system.h"

extern s32 check_entry_limit_or_combined_value(GridMenuObject *entry);

extern void *D_800D1558;
extern void *D_800D155C;

/* Handles the selected entry according to its type, flags, and availability. */
void confirm_selected_entry(GridMenuObject *state) {
    DungeonItemEntry *selected_entry;

    selected_entry = (DungeonItemEntry *)(state->selected_index * sizeof(*selected_entry) + (unsigned long)state->entry_base);
    if (selected_entry->kind != 0x16) {
        if (!(selected_entry->unk_03 & 0x80)) {
            if (check_entry_limit_or_combined_value(state) != 0) {
                SD_Call(AUDIO_MENU_CONFIRM);
                toggle_selected_entry_flag(state);
                apply_shop_object_slot_colors(state->subrecord);
                return;
            }
            SD_Call(0x506);
            submit_script_with_registered_context(D_800D1558);
            return;
        }
        SD_Call(0x506);
        if (state->field_18 == 1) {
            submit_script_with_registered_context(D_800D155C);
            return;
        }
    } else {
        close_twin_shop(NODE_HEADER(state));
        set_status_from_flagged_total(state);
    }
}
