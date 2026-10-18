#include "common.h"

void update_jump_motion();                     /* extern */

/* Update jump motion with an initial vertical velocity of -10. */
void set_initial_jump_velocity(s32 jump_state, s32 body, s32 context) {
    update_jump_motion(jump_state, body, context, -0xA);
}
