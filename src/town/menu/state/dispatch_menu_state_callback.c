#include "common.h"
#include "m2c_compat.h"
/* Node update callback: hands the body, position and sprite the active-node pass supplies to the
 * handler in the body's first word (initialize_randomized_motion_vector, which then installs
 * advance_motion_and_reset_appearance; both take all three). */
void dispatch_menu_state_callback(void *obj, void *position, void *sprite)
{
    void (**vtable)(void *, void *, void *);
    void (*handler)(void *, void *, void *);
    vtable = (void (**)(void *, void *, void *)) obj;
    handler = *vtable;
    handler(obj, position, sprite);
}
