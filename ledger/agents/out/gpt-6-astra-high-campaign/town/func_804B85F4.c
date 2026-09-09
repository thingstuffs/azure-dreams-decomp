#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80017BA0(s32, s32);                            /* extern */
extern M2C_UNK D_800194E8;

/* Call func_80017BA0, then return the address of D_800194E8. */
M2C_UNK *func_80016DF4(s32 first_input, s32 second_input) {
    func_80017BA0(first_input, second_input);
    return &D_800194E8;
}
