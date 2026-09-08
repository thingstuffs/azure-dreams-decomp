#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Start operation 4 in mode 2 with the owner and status flag. */
void func_80022F14(M2C_UNK owner, M2C_UNK status_flag) {
    func_80022D60(owner, 4, 2, status_flag);
}
