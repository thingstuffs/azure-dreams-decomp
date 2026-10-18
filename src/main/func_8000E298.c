#include "modules/main_server_ship.h"
#include "common.h"






extern s32 func_80069C18(s32 slot_selector);
extern s32 func_80069C38(s32 slot_selector);

/* Updates the operation state and returns its status, clearing the selected slot in state 3. */
s32 card_poll_selected_operation_state(void)
{
    s32 state;
    s32 status;

    state = (*(s32 *)(&D_800287C8));
    status = 0;
    if (state == 0) {
        return status;
    }
    if (state != 1) {
        if (state == 3) {
            goto state_three;
        }
        goto invalid_state;
    }
    card_boot_drain_hardware_events();
    if (func_80069C38((*(s32 *)(&D_800287CC))) != 0) {
        if ((func_80069C18((*(s32 *)(&D_800287CC)) != 0) & 4) != 0) {
            (*(s32 *)(&D_800287E0)) = state;
            (*(s32 *)(&D_800287C8))++;
            goto done;
        }
        status = 5;
        (*(s32 *)(&D_800287C8)) = 0;
        goto done;
    }
    status = 5;
    (*(s32 *)(&D_800287C8)) = 0;
    goto done;

state_three:
    {
        s32 *selected_slot;

        selected_slot = &(*(s32 (*)[])(&D_80084118))[0];
        if ((*(s32 *)(&D_800287CC)) != 0) {
            selected_slot = &(*(s32 (*)[])(&D_80084118))[1];
        }
        status = 3;
        *selected_slot = 0;
        (*(s32 *)(&D_800287C8)) = 0;
        goto done;
    }

invalid_state:
    status = 5;
done:
    return status;
}
