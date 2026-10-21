#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"






/* Returns the first slot (1-4) whose value passes func_8006A024, or zero. */
s32 card_boot_poll_software_events(void)
{
    s32 matching_slot = 0;

    if (func_8006A024(card_sw_done_event[0]) != 0) {
        matching_slot = 1;
    } else {
        if (func_8006A024(card_sw_error_event[0]) != 0) {
            matching_slot = 2;
        } else {
            if (func_8006A024(card_sw_timeout_event[0]) != 0) {
                matching_slot = 3;
            } else {
                if (func_8006A024(card_sw_new_event[0]) != 0) {
                    matching_slot = 4;
                }
            }
        }
    }
    return matching_slot;
}
