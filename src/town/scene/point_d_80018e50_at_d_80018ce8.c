#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern M2C_UNK D_80018CE8;
extern s32 *D_80018E50;

/* Set D_80018E50 to D_80018CE8 and return its address. */
void *point_d_80018e50_at_d_80018ce8(s32 unused) {
    D_80018E50 = &D_80018CE8;
    return &D_80018CE8;
}
