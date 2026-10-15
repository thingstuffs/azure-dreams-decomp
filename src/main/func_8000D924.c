#include "modules/main_server_ship.h"
#include "common.h"



/* Wait for both card operations, set the mode flag, and apply the current card state. */
void func_80020924(s32 mode_enabled, s32 *unused_repeat_counts)
{
    s32 *state_base;

    func_800214A4();
    _card_wait(0);
    _card_wait(1);

    state_base = (s32 *)0x80030000;
    if (mode_enabled != 0) {
        state_base[-0x1E0D] = 16;
    } else {
        state_base[-0x1E0D] = 0;
    }

    func_800213C4((*(s32 (*)[3])(&D_800287CC))[0]);
}
