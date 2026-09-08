#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80096208();                         /* extern */
M2C_UNK func_800962B8(s32);                            /* extern */

/* Pass the input to func_800962B8, then func_80096208. */
void func_800961D8(s32 input_value) {
    func_800962B8(input_value);
    func_80096208(input_value);
}
