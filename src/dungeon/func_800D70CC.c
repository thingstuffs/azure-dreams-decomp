#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DC82C_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
    u8 pad_3C[0x18];
    s32 unk_54;
    u8 pad_58[0x4];
    union { s32 s; volatile s32 u; } unk_5C;   /* accessed as both */
} S_800DC82C_0;   /* arg0 in func_800DC82C */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_800DC82C(S_800DC82C_0 *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    arg0->unk_5C.s = 0;
    temp_v0 = *arg0->unk_38;
    temp_v1 = 1;
    if (temp_v0 == 0) {
        temp_v0 = arg0->unk_54;
        temp_v0 |= 3;
        goto label_880;
    }
    if (temp_v0 == temp_v1) {
        temp_v0 = arg0->unk_54;
        temp_v1 = -3;
        temp_v0 |= 1;
        goto label_87C;
    }
    temp_v0 = arg0->unk_54;
    arg0->unk_5C.u = temp_v1;
    temp_v1 = -2;
    temp_v0 &= temp_v1;
    temp_v1 = -3;
label_87C:
    temp_v0 &= temp_v1;
label_880:
    arg0->unk_54 = temp_v0;
}
