
struct ObjectNodeHeader;
/* Card boot stop timer and init server.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01041 - CL:main/func_80014C60.
 */
#include "frontend/libcard/card_boot_stop_timer_and_init_server_g01041.h"
#include "shared/object_flags.h"

/* Run setup callbacks and set the active flag. */
void card_boot_stop_timer_and_init_server(void) {
    close_timer_2_update_event();
    animation_tick_scale = 1;
    card_boot_init_server();
}

/* Process the entry's values and set its local and global status flags. */
void card_boot_destroy_card_chooser(Struct80014C90 *entry) {
    Struct80014C90 *entry_data = (Struct80014C90 *)((s8 *)entry + 0x20);

    set_object_cleanup_flag(entry_data->unk20);
    card_boot_mark_object_complete((struct ObjectNodeHeader *)entry_data->unk24);
    if (entry->unk20 == 2) {
        configure_shared_fade_primitive();
    }
    entry->unk1E |= 0x8000;
    D_800814A0 |= OBJECT_REMOVE_PENDING;
}

/* Run setup and dispatch the request in mode 1. */
void card_boot_open_save_slot_selection(s32 request) {
    card_boot_stop_timer_and_init_server();
    init_card_boot_request_object(request, 1);
}

/* Run the extra setup callback and dispatch the request in mode 2. */
void dispatch_request_mode_two(s32 request) {
    save_and_clear_entity_flag_ten();
    card_boot_stop_timer_and_init_server();
    init_card_boot_request_object(request, 2);
}

/* Set up the request with scale 512 and center (160, 120), then dispatch in mode 0. */
void dispatch_menu_update_callback(s32 request) {
    card_boot_stop_timer_and_init_server();
    g_game_work.view.projection_distance = 0x200;
    SetGeomScreen(0x200);
    SetGeomOffset(0xA0, 0x78);
    init_card_boot_request_object(request, 0);
}
