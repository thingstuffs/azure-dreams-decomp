#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 kind;
} Entity;

s32 func_8009FB34();
void func_800A6FFC();
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

typedef struct S_800A6E8C_0 {
    u8 unk_00;
    u8 unk_01;
} S_800A6E8C_0;   /* var_s2 in func_800A6E8C */

typedef struct S_800A6E8C_1 {
    u8 unk_00;
    u8 unk_01;
} S_800A6E8C_1;   /* var_s3 in func_800A6E8C */

u32 func_800A6E8C(Entity *arg0, s32 arg1, s16 *arg2, s16 *arg3) {
    s32 sp10;
    s32 var_fp;
    s32 var_s4;
    s32 temp_a2;
    register s32 temp_filter ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_s7 ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_t0 ASM_REG("$8");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    register s32 var_a0 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 var_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 var_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_s5 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    u8 temp_s0;
    u8 temp_s1;
    u8 *base;
    u8 *var_s2;
    u8 *var_s3;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (arg0->kind < 0) {
        func_800A6FFC();
        return 0;
    }
    var_s5 = 0x100;
    var_fp = -1;
    var_s4 = 0x3F;
    temp_t0 = arg1 & 0xFF;
    ASM_KEEP(temp_t0);   /* MATCH pin: retail register colouring depends on it */
    sp10 = temp_t0;
    temp_filter = arg1 << 0x10;
    temp_s7 = temp_filter >> 0x18;
    base = D_800E36C8;
    var_s3 = base + 0x2F4;
    base = D_800E3548;
    var_s2 = base + 0xFC;
    do {
        temp_filter = ((S_800A6E8C_0 *)var_s2)->unk_01;
        temp_t0 = sp10;
        ASM_KEEP(temp_t0);   /* MATCH pin: retail register colouring depends on it */
        if ((temp_filter == temp_t0) && ((temp_s7 == 0) || (((S_800A6E8C_0 *)var_s2)->unk_00 == temp_s7))) {
            temp_s0 = ((S_800A6E8C_1 *)var_s3)->unk_00;
            temp_s1 = ((S_800A6E8C_1 *)var_s3)->unk_01;
            if ((s16)func_8009FB34(temp_s0, temp_s1) == arg0->kind) {
                temp_v0 = temp_s0 - arg0->x;
                var_a1 = temp_v0;
                if (temp_v0 < 0) {
                    var_a1 = 0 - var_a1;
                }
                temp_v1 = var_a1 << 0x10;
                temp_v0_2 = temp_s1 - arg0->y;
                var_a0 = temp_v0_2;
                if (temp_v0_2 < 0) {
                    var_a0 = 0 - var_a0;
                }
                temp_v0_3 = var_a0 << 0x10;
                temp_a2 = temp_v1 < temp_v0_3;
                var_a3 = var_a1;
                if (temp_a2 != 0) {
                    var_a3 = var_a0;
                }
                temp_v1 = var_s5 << 0x10;
                temp_v0_3 = var_a3 << 0x10;
                if (temp_v0_3 < temp_v1) {
                    var_s5 = var_a1;
                    if (temp_a2 != 0) {
                        var_s5 = var_a0;
                    }
                    temp_t0 = (s32)arg2;
                    ASM_KEEP(temp_t0);   /* MATCH pin: retail register colouring depends on it */
                    *(s16 *)temp_t0 = (s16) temp_s0;
                    temp_t0 = (s32)arg3;
                    ASM_KEEP(temp_t0);   /* MATCH pin: retail register colouring depends on it */
                    var_fp = var_s4;
                    *(s16 *)temp_t0 = (s16) temp_s1;
                }
            }
        }
        var_s3 -= 0xC;
        var_s4 -= 1;
        var_s2 -= 4;
    } while (var_s4 >= 0);
    return (u32) ~((s16)var_fp) >> 0x1F;
}
