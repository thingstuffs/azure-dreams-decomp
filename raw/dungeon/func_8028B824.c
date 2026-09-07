#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_80016034[];
#if 0
void func_8001E944(void) __attribute__((noreturn));
#endif
s32 func_8001E944();
s32 func_800A6D30();

void func_8001E824(void *arg0) {
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
        &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18
    };
    register u8 *entity ASM_REG("$19") = arg0;
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s2 ASM_REG("$18");
    register s32 minus_128 ASM_REG("$2");
    s32 temp_v0_2;
    u8 temp_v0;

    var_s0 = 0;
    ASM_KEEP(var_s0);
    ASM_KEEP(entity);
    temp_v0 = FIELD(entity, u8, 1);
    var_s2 = var_s0;
    if ((u32)(temp_v0 - 1) >= 0x12U) {
        goto block_16;
    }
    (void)jt_keep;
    goto *D_80016034[(u32)(temp_v0 - 1)];
jt_c4:
    var_s2 = 1;
    if (FIELD(entity, u8, 0) != 0x11) {
        var_s2 = (func_800A6D30() & 7) | 4;
    }
    var_s0 = -0x80;
    func_8001E944();
jt_c15:
    if (FIELD(entity, u8, 0) != 9) {
        goto block_8;
    }
    var_s0 |= 0x40;
jt_c17:
block_8:
    if (func_800A6D30() & 3) {
        goto block_12;
    }
    temp_v0_2 = (func_800A6D30() & 3) - 1;
    var_s2 = temp_v0_2;
    if (temp_v0_2 >= 0) {
        goto block_11;
    }
    var_s0 |= 0x40;
jt_c16:
block_11:
block_12:
    minus_128 = -0x80;
    ASM_KEEP(minus_128);
    var_s1 = var_s0 | minus_128;
    ASM_KEEP(var_s1);
    var_s0 = var_s1;
    if (func_800A6D30() & 7) {
        goto block_16;
    }
    var_s2 = -1;
    ASM_KEEP(var_s2);
    var_s0 = var_s1 | 0x40;
    func_8001E944();
jt_c18:
    var_s2 = ((u32)(func_800A6D30() & 0xFFFF) % 40U) + 0x3C;
jt_c1:
jt_c2:
jt_c3:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
block_16:
    FIELD(entity, s8, 2) = var_s2;
    FIELD(entity, s8, 3) = var_s0;
}
