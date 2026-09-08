#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Dispatch operation 0xe in mode 2 with the supplied context and payload. */
void func_8001C1E4(M2C_UNK context, M2C_UNK payload) {
    func_80402F84(context, 0xe, 2, payload);
}
