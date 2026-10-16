#include "common.h"
#include "m2c_compat.h"

s32 townCreateObjectFromThreeValues();                     /* extern */
void townResetObjectEntryAndBrighten();       /* extern */

/* Prepare the context and forward the arguments to the next handler. */
void townPrepareAndForwardCallback(s32 object, s32 context, s32 callback_arg) {
    townCreateObjectFromThreeValues(context);
    townResetObjectEntryAndBrighten(object, context, callback_arg);
}
