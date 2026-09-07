#include "common.h"

typedef struct S_8001EAA4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8001EAA4_0;   /* group_saved + ((var_a1 + var_a2) * 4) in func_8001EAA4 */

typedef struct S_8001EAA4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8001EAA4_1;   /* temp_a3 in func_8001EAA4 */



extern s32 func_800A6D30(void);
extern s32 D_80012090[];
extern s16 D_8001F6F8[];
extern u8 D_80073414[];

s32 func_8001EAA4(s8 *arg0, s8 *arg1) {
    s32 var_a2;
    s32 temp_v1_2;
    s32 var_a1;
    u8 *var_a3;
    s32 var_t0;
    s32 var_v0;
    register u16 *var_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u16 temp_v1;
    register s32 var_t1 ASM_REG("$9");   /* MATCH pin: retail register colouring depends on it */
    s32 result_index;
    u32 rng_result;
    register u32 temp_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    unsigned long var_t2;
    register u8 *group_saved ASM_REG("$11");   /* MATCH pin: retail register colouring depends on it */
    register u8 *temp_a3 ASM_REG("$13");   /* MATCH pin: load-bearing for the whole function shape */

    rng_result = func_800A6D30();
    var_v1 = (u16 *)D_8001F6F8;
    temp_a0 = var_v1[19];
    temp_a0 = (rng_result & 0xFFFF) % temp_a0;
    var_a2 = 1;
    var_a3 = (u8 *)var_v1;
    var_v1 = (u16 *)(var_a3 + 2);
    var_a1 = temp_a0 & 0xFFFF;
loop_1:
    var_t0 = 1;
    if (*var_v1 < (u32)var_a1) {
        var_a2 += 1;
        var_v1 += 1;
        if (var_a2 >= 0x13) {
            ASM_UNDEF(var_t0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            var_t0 = 1;
        } else {
            goto loop_1;
        }
    }
    var_a1 = var_a2 * 4;
    var_v1 = &((u16 *)var_a3)[var_a2];
    var_t2 = (unsigned long)D_80073414;
    var_v0 = var_a1 + var_a2;
    var_v0 *= 4;
    var_a3 = (u8 *)(var_v0 + var_t2);
    var_t1 = var_v1[-1];
    var_v0 = var_a3[2];
    if (var_t0 < var_v0) {
        var_v0 = var_a2 << 16;
        group_saved = (u8 *)var_t2;
        var_t2 = 2;
        temp_a3 = var_a3;
        ASM_KEEP_NV(temp_a3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        result_index = var_v0 >> 16;
        var_a3 = (u8 *)0x14;
loop_6:
        temp_v1 = *(u16 *)(var_a3 + ((S_8001EAA4_0 *)(group_saved + ((var_a1 + var_a2) * 4)))->unk_0C);
        if (!(temp_v1 & 0x10)) {
            if (temp_v1 & 0x40) {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                var_a1 = var_a2 * 4;
                if (D_80012090[0] != (s32)var_t2) {
                    goto block_19;
                }
            }
            {
                var_v0 = *(u16 *)(var_a3 + ((S_8001EAA4_1 *)temp_a3)->unk_0C) & 0x3000;
                if (var_v0 < 0) {
                    var_v0 += 0xFFF;
                }
                temp_v1_2 = (var_v0 >> 0xC) & 3;
                var_a1 = 0x80;
                if (temp_v1_2 != 0) {
                    var_a1 = 0x55;
                    if (temp_v1_2 != 1) {
                        var_a1 = 1;
                        if (temp_v1_2 == (s32)var_t2) {
                            var_a1 = 0x20;
                        }
                    }
                }
                var_t1 += var_a1;
                if (temp_a0 < (u32)(var_t1 & 0xFFFF)) {
                    *arg0 = (s8)var_a2;
                    *arg1 = (s8)var_t0;
                    return result_index;
                }
                goto block_18;
            }
        }
block_18:
        var_a1 = var_a2 * 4;
block_19:
        var_v0 = group_saved[((var_a1 + var_a2) * 4) + 2];
        var_t0 += 1;
        var_a3 += 0x14;
        if (var_t0 >= var_v0) {
            *arg0 = 0;
            *arg1 = 0;
            return 0;
        }
        goto loop_6;
    }
    *arg0 = 0;
    *arg1 = 0;
    return 0;
}
