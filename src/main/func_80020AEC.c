#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408D74;

/* Processes the context using the four-entry table at D_80408D74. */
void func_80020AEC(M2C_UNK context) {
    func_80047358(context, &D_80408D74, 4);
}
