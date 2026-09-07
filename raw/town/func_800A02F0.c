#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))
#ifdef NON_MATCHING
#define KEEP_PAIR(a, b) ((void)0)
#define KEEP_VALUE(v) ((void)0)
#else
#define KEEP_PAIR(a, b) __asm__("" : : "r"(a), "r"(b))
#define KEEP_VALUE(v) __asm__("" : : "r"(v))
#endif

extern s32 func_80033B2C();
extern s32 func_8008CC90();
extern s32 func_8009D424();
extern void func_8009DC4C(void);
extern s16 D_8006ADD4;

void func_8009DA50(u8 *arg0, void *arg1, s32 arg2, s32 arg3)
{
    register s32 temp_t0 ASM_REG("$8");
    register s32 temp_v1 ASM_REG("$3");
    register s32 temp_s2 ASM_REG("$18");
    register s32 temp_s3 ASM_REG("$19");
    register u8 *var_s0 ASM_REG("$16");
    register u8 *var_s1 ASM_REG("$17");
    register void *var_s4 ASM_REG("$20");
    register s32 var_s5 ASM_REG("$21");
    register s32 var_s6 ASM_REG("$22");
    register s32 var_a1 ASM_REG("$5");

    var_s1 = arg0;
    var_s4 = arg1;
    var_s6 = arg2;
    var_s5 = arg3;
    var_a1 = FIELD(var_s1, u8, 1);
    if ((var_a1 & 0xC0) != 0x80) {
        var_s0 = arg0 + 1;
loop_2:
        if (*var_s1 == 0) {
            if (!(var_a1 & 1)) {
                if (func_80033B2C(FIELD(var_s0, s16, 1), var_a1) == 0) {
                    func_8009DC4C();
                    var_s0 += 0x14;
                    KEEP_VALUE(var_s0);
                    return;
                }
                goto block_8;
            }
            if (func_80033B2C(FIELD(var_s0, s16, 1), var_a1) != 1) {
block_8:
                temp_t0 = var_s6 + FIELD(var_s0, u16, 0xF);
                temp_v1 = var_s5 + FIELD(var_s0, u16, 0x11);
                temp_s2 = temp_t0;
                temp_s3 = temp_v1;
                if ((func_8008CC90(
                         (s16)(FIELD(var_s4, u16, 0) - temp_t0),
                         (s16)(FIELD(var_s4, u16, 2) - temp_v1),
                         (s16)(FIELD(var_s4, u16, 8) - temp_t0),
                         (s16)(FIELD(var_s4, u16, 0xA) - temp_v1),
                         (s16)(FIELD(var_s4, u16, 0x10) - temp_t0),
                         (s16)(FIELD(var_s4, u16, 0x12) - temp_v1),
                         (s16)(FIELD(var_s4, u16, 0x18) - temp_t0),
                         (s16)(FIELD(var_s4, u16, 0x1A) - temp_v1)) != 0) ||
                    (D_8006ADD4 == 0xC) ||
                    (FIELD(var_s0, u8, 0) & 0x10)) {
                    if (func_8009D424(
                            FIELD(var_s0, s32, 0xB),
                            FIELD(var_s0, u8, 3),
                            FIELD(var_s0, u8, 4),
                            FIELD(var_s0, u8, 5),
                            FIELD(var_s0, u8, 6),
                            FIELD(var_s0, u8, 0) & 0x20,
                            FIELD(var_s0, s32, 7),
                            (s16)temp_s2,
                            (s16)temp_s3,
                            var_s1) != 0) {
                        *var_s1 = 1;
                    }
                    KEEP_PAIR(temp_s2, temp_s3);
                    if (!(FIELD(var_s0, u8, 0) & 0xC0)) {
                        do {
                            var_s0 += 0x14;
                            var_s1 += 0x14;
                        } while (!(FIELD(var_s0, u8, 0) & 0xC0));
                    }
                }
            }
            goto block_15;
        }
block_15:
        var_s0 += 0x14;
        var_a1 = *var_s0;
        var_s1 += 0x14;
        if ((var_a1 & 0xC0) != 0x80) {
            goto loop_2;
        }
    }
}
