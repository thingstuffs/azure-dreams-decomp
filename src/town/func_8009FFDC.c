#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D7D0();                         /* extern */

typedef struct S_8009D73C_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_8009D73C_0;   /* *var_s1 in func_8009D73C */

void func_8009D73C(void **arg0) {
    s32 *var_s0;
    s32 temp_a0;
    void **var_s1;

    var_s1 = arg0;
    if (*var_s1 != NULL) {
        do {
            var_s0 = ((S_8009D73C_0 *)(*var_s1))->unk_0C;
            if ((var_s0 != NULL) && (*var_s0 != 0)) {
                do {
                    temp_a0 = *var_s0;
        var_s0 += 1;
                    func_8009D7D0(temp_a0);
                } while (*var_s0 != 0);
            }
            var_s1 = (void **)((s8 *)((void **)((s8 *)var_s1 + 4)));
        } while (*var_s1 != NULL);
    }
}
