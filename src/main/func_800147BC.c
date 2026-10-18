#include "common.h"
#include "shared/game_work.h"

extern void card_boot_toggle_channel(void);
extern s32 card_boot_get_operation_state(void);
extern s32 card_boot_debounce_card_status_events(void);
extern void func_80021904(void);
extern void card_boot_show_please_wait_notice(void *input, void *value);

extern u8 D_8002789C[];
extern void *D_8002809C[];

/* Updates the selected callback or triggers a one-time action when no callback is selected. */
void card_boot_poll_card_chooser_status(void *state) {
    s32 callback_index;
    void *callback;

    if ((g_game_work.buttons != 0) && (((s32)g_game_work.unk_010) & 0x20)) {
        card_boot_toggle_channel();
        *(s32 *)((u8 *)state + 0x38) = 0;
        *(void **)((u8 *)state - 0x10) = D_8002789C;
        return;
    }

    callback_index = card_boot_debounce_card_status_events();
    func_80021904();
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
