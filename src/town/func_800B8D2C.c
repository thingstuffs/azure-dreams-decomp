#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B648C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B648C_0;   /* arg0 in func_800B648C */

typedef struct S_800B648C_1 {
    u8 pad_00[0xC];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
} S_800B648C_1;   /* var_s1 in func_800B648C */


void *func_800B6464();                       /* extern */
s32 func_800B677C();                         /* extern */

void func_800B648C(S_800B648C_0 *arg0, M2C_UNK arg1) {
    S_800B648C_1 *var_s1;

    var_s1 = func_800B6464(arg1);
    arg0->unk_0C = var_s1;
    if (var_s1->unk_0C.s != 0) {
        do {
            var_s1 = var_s1->unk_0C.u;
        } while (var_s1->unk_0C.s != 0);
    }
    var_s1->unk_0C.s = func_800B677C(arg1);
}
