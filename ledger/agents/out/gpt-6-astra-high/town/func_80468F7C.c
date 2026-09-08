#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_80017B90;

/* Passes the global pointer D_80017B90 by reference to func_80019E7C. */
void func_80019F7C(void) {
    func_80019E7C(&D_80017B90);
}
