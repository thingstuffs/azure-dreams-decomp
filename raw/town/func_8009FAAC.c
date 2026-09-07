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
s32 func_8009D404();
extern u16 D_80082D08[];

s32 func_8009D20C(void *arg0, void *arg1_)
{
    register void *arg1 ASM_REG("$17") = arg1_;
    register s32 var_v0 ASM_REG("$2");
    register s32 one ASM_REG("$3");
    s32 geom_result;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x98);
    if (temp_s0 != NULL) {
        if (!(M2C_FIELD(temp_s0, u8 *, 1) & 1)) {
            if (func_80033B2C(M2C_FIELD(temp_s0, s16 *, 2)) == 0) {
                register s32 delay_v0 ASM_REG("$2") = 1;
                KEEP_INPUT(delay_v0);
                return func_8009D404();
            }
            goto block_6;
        }
        temp_v0 = func_80033B2C(M2C_FIELD(temp_s0, s16 *, 2));
        one = 1;
        ASM_KEEP(one);
        if (temp_v0 == one) {
            var_v0 = 1;
        } else {
block_6:
            if (!(M2C_FIELD(temp_s0, u8 *, 1) & 0x10)) {
                goto block_7;
            }
            var_v0 = 0;
        }
        return var_v0;
    }
block_7:
    if (func_8008CC90((s16)(D_80082D08[0] - M2C_FIELD(arg1, u16 *, 2)), (s16)(D_80082D08[1] - M2C_FIELD(arg1, u16 *, 6)), (s16)(D_80082D08[4] - M2C_FIELD(arg1, u16 *, 2)), (s16)(D_80082D08[5] - M2C_FIELD(arg1, u16 *, 6)), (s32)(s16)(D_80082D08[8] - M2C_FIELD(arg1, u16 *, 2)), (s32)(s16)(D_80082D08[9] - M2C_FIELD(arg1, u16 *, 6)), (s32)(s16)(D_80082D08[0xC] - M2C_FIELD(arg1, u16 *, 2)), (s32)(s16)(D_80082D08[0xD] - M2C_FIELD(arg1, u16 *, 6))) != 0) {
        goto geom_zero;
    }
    geom_result = func_8008CC90((s16)(D_80082D08[0] - M2C_FIELD(arg0, u16 *, 0x84)), (s16)(D_80082D08[1] - M2C_FIELD(arg0, u16 *, 0x86)), (s16)(D_80082D08[4] - M2C_FIELD(arg0, u16 *, 0x84)), (s16)(D_80082D08[5] - M2C_FIELD(arg0, u16 *, 0x86)), (s32)(s16)(D_80082D08[8] - M2C_FIELD(arg0, u16 *, 0x84)), (s32)(s16)(D_80082D08[9] - M2C_FIELD(arg0, u16 *, 0x86)), (s32)(s16)(D_80082D08[0xC] - M2C_FIELD(arg0, u16 *, 0x84)), (s32)(s16)(D_80082D08[0xD] - M2C_FIELD(arg0, u16 *, 0x86)));
    var_v0 = 2;
    if (geom_result == 0) {
        goto geom_done;
    }
geom_zero:
    var_v0 = 0;
geom_done:
    ASM_KEEP(var_v0);
    return var_v0;
}
