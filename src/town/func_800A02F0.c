#include "common.h"

typedef struct S_8009DA50_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8009DA50_0;   /* var_s1 in func_8009DA50 */

typedef struct S_8009DA50_1 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x4];
    u16 unk_18;
    u16 unk_1A;
} S_8009DA50_1;   /* var_s4 in func_8009DA50 */

typedef struct S_8009DA50_2 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_8009DA50_2;   /* var_s0 in func_8009DA50 */


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
extern s16 D_8006ADD4;

void func_8009DA50(u8 *arg0, void *arg1, s32 arg2, s32 arg3)
{
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_s2;
    register s32 temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *var_s0;
    register u8 *var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s5;
    s32 var_s6;
    register s32 var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    var_s1 = arg0;
    var_s4 = arg1;
    var_s6 = arg2;
    var_s5 = arg3;
    var_a1 = ((S_8009DA50_0 *)var_s1)->unk_01;
    if ((var_a1 & 0xC0) != 0x80) {
        var_s0 = arg0 + 1;
loop_2:
        if (*var_s1 == 0) {
            if (!(var_a1 & 1)) {
                if (func_80033B2C((*(s16 *)((u8 *)var_s0 + 1)), var_a1) == 0) {
                    var_s0 += 0x14;
                    var_a1 = *var_s0;
                    var_s1 += 0x14;
                    if ((var_a1 & 0xC0) != 0x80) {
                        goto loop_2;
                    }
                    return;
                }
                goto block_8;
            }
            if (func_80033B2C((*(s16 *)((u8 *)var_s0 + 1)), var_a1) != 1) {
block_8:
                temp_t0 = var_s6 + (*(u16 *)((u8 *)var_s0 + 0xF));
                temp_v1 = var_s5 + (*(u16 *)((u8 *)var_s0 + 0x11));
                temp_s2 = temp_t0;
                temp_s3 = temp_v1;
                if ((func_8008CC90(
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_00 - temp_t0),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_02 - temp_v1),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_08 - temp_t0),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_0A - temp_v1),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_10 - temp_t0),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_12 - temp_v1),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_18 - temp_t0),
                         (s16)(((S_8009DA50_1 *)var_s4)->unk_1A - temp_v1)) != 0) ||
                    (D_8006ADD4 == 0xC) ||
                    (((S_8009DA50_2 *)var_s0)->unk_00 & 0x10)) {
                    if (func_8009D424(
                            (*(s32 *)((u8 *)var_s0 + 0xB)),
                            ((S_8009DA50_2 *)var_s0)->unk_03,
                            ((S_8009DA50_2 *)var_s0)->unk_04,
                            ((S_8009DA50_2 *)var_s0)->unk_05,
                            ((S_8009DA50_2 *)var_s0)->unk_06,
                            ((S_8009DA50_2 *)var_s0)->unk_00 & 0x20,
                            (*(s32 *)((u8 *)var_s0 + 7)),
                            (s16)temp_s2,
                            (s16)temp_s3,
                            var_s1) != 0) {
                        *var_s1 = 1;
                    }
                    KEEP_PAIR(temp_s2, temp_s3);
                    if (!(((S_8009DA50_2 *)var_s0)->unk_00 & 0xC0)) {
                        do {
                            var_s0 += 0x14;
                            var_s1 += 0x14;
                        } while (!(((S_8009DA50_2 *)var_s0)->unk_00 & 0xC0));
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
