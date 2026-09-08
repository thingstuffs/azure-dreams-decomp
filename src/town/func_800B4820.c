/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B1DCC_arg0.h"

s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
void func_800B1F10(s32 arg0, s32 arg1);
void func_800B1F48(s32 arg0, s32 arg1, s32 arg2);



typedef struct S_800B1F80_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B1F80_1;   /* temp_s0 in func_800B1F80 */

void func_800B1F80(s8 *arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_ret;
    s32 temp_s1;
    s32 temp_v0;
    S_800B1F80_1 *temp_s0;

    temp_s0 = arg0 + ((((Rec_func_800B1DCC_arg0 *)arg0)->unk_0C * 0x10) + 0x1C);
    temp_ret = func_80049E1C(temp_s0->unk_08, arg1, temp_s0->unk_0C);
    temp_v0 = temp_ret;
    if (temp_v0 >= temp_s0->unk_0C) {
        temp_s0->unk_08 = 0;
        return;
    }
    if (temp_v0 != temp_s0->unk_08) {
        temp_s0->unk_08 = temp_v0;
        temp_a1 = ((Rec_func_800B1DCC_arg0 *)arg0)->unk_0C;
        temp_s1 = temp_ret / 10;
        func_800B1F48(*((s32 *)((s8 *)arg0 + (temp_a1 * 4))), temp_a1, temp_v0);
        if (temp_s1 != temp_s0->unk_00) {
            temp_s0->unk_00 = temp_s1;
            temp_a1_2 = ((Rec_func_800B1DCC_arg0 *)arg0)->unk_0C;
            func_800B1F10(*((s32 *)((s8 *)arg0 + (temp_a1_2 * 4))), temp_a1_2);
        }
    }
}
