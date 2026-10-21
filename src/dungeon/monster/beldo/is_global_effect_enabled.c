#include "common.h"
#include "shared/sys_flags.h"


/* Returns whether bit 0x10 is set in D_80013714[0]. */
s32 is_global_effect_enabled(void) {
    if (system_update_flags & 0x10) {
        return 1;
    }
    return 0;
}
