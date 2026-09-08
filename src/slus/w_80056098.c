#include "common.h"

#include "common.h"

/* D_80085458 element (stride 0x78). Envelope channel A. */
typedef struct {
    /* 0x00 */ u8 pad00[0x25];
    /* 0x25 */ s8 f25;
    /* 0x26 */ u8 f26;
    /* 0x27 */ s8 f27;
    /* 0x28 */ u8 f28;
    /* 0x29 */ u8 pad29[3];
    /* 0x2C */ s32 f2c;
    /* 0x30 */ s32 f30;
    /* 0x34 */ u8 f34;
    /* 0x35 */ u8 f35;
    /* 0x36 */ u8 f36;
    /* 0x37 */ u8 pad37;
    /* 0x38 */ s32 f38;
    /* 0x3C */ s32 f3c;
} S_80085458;

void func_80056098(S_80085458 *arg0) {
    s32 temp_a1;
    register s32 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_v0_2;
    s32 temp_v0;
    register s32 a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 v1;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 *pu;
    s8 *ps;

    temp_a1 = arg0->f30;
    if (temp_a1 != 0) {
        temp_v1 = arg0->f26;
        if (temp_v1 != arg0->f34) {
            arg0->f26 = temp_v1 + 1;
            return;
        }
        temp_v1_2 = arg0->f28;
        if (temp_v1_2 >= arg0->f35) {
            arg0->f2c = temp_a1;
        } else {
            if (temp_v1_2 != 0) {
                /* split so f2c loads into $v0 first, then f38 into $v1 */
                var_v0 = arg0->f2c;
                var_v0 = var_v0 + arg0->f38;
            } else {
                var_v0 = arg0->f38;
            }
            arg0->f2c = var_v0;
            arg0->f28 = arg0->f28 + 1;
        }
        /* Dual-typed pointers defeat store-load CSE → sb then lb.
           f25=0 early is scheduled into bgez delay under -fno-schedule-insns
           with schedule-insns2 still active. */
        pu = (u8 *)&arg0->f27;
        ps = &arg0->f27;
        *pu = *pu + arg0->f36;
        arg0->f25 = 0;
        temp_v0 = *ps;
        if (temp_v0 < 0) {
            temp_v0 = -temp_v0;
            a1 = temp_v0 << 1;
            v1 = a1;
            if ((temp_v0 << 25) < 0) {
                v1 = -a1;
            }
            var_v0_2 = arg0->f2c * (s8)v1;
            if (var_v0_2 > 0) {
                var_v0_2 = -var_v0_2;
            }
        } else {
            a1 = temp_v0 << 1;
            v1 = a1;
            if ((temp_v0 << 25) < 0) {
                v1 = -a1;
            }
            var_v0_2 = arg0->f2c * (s8)v1;
            if (var_v0_2 < 0) {
                var_v0_2 = -var_v0_2;
            }
        }
        if (var_v0_2 != 0) {
            if (var_v0_2 < 0) {
                var_v0_2 += 0x3FF;
            }
            arg0->f3c = var_v0_2 >> 10;
            return;
        }
        arg0->f3c = 0;
    }
}
