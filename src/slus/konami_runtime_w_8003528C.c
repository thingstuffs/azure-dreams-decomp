#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80034F88();              /* extern */
extern M2C_UNK D_80082A38;

/* Passes the value and the shared object to func_80034F88. */
void func_8003528C(s32 value) {
    func_80034F88(&D_80082A38, value);
}
