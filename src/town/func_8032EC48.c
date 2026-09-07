#include "common.h"

u8 *func_80019448(u8 *arg0, u8 *arg1) {
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_v1 = var_a0;
    if (*var_a1 != 0) {
        do {
            do { *var_a0 = *var_a1; } while (0);
            var_a1 += 1;
            var_a0 += 1;
        } while (*var_a1 != 0);
    }
    *var_a0 = 0;
    return temp_v1;
}
