#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

extern s32 func_80069C08(s32 card_channel);




/* Processes state 2, returning 5 on reset or advancing to state 3. */
s32 card_boot_poll_state_two_transition(void)
{
    s32 status;

    status = 0;
    if ((*(s32 (*)[])(&card_operation_state))[0] == 2) {
        card_boot_drain_software_events();
        if (func_80069C08((*(s32 *)(&card_selected_channel_alias))) == 0) {
            (*(s32 (*)[])(&card_operation_state))[0] = 0;
            status = 5;
        } else {
            (*(s32 *)(&card_event_backend_mode)) = 0;
            (*(s32 (*)[])(&card_operation_state))[0]++;
        }
    }
    return status;
}
