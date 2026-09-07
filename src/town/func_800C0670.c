/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083160[];

typedef struct S_800BDDD0_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    s16 unk_1A;
} S_800BDDD0_0;   /* temp_t3 in func_800BDDD0 */

void func_800BDDD0(s32 arg0, s16 arg1) {
    s16 temp_a0;
    s32 var_a3;
    s32 var_t0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 raw_arg0;
    s32 outer_limit;
    u8 *base;
    u8 *temp_t3;
    s32 temp_t4;

    var_t0 = (s16)arg0;
    base = D_80083160;
    temp_t3 = base + 0x1DC;
    temp_t4 = *(s32 *)(base + 0x1DC);
    raw_arg0 = arg0;
    temp_v1 = var_t0 + 4;
    if (var_t0 < temp_v1) {
        do {
            var_a3 = arg1;
            outer_limit = temp_v1;
            while (var_a3 < (arg1 + 4)) {
                temp_a0 = (var_t0 - raw_arg0) + 1;
                temp_a0 += (var_a3 - arg1) * 4;
                ASM_KEEP(temp_a0);   /* MATCH pin: retail register colouring depends on it */
                temp_v1_2 = var_a3 & ((S_800BDDD0_0 *)temp_t3)->unk_1A;
                var_a3 += 1;
                *((s16 *) (((s32) (((((S_800BDDD0_0 *)temp_t3)->unk_18 & var_t0) + (temp_v1_2 << ((S_800BDDD0_0 *)temp_t3)->unk_14)) << 0x10) >> 0xF) + temp_t4)) = temp_a0;
            }
            var_t0 += 1;
        } while (var_t0 < outer_limit);
    }
}
