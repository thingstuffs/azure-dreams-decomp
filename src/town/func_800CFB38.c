#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CD158();                     /* extern */

/* Forward three inputs to func_800CD158 with a fixed fourth argument of -10. */
void func_800CD298(M2C_UNK input_first, M2C_UNK input_second, M2C_UNK input_third) {
    func_800CD158(input_first, input_second, input_third, -0xA);
}
