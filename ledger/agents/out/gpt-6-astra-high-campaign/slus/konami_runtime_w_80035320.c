#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80035060();              /* extern */
extern M2C_UNK D_80082A38;

/* Passes the value to func_80035060 with the shared state. */
void func_80035320(s32 value) {
    func_80035060(&D_80082A38, value);
}
