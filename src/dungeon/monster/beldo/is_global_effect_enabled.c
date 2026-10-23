#include "common.h"
#include "shared/sys_flags.h"


/* Returns whether system_update_flags has bit 0x10 set. */
s32 is_global_effect_enabled(void) {
    if (system_update_flags & 0x10) {
        return 1;
    }
    return 0;
}
