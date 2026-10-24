#include "town/menu/motion.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void invoke_menu_motion_handler(void *obj, void *position, void *sprite)
{
    s32 (*handler)(void *, void *, void *);
    handler = *((s32 (**)(void *, void *, void *)) obj);
    handler(obj, position, sprite);
}
