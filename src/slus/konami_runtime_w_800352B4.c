#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80034F9C();                   /* extern */
extern M2C_UNK D_80082A38;

/* Passes the global object D_80082A38 to func_80034F9C. */
void func_800352B4(void) {
    func_80034F9C(&D_80082A38);
}
