#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800253A0(); /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8004B634();                            /* extern */

/* Prepares shared state and initializes an item in mode 1. */
void func_8004B660(s32 context, M2C_UNK user_data, M2C_UNK item) {
    func_8004B634();
    func_8003F320();
    func_800253A0(context, user_data, 1, item);
}
