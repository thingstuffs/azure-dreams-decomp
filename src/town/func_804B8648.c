#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80018CE8;
extern M2C_UNK *D_80018E50;

/* Set D_80018E50 to D_80018CE8 and return its address. */
s32 award_next_unearned_milestone(void) {
    D_80018E50 = &D_80018CE8;
    return (s32) &D_80018CE8;
}
