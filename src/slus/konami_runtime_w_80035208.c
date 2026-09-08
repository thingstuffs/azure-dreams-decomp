#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80035164();     /* extern */
extern M2C_UNK D_80082A38;

/* Calls func_80035164 for D_80082A38 with the supplied value and mode 2. */
void func_80035208(s32 value) {
    func_80035164(&D_80082A38, value, 2);
}
