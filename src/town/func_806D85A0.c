#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D85A0_0 {
    void * unk_00;
} S_806D85A0_0;   /* &D_80016000 in func_806D85A0 */

typedef struct S_806D85A0_1 {
    u8 pad_00[0x2D0];
    void * unk_2D0;
    u8 pad_2D4[0x5D2C];
    void * unk_6000;
} S_806D85A0_1;   /* temp_func in func_806D85A0 */

typedef struct S_806D85A0_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806D85A0_2;   /* temp_v1 in func_806D85A0 */

typedef struct S_806D85A0_3 {
    u8 pad_00[0x3640];
    u8 unk_3640;
} S_806D85A0_3;   /* var_s6 + var_s2 in func_806D85A0 */

typedef struct S_806D85A0_4 {
    s16 unk_00;
    s16 unk_02;
} S_806D85A0_4;   /* temp_s3 in func_806D85A0 */

typedef struct S_806D85A0_5 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
} S_806D85A0_5;   /* ((S_806D85A0_0 *)(&D_80016000))->unk_00 in func_806D85A0 */

typedef struct S_806D85A0_6 {
    u8 pad_00[0x2D0];
    M2C_UNK (*unk_2D0)(s32, s32, s32);
} S_806D85A0_6;   /* ((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_20 in func_806D85A0 */


void *func_80017024();                 /* extern */
s32 func_8001876C();                         /* extern */
extern volatile M2C_UNK D_80016000;
extern M2C_UNK D_80018FE0;

void func_806D85A0(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    register s32 var_s7 ASM_REG("$23");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v0;
    s32 call_a0;
    register s32 call_a1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 call_a2;
    register void *temp_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *temp_func ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_s0;
    register void *temp_s3 ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    void *var_s6;

    temp_s0 = ((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_38;
    if (func_8001876C(1) == 0) {
        temp_v0 = func_8001876C(2);
        var_s7 = 2;
        if (temp_v0 != 0) {
            var_s7 = 1;
        }
    } else {
        var_s7 = 0;
    }
    call_a0 = 4;
    ASM_KEEP_NV(call_a0);   /* MATCH pin: keeps a statement from moving across a call/branch */
    call_a1 = call_a0;
    call_a2 = 0;
    ASM_KEEP_NV(call_a1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP_NV(call_a2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    temp_func = (void *)0x80010000;
    ASM_KEEP_NV(temp_func);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_v1 = ((S_806D85A0_1 *)temp_func)->unk_6000;
    var_s4 = call_a2;
    temp_func = ((S_806D85A0_2 *)temp_v1)->unk_20;
    var_s5 = var_s7 * 8;
    temp_func = ((S_806D85A0_1 *)temp_func)->unk_2D0;
    ASM_KEEP(temp_func);   /* MATCH pin: keeps a statement from moving across a call/branch */
    var_s6 = temp_s0;
    ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))temp_func)(call_a0, call_a1, call_a2);
    do {
        var_s2 = 0;
        if ((*(s16 *)((u8 *)(&D_80018FE0) + var_s5)) > 0) {
            s16 *temp_fp;

            temp_func = (void *)0x80020000;
            ASM_KEEP_NV(temp_func);   /* MATCH pin: keeps a statement from moving across a call/branch */
            temp_fp = (s16 *)((s8 *)temp_func - 0x7020);
loop_6:
            if (((S_806D85A0_3 *)(var_s6 + var_s2))->unk_3640 != 0) {
                temp_s3 = func_80017024(var_s4, var_s2, var_s7);
                if (var_s4 == 0) {
                    var_s1 = 0;
                    do {
                        var_s0 = 0;
loop_10:
                        var_a2 = var_s1 + var_s0;
                        temp_a0 = ((S_806D85A0_4 *)temp_s3)->unk_00 + var_s1;
                        temp_a1 = ((S_806D85A0_4 *)temp_s3)->unk_02 + var_s0;
                        ((S_806D85A0_6 *)(((S_806D85A0_5 *)(((S_806D85A0_0 *)(&D_80016000))->unk_00))->unk_20))->unk_2D0(temp_a0, temp_a1, var_a2);
                        var_s0 += 1;
                        if (var_s0 < 2) {
                            goto loop_10;
                        }
                        var_s1 += 1;
                    } while (var_s1 < 2);
                }
                var_s2 += 1;
                if (var_s2 < (*(s16 *)((u8 *)((s8 *)(u32)var_s5) + (s32)temp_fp))) {
                    goto loop_6;
                }
            }
        }
        var_s5 += 0x18;
        var_s4 += 1;
        var_s6 += 0xC;
    } while (var_s4 < 0x10);
}
