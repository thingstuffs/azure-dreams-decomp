#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Dispatches request 14 with parameter 2 for the parent and its status pointer. */
void func_80022F8C(M2C_UNK parent, M2C_UNK status) {
    func_80022D60(parent, 0xe, 2, status);
}
