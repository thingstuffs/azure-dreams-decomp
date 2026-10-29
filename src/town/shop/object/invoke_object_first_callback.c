#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"
/* Call the object's first virtual method. */
void invoke_object_first_callback(void *obj)
{
    (*((s32 (**)(void *)) obj))(obj);
}
