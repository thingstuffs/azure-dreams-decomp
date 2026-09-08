#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408CE8;

/* Forwards the context with D_80408CE8 and the fixed value 7. */
void func_8001DB5C(M2C_UNK context) {
    func_80047358(context, &D_80408CE8, 7);
}
