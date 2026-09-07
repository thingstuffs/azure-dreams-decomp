#include "common.h"

#include "common.h"

void func_8003AEA8(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 > 0) {
        do {
            *var_a0 = 0;
            var_a1 -= 1;
            var_a0 += 1;
        } while (var_a1 > 0);
    }
}
