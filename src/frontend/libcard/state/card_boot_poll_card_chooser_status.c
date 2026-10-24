#include "common.h"
#include "shared/game_work.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/state.h"
#include "main/data.h"

/* Updates the selected callback or triggers a one-time action when no callback is selected. */
void card_boot_poll_card_chooser_status(void *state) {
    s32 callback_index;
    void *callback;

    if ((g_game_work.buttons != 0) && ((g_game_work.pressed_buttons) & 0x20)) {
        card_boot_toggle_channel();
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(void **)((u8 *)state - 0x10) = D_8002789C;
        return;
    }

    callback_index = card_boot_debounce_card_status_events();
    no_op_card_stub();
    if (callback_index != 0) {
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(s32 *)((u8 *)state + 0x30) = callback_index;
        callback = D_8002809C[callback_index];
        *(s32 *)((u8 *)state + 0x34) = callback_index;
        *(void **)((u8 *)state - 0x10) = callback;
        return;
    }

    if ((card_boot_get_operation_state() == 3) && (*(s32 *)((u8 *)state + 0x38) == 0)) {
        card_boot_show_please_wait_notice((u8 *)state - 0x20, (u8 *)state + 0x38);
        *(s32 *)((u8 *)state + 0x38) = 1;
    }
}
