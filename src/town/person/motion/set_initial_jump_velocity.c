#include "common.h"

#include "town/person/jump_motion.h"

/* Update jump motion with an initial vertical velocity of -10. */
void set_initial_jump_velocity(struct S_800CC070_0 *jump_state, struct S_800CC070_1 *body, void *context) {
    update_jump_motion(jump_state, body, context, -0xA);
}
