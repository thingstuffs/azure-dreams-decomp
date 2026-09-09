#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad24[0x24];
    u8 x;
    u8 y;
    s8 kind;
} Entity;

s32 func_8009FB34();
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
    register s32 temp_filter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    register s32 var_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 var_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 var_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 temp_s0;
    u8 temp_s1;
    u8 *base;
    u8 *var_s2;
    u8 *var_s3;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (arg0->kind < 0) {
        return 0;
    }
    var_s5 = 0x100;
    var_fp = -1;
    var_s4 = 0x3F;
    temp_t0 = arg1 & 0xFF;
    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
        ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
                    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    *(s16 *)temp_t0 = (s16) temp_s0;
                    temp_t0 = (s32)arg3;
                    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
