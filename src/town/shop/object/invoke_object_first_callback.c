#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void invoke_object_first_callback(void *obj)
{
    (*((s32 (**)(void *)) obj))(obj);
}
