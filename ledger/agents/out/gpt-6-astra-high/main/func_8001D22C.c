#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408CB8;

/* Calls func_80047358 with the supplied context, D_80408CB8, and 10. */
void func_8001D22C(M2C_UNK context) {
    func_80047358(context, &D_80408CB8, 0xa);
}
