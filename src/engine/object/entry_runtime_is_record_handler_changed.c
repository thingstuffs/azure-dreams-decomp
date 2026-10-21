#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

extern u8 runtime_dispatch_mode_alias[9];

/* Returns the check result in mode 2, otherwise whether the check or fallback status is nonzero. */
s32 test_runtime_handler_or_fallback_status(void *context) {
    s32 result;

    if (runtime_dispatch_mode_alias[0] != 2) {
        result = 0;
        if (runtime_is_record_handler_changed(context) != 0) {
            result = 1;
        } else {
            s16 *fallback_status = map_change_pending;
            if (*fallback_status != 0) {
                result = 1;
            }
        }
        return result;
    }

    return runtime_is_record_handler_changed(context);
}
