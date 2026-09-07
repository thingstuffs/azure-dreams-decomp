#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B2164();                 /* extern */

typedef struct S_800B2190_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2190_0;   /* temp_a0 in func_800B2190 */

typedef struct S_800B2190_1 {
    s32 unk_00;
} S_800B2190_1;   /* *var_s0 in func_800B2190 */

typedef struct S_800B2190_2 {
    void * unk_00;
    void * unk_04;
} S_800B2190_2;   /* var_s0 in func_800B2190 */

void func_800B2190(s32 arg0, s32 arg1) {
    s32 temp_a1;
    void **var_s0;
    S_800B2190_0 *temp_a0;

    temp_a1 = arg1 * 4;
    var_s0 = arg0 + temp_a1;
    temp_a0 = *var_s0;
    if (temp_a0->unk_01 == 0x13) {
        func_800B2164(temp_a0, temp_a1);
    }
    ((S_800B2190_1 *)(*var_s0))->unk_00 = 0;
    if (*var_s0 != NULL) {
        do {
            ((S_800B2190_2 *)var_s0)->unk_00 = ((S_800B2190_2 *)var_s0)->unk_04;
            var_s0 = (void **)((s8 *)((void **)((s8 *)var_s0 + 4)));
        } while (*var_s0 != NULL);
    }
}
