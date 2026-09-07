/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A200_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001A200_0;   /* D_80016000[0] in func_8001A200 */

typedef struct S_8001A200_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_8001A200_1;   /* temp_v0 in func_8001A200 */

typedef struct S_8001A200_2 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8001A200_2;   /* var_s0 in func_8001A200 */


M2C_UNK func_8001A188();     /* extern */
M2C_UNK func_8001A2BC();                            /* extern */
extern void *D_80016000[3];
extern u8 D_8001791C[96];

void func_8001A200(void *arg0, s32 *arg1) {
    u8 *var_a2;
    s32 temp_a0;
    register s32 temp_s2 ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 temp_v1;
    void *temp_v0;
    s32 var_a1;
    s32 var_a3;
    register u8 *var_s3 ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *var_s1;
    register void *var_s0 ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *split_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 final_status;
    register s32 final_mask ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    var_s0 = arg0;
    temp_v0 = ((S_8001A200_0 *)(D_80016000[0]))->unk_20;
    var_s1 = (u8 *)arg1;
    temp_s2 = *((((S_8001A200_1 *)temp_v0)->unk_2D4(0)) + (s32 *)var_s1);
    if ((((S_8001A200_2 *)var_s0)->unk_01 & 0xC0) != 0x80) {
        split_base = (u8 *)0x80010000;
        ASM_KEEP(split_base);   /* MATCH pin: load-bearing for the whole function shape */
        var_s3 = split_base + 0x791C;
        var_s1 = var_s0 + 1;
loop_2:
        var_a3 = 1;
        var_a1 = temp_s2 + 4;
        var_a2 = var_s3 + 0xC;
loop_3:
        temp_v1 = *(s32 *)var_a2;
        temp_a0 = (*(s32 *)((u8 *)var_s1 + 0xB));
        if ((temp_v1 == temp_a0) || ((temp_v1 == 6) && (temp_a0 == 0x64))) {
            func_8001A188(var_s0, var_a1, var_a2, var_a3);
            func_8001A2BC();
            var_s1 += 0x14;
            ASM_KEEP(var_s1);   /* MATCH pin: retail delay-slot contents depend on it */
            return;
        }
        var_a1 += 4;
        var_a3 += 1;
        var_a2 += 0xC;
        if (var_a3 >= 8) {
            var_s1 += 0x14;
            var_s0 += 0x14;
            final_status = *var_s1;
            final_mask = 0x80;
            if ((final_status & 0xC0) == final_mask) {
            } else {
                goto loop_2;
            }
        } else {
            goto loop_3;
        }
    }
}
