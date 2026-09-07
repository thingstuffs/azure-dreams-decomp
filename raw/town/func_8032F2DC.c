#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80016000[];

s32 func_80019ADC(s32 arg0, s32 arg1) {
    s32 result;
    s32 var_a3;
    void **var_a2;
    void *temp_v0;
    void *temp_v1;

    result = -1;
    do { temp_v0 = M2C_FIELD(*(void **)D_80016000, void **, 0x38); } while (0);
    var_a2 = temp_v0 + 0x29C;
    var_a3 = 0;
    if (M2C_FIELD(temp_v0, s32 *, 0x29C) != 0) {
loop_1:
        do { temp_v1 = *var_a2; } while (0);
        if ((M2C_FIELD(temp_v1, u8 *, 1) == arg0) &&
            (M2C_FIELD(temp_v1, u8 *, 0) == arg1)) {
            result = var_a3;
            goto done;
        }
        var_a2 = (void **)((s8 *)var_a2 + 4);
        var_a3 += 1;
        if (*var_a2 == 0) {
            goto done;
        }
        goto loop_1;
    }
done:
    return result;
}
