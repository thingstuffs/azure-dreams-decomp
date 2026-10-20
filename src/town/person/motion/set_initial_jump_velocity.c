#include "common.h"

struct S_800CC070_0; struct S_800CC070_1; void update_jump_motion(struct S_800CC070_0 *, struct S_800CC070_1 *, s32, s16);                     /* extern */

/* Update jump motion with an initial vertical velocity of -10. */
void set_initial_jump_velocity(s32 jump_state, s32 body, s32 context) {
    update_jump_motion((struct S_800CC070_0 *)(jump_state), (struct S_800CC070_1 *)(body), context, -0xA);
}
