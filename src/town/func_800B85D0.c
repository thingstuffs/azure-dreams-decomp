#include "shared/runtime_dispatch.h"
#include "common.h"

/* D_80082E6A: standalone byte global, declared >8B to force %hi/%lo
 * addressing (matches src/w_80047694.c sibling; same symbol, same form). */

/* D_800D1790: declared >8B so a plain value load also uses %hi/%lo. */
extern s32 D_800D1790[2];

extern s32 select_object_state_value(void);

/* Returns the global in mode 1, otherwise calls the default handler. */
s32 get_mode_specific_value(void) {
    if (D_80082E60.mode != 1) {
        return select_object_state_value();
    }
    return D_800D1790[0];
}
