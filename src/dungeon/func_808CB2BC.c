#include "common.h"
#include "m2c_compat.h"

typedef struct S_80123754_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123754_0;   /* *var_a0 in func_80123754 */

typedef struct S_80123754_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80123754_1;   /* ((S_80123754_0 *)(*var_a0))->unk_08 in func_80123754 */

extern s32 D_80126A88;
extern M2C_UNK D_80129728;

void func_80123754(void) {
    s8 *var_a1;
    s32 temp_v0;
    s32 *temp_v1;
    s32 var_a2;
    s8 *var_v0;
    void **var_a0;

    var_a2 = 0;
    var_v0 = (s8 *)&D_80129728;
    var_a0 = (void **)(var_v0 + 0x38);
    var_a1 = (s8 *)&D_80126A88;
    do {
        temp_v1 = *(s32 **)var_a0;
        temp_v0 = *(s32 *)var_a1;
        var_a1 += 8;
        *temp_v1 = temp_v0;
        var_a2 += 1;
        ((S_80123754_1 *)(((S_80123754_0 *)(*var_a0))->unk_08))->unk_02 = 0;
        var_a0 = (void **)((s8 *)((void **)((s8 *)var_a0 + 4)));
    } while (var_a2 < 0xE);
}
