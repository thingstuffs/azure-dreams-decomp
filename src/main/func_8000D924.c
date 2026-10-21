#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"



/* Wait for both card operations, set the mode flag, and apply the current card state. */
void card_boot_select_channel_mode(s32 mode_enabled, s32 *unused_repeat_counts)
{
    s32 *state_base;

    card_boot_drain_software_events();
    _card_wait(0);
    _card_wait(1);

    state_base = (s32 *)0x80030000;
    if (mode_enabled != 0) {
        state_base[-0x1E0D] = 16;
    } else {
        state_base[-0x1E0D] = 0;
    }

    card_boot_request_info((*(s32 (*)[3])(&card_selected_channel_alias))[0]);
}
