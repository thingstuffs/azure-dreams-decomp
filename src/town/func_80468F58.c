#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_80017B90;

/* Passes the address of D_80017B90 to func_80019DE0. */
void func_80019F58(void) {
    func_80019DE0(&D_80017B90);
}
