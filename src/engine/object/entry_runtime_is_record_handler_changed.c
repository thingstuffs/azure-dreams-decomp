#include "common.h"

#include "engine/object.h"
#include "slus/data.h"

extern u8 runtime_dispatch_mode_alias[9];

/* Returns the check result in mode 2, otherwise whether the check or fallback status is nonzero. */
s32 is_script_or_map_change_pending(void *context) {
    s32 result;

    if (runtime_dispatch_mode_alias[0] != 2) {
        result = 0;
        if (has_active_script_handler(context) != 0) {
            result = 1;
        } else {
            s16 *fallback_status = map_change_pending;
            if (*fallback_status != 0) {
                result = 1;
            }
        }
        return result;
    }

    return has_active_script_handler(context);
}
