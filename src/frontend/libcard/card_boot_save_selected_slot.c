#include "shared/object_node.h"
#include "shared/game_state.h"
#include "shared/audio_commands.h"
#include "common.h"
#include "frontend/libcard/message.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "slus.h"

extern void *card_boot_recheck_selected_channel(void);
void configure_shared_fade_primitive(void);


/* Processes the current selection and stores the next state. */
void *card_boot_save_selected_slot(CardSaveMenuBody *menu) {
    void *result;

    card_boot_prepare_save_buffer(0x80010000, menu->selection, menu->mode);
    if (card_boot_write_save_via_temporary_path(menu->selection, 0x80010000) == 0) {
        menu->saved_callback = card_boot_update_save_slot_menu_input;
        card_boot_show_overwrite_failure_notice(NODE_HEADER(menu));
        NODE_HEADER(menu)->update_callback = D_800261C0;
    } else {
        card_boot_set_slot_details_selection(menu->surface, menu->selection, 3);
        card_boot_refresh_five_slot_objects(menu);
        card_boot_set_slot_selection_marker(menu->slots[menu->selection], 1);
        if (GAME_STATE->dungeon_save_marker != 0) {
            configure_shared_fade_primitive();
            NODE_HEADER(menu)->update_callback = release_card_records_and_request_scene_state_three;
        } else {
            SD_Call(AUDIO_MENU_CONFIRM);
            NODE_HEADER(menu)->update_callback = card_boot_update_save_slot_menu_input;
        }
    }
    result = card_boot_recheck_selected_channel();
    menu->unk_40 = 0;
    return result;
}
