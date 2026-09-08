#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CC070();                     /* extern */

/* Update jump motion with an initial vertical velocity of -10. */
void func_800CC1B0(M2C_UNK jump_state, M2C_UNK body, M2C_UNK context) {
    func_800CC070(jump_state, body, context, -0xA);
}
