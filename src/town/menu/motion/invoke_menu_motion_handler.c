#include "town/menu/motion.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void invoke_menu_motion_handler(void *obj, struct ObjectPosition *position, void *sprite)
{
    s32 (*handler)(void *, struct ObjectPosition *, void *);
    handler = *((s32 (**)(void *, struct ObjectPosition *, void *)) obj);
    handler(obj, position, sprite);
}
