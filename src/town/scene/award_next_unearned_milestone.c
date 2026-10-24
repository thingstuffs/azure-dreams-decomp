#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80018CE8;
extern s32 *D_80018E50;

/* Set D_80018E50 to D_80018CE8 and return its address. */
void *award_next_unearned_milestone(s32 unused) {
    D_80018E50 = &D_80018CE8;
    return &D_80018CE8;
}
