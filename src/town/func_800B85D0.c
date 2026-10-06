#include "shared/runtime_dispatch.h"
#include "common.h"

/* D_80082E6A: standalone byte global, declared >8B to force %hi/%lo
 * addressing (matches src/w_80047694.c sibling; same symbol, same form). */

/* D_800D1790: declared >8B so a plain value load also uses %hi/%lo. */
extern s32 D_800D1790[2];

extern s32 func_800A652C(void);

/* Returns the global in mode 1, otherwise calls the default handler. */
s32 func_800B5D30(void) {
    if (D_80082E60.mode != 1) {
        return func_800A652C();
    }
    return D_800D1790[0];
}
