#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AEF8_1 {
    M2C_UNK (*unk_00)(s32, s32, s32, s32);
} S_8003AEF8_1;   /* var_v0 in func_8003AEF8 */


typedef struct S_8003AEF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    void * unk_14;
} S_8003AEF8_0;   /* var_v0 in func_8003AEF8 */


void func_8003AEF8(void *arg0) {
    M2C_UNK (*temp_v1)(s32, s32, s32, s32);
    void *temp_s0;
    S_8003AEF8_0 *var_v0;

    var_v0 = arg0;
    if (var_v0 != NULL) {
        do {
            temp_s0 = var_v0->unk_14;
            temp_v1 = ((S_8003AEF8_1 *)var_v0)->unk_00;
            var_v0->unk_14 = NULL;
            if (temp_v1 != NULL) {
                temp_v1(var_v0->unk_04, var_v0->unk_08, var_v0->unk_0C, var_v0->unk_10);
            }
            var_v0 = temp_s0;
        } while (var_v0 != NULL);
    }
}
