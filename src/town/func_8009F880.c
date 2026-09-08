#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define KEEP_INPUT(value) ((void)0)
#else
#define KEEP_INPUT(value) __asm__ __volatile__("" : : "r"(value))
#endif

s32 func_80033B2C();
s32 func_8008CC90();
extern s16 D_8006ADD4;
extern u16 D_80082D08[];

typedef struct S_8009CFE0_0 {
    u8 pad_00[0x84];
    u16 unk_84;
    u16 unk_86;
    u8 pad_88[0x10];
    void * unk_98;
} S_8009CFE0_0;   /* arg0 in func_8009CFE0 */

typedef struct S_8009CFE0_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    s16 unk_02;
} S_8009CFE0_1;   /* temp_s0 in func_8009CFE0 */

typedef struct S_8009CFE0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8009CFE0_2;   /* arg1 in func_8009CFE0 */

s32 func_8009CFE0(S_8009CFE0_0 *arg0, void *arg1_)
{
    S_8009CFE0_2 *arg1 = arg1_;
    register s32 var_v0 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 one;
    s32 geom_result;
    s32 temp_v0;
    S_8009CFE0_1 *temp_s0;

    temp_s0 = arg0->unk_98;
    if (temp_s0 != NULL) {
        if (!(temp_s0->unk_01 & 1)) {
            if (func_80033B2C(temp_s0->unk_02) == 0) {
                register s32 delay_v0 ASM_REG("$2") = 1;   /* MATCH pin: keeps a constant in a register as retail does */
                KEEP_INPUT(delay_v0);
                return 1;
            }
            goto block_6;
        }
        temp_v0 = func_80033B2C(temp_s0->unk_02);
        one = 1;
        ASM_KEEP(one);   /* MATCH pin: load-bearing for the whole function shape */
        if (temp_v0 == one) {
            var_v0 = 1;
            goto return_value;
        }
block_6:
        if (temp_s0->unk_01 & 0x10) {
            var_v0 = 0;
            goto return_value;
        }
    } else {
        goto geometry;
    }
block_7:
    if (D_8006ADD4 == 0xC) {
        var_v0 = 0;
        goto return_value;
    }
geometry:
    if (func_8008CC90(
            (s16)(D_80082D08[0] - arg1->unk_02),
            (s16)(D_80082D08[1] - arg1->unk_06),
            (s16)(D_80082D08[4] - arg1->unk_02),
            (s16)(D_80082D08[5] - arg1->unk_06),
            (s32)(s16)(D_80082D08[8] - arg1->unk_02),
            (s32)(s16)(D_80082D08[9] - arg1->unk_06),
            (s32)(s16)(D_80082D08[0xC] - arg1->unk_02),
            (s32)(s16)(D_80082D08[0xD] - arg1->unk_06)) != 0) {
        goto geom_zero;
    }
    geom_result = func_8008CC90(
        (s16)(D_80082D08[0] - arg0->unk_84),
        (s16)(D_80082D08[1] - arg0->unk_86),
        (s16)(D_80082D08[4] - arg0->unk_84),
        (s16)(D_80082D08[5] - arg0->unk_86),
        (s32)(s16)(D_80082D08[8] - arg0->unk_84),
        (s32)(s16)(D_80082D08[9] - arg0->unk_86),
        (s32)(s16)(D_80082D08[0xC] - arg0->unk_84),
        (s32)(s16)(D_80082D08[0xD] - arg0->unk_86));
    var_v0 = 2;
    if (geom_result == 0) {
        goto return_value;
    }
geom_zero:
    var_v0 = 0;
return_value:
    return var_v0;
}
