#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80035164();     /* extern */
extern M2C_UNK D_80082A38;

/* Set the global runtime's script address using mode zero. */
void func_80035260(s32 script_addr) {
    func_80035164(&D_80082A38, script_addr, 0);
}
