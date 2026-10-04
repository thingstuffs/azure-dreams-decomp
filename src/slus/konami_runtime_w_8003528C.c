#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void func_80034F88();              /* extern */
extern u8 D_80082A38[];

/* Passes the value and the shared object to func_80034F88. */
void func_8003528C(s32 value) {
    func_80034F88(&D_80082A38, value);
}
