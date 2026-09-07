#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_80016BDC(s16);                         /* extern */

typedef struct S_808B16A0_0 {
    s16 unk_00;
    s16 unk_02;
} S_808B16A0_0;   /* var_s0 in func_808B16A0 */

void func_808B16A0(void *arg0, s32 arg1) {
    char pad[8];
    s16 temp_a0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    if (arg1 > 0) {
        var_s0 = arg0;
        do {
            var_s1 += 1;
            func_80016BDC(((S_808B16A0_0 *)var_s0)->unk_00);
            temp_a0 = ((S_808B16A0_0 *)var_s0)->unk_02;
            var_s0 += 4;
            func_80016BDC(temp_a0);
        } while (var_s1 < arg1);
    }
}
