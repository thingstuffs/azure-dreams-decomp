#include "common.h"
#include "m2c_compat.h"

u8 *initCardMessageObject();   /* extern */

/* Dispatch operation 0xe in mode 2 with the supplied context and payload. */
void func_8001C1E4(M2C_UNK context, M2C_UNK payload) {
    initCardMessageObject(context, 0xe, 2, payload);
}
