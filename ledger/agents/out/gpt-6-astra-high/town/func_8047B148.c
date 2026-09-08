#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019BB4[];
extern M2C_UNK D_80016550;

/* Returns the table entry indexed by the first value in D_80019BB4. */
s32 func_8047B148(void) {
    return *(M2C_UNK *)((u8 *)&D_80016550 + ((*D_80019BB4) * 4));
}
