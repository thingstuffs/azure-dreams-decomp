#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D940_0 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} S_8009D940_0;   /* temp_t0 in func_8009D940 */

typedef struct S_8009D940_1 {
    s16 unk_00;
    s16 unk_02;
} S_8009D940_1;   /* arg0 in func_8009D940 */

typedef struct S_8009D940_2 {
    s16 unk_00;
    s16 unk_02;
} S_8009D940_2;   /* arg1 in func_8009D940 */

void func_8009D940(S_8009D940_1 *arg0, S_8009D940_2 *arg1, void **arg2, void **arg3) {
    s32 temp_a0;
    s32 temp_t1;
    void **var_a2;
    void **var_a3;
    S_8009D940_0 *temp_t0;

    var_a2 = arg2;
    var_a3 = arg3;
    if (*var_a2 != NULL) {
        do {
            temp_t0 = *var_a2;
            temp_t1 = temp_t0->unk_00 + temp_t0->unk_04;
            if (arg0->unk_00 >= temp_t1) {
                temp_a0 = temp_t0->unk_02 + temp_t0->unk_06;
                if ((arg0->unk_02 >= temp_a0) && ((temp_t1 + temp_t0->unk_08) >= arg1->unk_00) && ((temp_a0 + temp_t0->unk_0A) >= arg1->unk_02)) {
                    *var_a3 = temp_t0;
                    var_a3 = (void **)((s8 *)((void **)((s8 *)var_a3 + 4)));
                }
            }
            var_a2 = (void **)((s8 *)((void **)((s8 *)var_a2 + 4)));
        } while (*var_a2 != NULL);
    }
    *var_a3 = NULL;
}
