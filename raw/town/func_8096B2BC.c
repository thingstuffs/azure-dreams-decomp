#include "common.h"

extern s32 D_80126A88[];
extern u8 D_80129728[];

void func_80123754(void) {
    void **var_a0;
    s32 *temp_v1;
    s32 temp_v0;
    s32 *var_a1;
    s32 var_a2;
    u8 *base_v0;

    var_a2 = 0;
    base_v0 = D_80129728;
    var_a0 = (void **)(base_v0 + 0x38);
    var_a1 = D_80126A88;
    do {
        temp_v1 = *var_a0;
        temp_v0 = *var_a1;
        var_a1 += 2;
        *temp_v1 = temp_v0;
        var_a2 += 1;
        *(s16 *)((u8 *)*(void **)((u8 *)*var_a0 + 8) + 2) = 0;
        var_a0 += 1;
    } while (var_a2 < 0xE);
}
