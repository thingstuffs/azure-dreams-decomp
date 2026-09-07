#include "common.h"

void func_8001941C(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 var_a2;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a2 != 0) {
        do {
            *var_a0 = *var_a1;
            var_a1++;
            var_a2--;
            var_a0++;
        } while (var_a2 != 0);
    }
}
