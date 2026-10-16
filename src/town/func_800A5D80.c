#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void townDispatchMenuStateCallback(void *obj)
{
    s32 (**vtable)(void *);
    s32 (*handler)(void *);
    vtable = (s32 (**)(void *)) obj;
    handler = *vtable;
    handler(obj);
}
