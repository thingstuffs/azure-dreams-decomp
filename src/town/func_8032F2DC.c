#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80016000[];

typedef struct S_80019ADC_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80019ADC_0;   /* *(void **)D_80016000 in func_80019ADC */

typedef struct S_80019ADC_1 {
    u8 pad_00[0x29C];
    s32 unk_29C;
} S_80019ADC_1;   /* temp_v0 in func_80019ADC */

typedef struct S_80019ADC_2 {
    u8 unk_00;
    u8 unk_01;
} S_80019ADC_2;   /* temp_v1 in func_80019ADC */

s32 func_80019ADC(s32 arg0, s32 arg1) {
    s32 result;
    s32 var_a3;
    void **var_a2;
    void *temp_v0;
    S_80019ADC_2 *temp_v1;

    result = -1;
    do { temp_v0 = ((S_80019ADC_0 *)(*(void **)D_80016000))->unk_38; } while (0);
    var_a2 = temp_v0 + 0x29C;
    var_a3 = 0;
    if (((S_80019ADC_1 *)temp_v0)->unk_29C != 0) {
loop_1:
        do { temp_v1 = *var_a2; } while (0);
        if ((temp_v1->unk_01 == arg0) &&
            (temp_v1->unk_00 == arg1)) {
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
