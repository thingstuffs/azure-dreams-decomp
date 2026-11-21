#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Returns 1 through 4 for the first signaled card software event, or 0 if none is signaled. */
s32 card_devkit_poll_first_software_event(void) {
    s32 result;

    result = 0;
    if (TestEvent_8007C9C8(dev_card_sw_done_event) != 0) {
        result = 1;
    } else {
        if (TestEvent_8007C9C8(dev_card_sw_error_event) != 0) {
            result = 2;
        } else {
            if (TestEvent_8007C9C8(dev_card_sw_timeout_event) != 0) {
                result = 3;
            } else {
                if (TestEvent_8007C9C8(dev_card_sw_new_event) != 0) {
                    result = 4;
                }
            }
        }
    }
    return result;
}
