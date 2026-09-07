#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern s32 func_8008CFB4(s32 *);


typedef struct S_8008C4C8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C4C8_1;   /* temp_s0 in func_8008C4C8 */

s16 func_8008C4C8(Rec_func_8008ACDC_arg0 *arg0, s32 arg1, s32 arg2) {
    s32 sp[5];
    s32 temp_v0;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_v0_2;
    S_8008C4C8_1 *temp_s0;

    temp_a2 = arg2 * 0x10;
    temp_s0 = temp_a2 + arg1;
    sp[0] = arg0->unk_00 + temp_s0->unk_00;
    sp[1] = arg0->unk_04 + temp_s0->unk_04;
    sp[2] = arg0->unk_08 + temp_s0->unk_08;
    temp_v0 = func_8008CFB4(sp);
    if ((s16) temp_v0 == 0x7FFF) {
        return 0x7FFF;
    }
    temp_v1 = temp_s0->unk_00;
    var_v0_2 = temp_v1 >> 0x10;
    if (temp_v1 < 0) {
        temp_v1 += 0xFFFF;
        var_v0_2 = temp_v1 >> 0x10;
    }
    return temp_v0 - var_v0_2;
}
