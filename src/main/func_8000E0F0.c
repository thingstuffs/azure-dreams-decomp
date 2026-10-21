#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"






extern s32 func_80069C18(s32 slot_index);
extern s32 func_80069C08(s32 selected_slot);

/* Advance the selected entry through its completion states and return its status. */
s32 card_advance_selected_operation(void)
{
    u32 state;
    s32 result;

    state = (*(s32 *)(&card_operation_state));
    result = 0;
    if (state != 0) {
        switch (state) {
        case 1:
            {
                s32 *completion_flag;

                completion_flag = &(*(s32 (*)[])(&card_slot_completion_flags))[0];
                if ((*(s32 *)(&card_selected_channel_alias)) != 0) {
                    completion_flag = &(*(s32 (*)[])(&card_slot_completion_flags))[1];
                }
                if (*completion_flag != 0) {
                    result = 1;
                    (*(s32 *)(&card_operation_state)) = 0;
                } else if ((func_80069C18(0) & 1) != 0 ||
                           (func_80069C18(1) & 1) != 0) {
                    card_boot_drain_software_events();
                    do {
                        state = func_80069C08((*(s32 *)(&card_selected_channel_alias)));
                    } while (state == 0);
                    (*(s32 *)(&card_event_backend_mode)) = 0;
                    (*(s32 *)(&card_operation_state)) = 3;
                }
                return result;
            }
        case 2:
            break;
        case 3:
            {
                s32 *completion_flag;

                completion_flag = &(*(s32 (*)[])(&card_slot_completion_flags))[0];
                if ((*(s32 *)(&card_selected_channel_alias)) != 0) {
                    completion_flag = &(*(s32 (*)[])(&card_slot_completion_flags))[1];
                }
                result = 2;
                *completion_flag = 1;
                (*(s32 *)(&card_operation_state)) = 0;
            }
            break;
        default:
            result = 5;
            break;
        }
    }
    return result;
}
