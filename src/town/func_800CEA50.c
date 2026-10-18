#include "common.h"
#include "m2c_compat.h"

void update_jump_motion();                     /* extern */

/* Update jump motion with an initial vertical velocity of -10. */
void set_initial_jump_velocity(M2C_UNK jump_state, M2C_UNK body, M2C_UNK context) {
    update_jump_motion(jump_state, body, context, -0xA);
}
