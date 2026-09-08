#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408C9C;

/* Pass the caller's context and fixed data to func_80047358. */
void func_8001CAA0(M2C_UNK context) {
    func_80047358(context, &D_80408C9C, 0x12);
}
