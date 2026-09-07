#include "common.h"

extern s32 func_80033BE4(void);
extern void func_80033C1C(s32, s32);
extern void func_80033C84(s32);
extern s32 func_8003FC64(s32);
extern void func_8003FFF0(s32);
extern void func_80040044(s32);
extern void func_8008B818(s32, s32, s32, s32);
extern s8 D_800CFC2C[11];
extern u8 D_800FC418;

s32 func_8008B654(s32 arg0, s32 arg1) {
    s32 sp10[12];
    s32 sp40[12];
    s32 *var_s1;
    s32 *var_s3;
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s2;
    register s32 var_v0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s8 *var_s0_2;
    s8 temp_v0_3;
    s8 *temp_v0_4;

    var_s2 = 0;
    var_s1 = sp10;
    var_s3 = sp40;
loop_1:
    temp_v0 = func_8003FC64(0x11);
    var_v0 = var_s2 < 0xB;
    if (temp_v0 != 0) {
        temp_v0_2 = func_80033BE4();
        ASM_KEEP_NV(temp_v0_2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        if ((temp_v0_2 == 0) || (func_80033C1C(temp_v0_2, 0), *var_s1 = temp_v0, var_s1 += 1, *var_s3 = temp_v0_2, ({ ASM_KEEP(temp_v0_2); 0; }), var_s2 += 1, var_s3 += 1, ((var_s2 < 0xB) == 0))) {
            var_v0 = var_s2 < 0xB;
        } else {
            goto loop_1;
        }
    }
    if (var_v0 != 0) {
        if (var_s1 != sp10) {
            var_s0 = sp10;
            do {
                var_s1 -= 1;
                func_8003FFF0(*var_s1);
                func_80040044(*var_s1);
            } while (var_s1 != var_s0);
        }
        if (var_s3 != sp40) {
            var_s0 = sp40;
            do {
                var_s3 -= 1;
                func_80033C84(*var_s3);
            } while (var_s3 != var_s0);
        }
        return 0;
    }
    var_s1 = sp10;
    var_s3 = sp40;
    var_s2 = hard_zero;
    var_s0_2 = D_800CFC2C;
    do {
    temp_v0_3 = *(s8 *)((u32)var_s2 + (u32)var_s0_2);
    if (temp_v0_3 == var_s2) {
        temp_a1 = 0;
    } else {
        temp_a1 = sp10[temp_v0_3] + 0x20;
    }
    temp_a0 = var_s2;
    var_s2 += 1;
    temp_v0_4 = (s8 *)(*var_s1 + 0x20);
    *(s32 *)(temp_v0_4 + 0x74) = 0;
    *(s32 *)(temp_v0_4 + 0x78) = arg1;
    *(s32 *)(temp_v0_4 + 0x7C) = arg0;
    temp_a2 = *var_s1;
    var_s1 += 1;
    temp_a3 = *var_s3;
    var_s3 += 1;
    func_8008B818(temp_a0, temp_a1, temp_a2, temp_a3);
    } while (var_s2 < 0xB);
    D_800FC418 = 0;
    return 1;
}
