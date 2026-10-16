#include "common.h"
#include "m2c_compat.h"
/* Call the object's first virtual method. */
void townInvokeObjectFirstCallback(void *obj)
{
    (*((s32 (**)(void *)) obj))(obj);
}
