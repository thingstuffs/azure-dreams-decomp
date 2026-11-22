#include "common.h"
#include "m2c_compat.h"
#include "town/menu/state.h"
#include "town/menu/randomized_effect_motion_g00570.h"
/* Node update callback: hands the body, position and sprite the active-node pass supplies to the
 * handler in the body's first word (initialize_randomized_motion_vector, which then installs
 * advance_motion_and_reset_appearance; both take all three). */
void dispatch_menu_state_callback(RandomizedEffectMotionBody *body, ObjectPosition *position, SpriteFrameState *sprite)
{
    body->callback(body, position, sprite);
}
