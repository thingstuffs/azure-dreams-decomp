#include "common.h"
#include "m2c_compat.h"

void townUpdateJumpMotion();                     /* extern */

/* Update jump motion with an initial vertical velocity of -10. */
void townSetInitialJumpVelocity(M2C_UNK jump_state, M2C_UNK body, M2C_UNK context) {
    townUpdateJumpMotion(jump_state, body, context, -0xA);
}
