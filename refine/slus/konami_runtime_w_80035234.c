#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80035164();     /* extern */
extern M2C_UNK D_80082A38;

/* Start a script in the global runtime with mode 1. */
void func_80035234(s32 script_addr) {
    func_80035164(&D_80082A38, script_addr, 1);
}
