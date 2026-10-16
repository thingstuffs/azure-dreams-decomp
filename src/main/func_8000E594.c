#include "modules/main_server_ship.h"
#include "common.h"










/* Dispatches a nonzero handler result through the current mode's callback table. */
s32 cardBootDispatchEventCallbacks(void)
{
    CallbackWork callback_sets;
    MainCallback *first_callbacks;
    s32 mode;
    s32 result;

    callback_sets.first = D_80020034;
    callback_sets.second = D_80020048;
    result = 0;
    mode = D_800287E0[0];
    first_callbacks = callback_sets.first.value;
    if (mode == 0) {
        result = cardBootPollSoftwareEvents();
        if (result != 0) {
            result = first_callbacks[result]();
        }
    } else if (mode == 1) {
        result = cardBootTakeHardwareStatus();
        if (result != 0) {
            result = (*(MainCallback *)((u8 *)first_callbacks + (result * 4) + 0x18))();
        }
    }
    return result;
}
