#include "modules/main_server_ship.h"
#include "common.h"



/* Wait for both card operations, set the mode flag, and apply the current card state. */
void cardBootSelectChannelMode(s32 mode_enabled, s32 *unused_repeat_counts)
{
    s32 *state_base;

    cardBootDrainSoftwareEvents();
    _card_wait(0);
    _card_wait(1);

    state_base = (s32 *)0x80030000;
    if (mode_enabled != 0) {
        state_base[-0x1E0D] = 16;
    } else {
        state_base[-0x1E0D] = 0;
    }

    cardBootRequestInfo((*(s32 (*)[3])(&D_800287CC))[0]);
}
