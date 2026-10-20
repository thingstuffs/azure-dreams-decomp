#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void invoke_menu_motion_handler(void *obj)
{
    s32 (*handler)(void *);
    handler = *((s32 (**)(void *)) obj);
    handler(obj);
}
