#include "common.h"

s32 service_script_controller(void);        /* extern */
extern s32 (*D_800FE5D8)(s32, s32, s32);

void dispatch_deferred_callback(s32 callback_first_value, s32 callback_second_value, s32 callback_third_value, s32 unused_value) {
    if (service_script_controller() == 0) {
        s32 (*callback)(s32, s32, s32) = D_800FE5D8;
                /* MATCH: Keep the callback load before argument register setup. */
        callback(callback_first_value, callback_second_value, callback_third_value);
    }
}
