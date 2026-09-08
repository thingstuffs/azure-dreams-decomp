#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001E869;

/* Returns the address of D_8001E869 as an integer. */
s32 func_8001671C(void) {
    return (s32) &D_8001E869;
}
