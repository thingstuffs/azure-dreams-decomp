#include "common.h"
#include "m2c_compat.h"

s32 func_80026F54();
s32 func_80026FA8();
void *func_80027110();
void func_800272F8(void) __attribute__((noreturn));
s32 func_8004B404();
M2C_UNK func_80069E88();
extern M2C_UNK D_800157C0;

s32 func_8002714C(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    register s32 tail_return ASM_REG("$2");   /* MATCH pin: retail delay-slot contents depend on it */

    var_s0 = arg1;
    var_s3 = arg2;
    var_s4 = arg3;
    var_s0 /= 72;
    ASM_USE_NV(var_s4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s6 = func_8004B404(0x91);
    if (var_s6 != 0) {
        var_s3 -= var_s0 * 8;
        if (var_s3 >= 9) {
            var_s3 = 8;
        }
        if (var_s0 == 0) {
            var_s1 = 0;
            ASM_KEEP_NV(var_s1);   /* MATCH pin: retail register colouring depends on it */
            var_s2 = var_s1;
            var_s0 = var_s6;
            do {
                func_80069E88(var_s0, func_80027110(var_s4, var_s1 | var_s2), 0x12);
                var_s1 += 1;
                var_s0 += 0x12;
            } while (var_s1 < 5);
            var_s0 = func_80026F54(arg0, var_s4, 0);
            if (var_s1 < var_s3) {
                var_s5 = (s32)0x800157C0;
                var_s2 = (var_s1 * 0x12) + var_s6;
                do {
                    func_80069E88(var_s2, (var_s0 * 0x13) + var_s5, 0x12);
                    var_s0 = func_80026FA8(arg0, var_s4, var_s0 + 1);
                    var_s1 += 1;
                    var_s2 += 0x12;
                } while (var_s1 < var_s3);
                tail_return = var_s6;
                ASM_TAILSLOT_PIN_TIED(tail_return);   /* MATCH pin: retail delay-slot contents depend on it */
                func_800272F8();
            }
        } else {
            var_s0 = func_80026F54(arg0, var_s4, (var_s0 * 8) - 5);
            var_s1 = 0;
            if (var_s3 > 0) {
                var_s5 = (s32)0x800157C0;
                var_s2 = var_s6;
                do {
                    func_80069E88(var_s2, (var_s0 * 0x13) + var_s5, 0x12);
                    var_s0 = func_80026FA8(arg0, var_s4, var_s0 + 1);
                    var_s1 += 1;
                    var_s2 += 0x12;
                } while (var_s1 < var_s3);
            }
        }
    }
    return var_s6;
}
