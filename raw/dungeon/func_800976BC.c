#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 *D_800E3D7C[];
extern u8 D_800E3E41;
extern void *D_80083470[3];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
M2C_UNK func_80094E34();
s32 func_80098250();
M2C_UNK func_8009CFB4();
M2C_UNK func_8009CFF4();
M2C_UNK func_8009D034();
s32 func_8009D218(void *, s32, s32);
M2C_UNK func_800A56E0();
M2C_UNK func_800B4C7C();
extern void func_80099C58(s16, s16, s16, s16, s32);

void func_8009CE1C(void *arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, s32 arg5, u16 arg6) {
    M2C_UNK var_a0;
    s16 temp_lo;
    s32 var_a2;
    s16 var_s2;
    s16 var_v1;
    s32 temp_s2;
    register s32 temp_s3 ASM_REG("$19");
    s32 temp_v1;
    M2C_UNK temp_v1_2;
    s32 var_s1;
    register s16 var_s3 ASM_REG("$19");
    s32 var_v0_2;
    s32 var_v0_3;
    M2C_UNK var_v0_4;
    register s32 var_v0_5 ASM_REG("$2");
    void *temp_t1;
    register u16 var_s4 = arg1;
    register s16 var_s5 ASM_REG("$21") = arg3;
    s32 var_v0;

    var_s3 = arg2;
    var_s2 = var_s3;
    var_s1 = 0;
    if ((arg0 != NULL) && (func_8009D218(arg0, var_s5 & 0xFFFF, arg5) == 0)) {
        if (var_s3 == 0xFF) {
            var_s2 = M2C_FIELD(*D_800E3D7C, u8 *, 0x11) * 4;
            if (var_s2 >= 0x64) {
                var_s2 = 0x63;
            }
            {
                register s32 inner_shift ASM_REG("$2");
                inner_shift = var_s4 << 0x10;
                var_v0 = inner_shift;
            }
        } else {
            register s32 default_shift ASM_REG("$2");
            default_shift = var_s4 << 0x10;
            var_v0 = default_shift;
        }
        ASM_USE_NV(var_s3);
        temp_s2 = ((var_v0 >> 0x10) + var_s2) * 2;
        M2C_FIELD(arg0, u16 *, 0x6A) = arg4;
        if ((M2C_FIELD(arg0, u8 *, 0x13) != 0) && !(M2C_FIELD(arg0, s32 *, 0x1C) & 0x238) && !(M2C_FIELD(arg0, u16 *, 0x46) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0x2A) = (u16) (arg4 + 0x800);
        }
        M2C_FIELD(arg0, u16 *, 0x22) = (u16) (M2C_FIELD(arg0, u8 *, 0x27) + func_80098250(arg0));
        if ((func_80042900(arg0, 0xA) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x22) = (u16) ((s32) (M2C_FIELD(arg0, u16 *, 0x22) << 0x10) >> 0x11);
        }
        if (M2C_FIELD(arg0, s16 *, 0x22) == 0) {
            M2C_FIELD(arg0, u16 *, 0x22) = (u16) (M2C_FIELD(arg0, u16 *, 0x22) + 1);
        }
        temp_s3 = func_8009CD58(arg0, 7, 0);
        if (var_s5 & 1) {
            if ((func_80042900(arg0, 0x13) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_21;
            }
            if (temp_s3 & 4) {
                var_s1 += 1;
            }
            if (temp_s3 & 2) {
                var_s1 -= 1;
                goto block_21;
            }
            var_v0_2 = var_s5 & 2;
            goto block_22;
        }
block_21:
        var_v0_2 = var_s5 & 2;
block_22:
        if (var_v0_2 != 0) {
            if ((func_80042900(arg0, 0x14) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_30;
            }
            if (temp_s3 & 1) {
                var_s1 += 1;
            }
            if (temp_s3 & 4) {
                var_s1 -= 1;
                goto block_30;
            }
            var_v0_3 = var_s5 & 4;
            goto block_31;
        }
block_30:
        var_v0_3 = var_s5 & 4;
block_31:
        if (var_v0_3 != 0) {
            if ((func_80042900(arg0, 0x12) << 0x10) != 0) {
                temp_s2 >>= 2;
                goto block_39;
            }
            if (temp_s3 & 2) {
                var_s1 += 1;
            }
            var_v0_5 = temp_s3 & 1;
            if (var_v0_5) {
                var_s1 -= 1;
                goto block_39;
            }
            var_v0_4 = var_s1 << 0x10;
            goto block_40;
        }
block_39:
        var_v0_4 = var_s1 << 0x10;
block_40:
        temp_lo = temp_s2 * (var_v0_4 >> 0x10);
        var_v1 = temp_lo;
        if (temp_lo < 0) {
            var_v1 = (s16) ((u32) (temp_lo + 3) >> 2);
        }
        temp_s2 += var_v1;
        temp_v1 = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0x22) - temp_s2) / 2;
        M2C_FIELD(arg0, u16 *, 0x64) = (u16) temp_v1;
        if ((s16) temp_v1 >= 0) {
            M2C_FIELD(arg0, s16 *, 0x64) = -1;
        }
        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x20000000);
        if ((func_80042900(arg0, 0x1D) << 0x10) == 0) {
            var_a2 = (s16) (0 - M2C_FIELD(arg0, u16 *, 0x64));
        } else {
            var_a2 = 0;
        }
        func_800B4C7C(3, arg0, var_a2, 0);
        if (arg0 == *D_800E3D7C) {
            D_800E3E41 = (u8) arg6;
            func_80094E34();
        }
        M2C_FIELD(arg0, s32 *, 0x60) = arg5;
        D_80083470[0] = arg0 - 0x20;
        if (!(M2C_FIELD(M2C_FIELD(arg0, void **, -0x14), u16 *, 0x14) & 0x8000)) {
            func_800419EC(8, 0x10);
        }
        var_a0 = 0x601;
        if ((arg5 != 0) && !(arg5 & 0x20000000)) {
            var_a0 = 0x602;
        }
        func_800A56E0(var_a0);
        temp_t1 = M2C_FIELD(arg0, void **, -0x14);
        temp_v1_2 = ((u16) M2C_FIELD(arg0, u16 *, 0x2A) >> 8) & 0xE;
        func_80099C58((u16) ((M2C_FIELD(temp_t1, u8 *, 0x24) << 6) + ((D_8006CCD8[(u32) temp_v1_2 >> 1] * 0x20) + 0x20)), (u16) ((M2C_FIELD(temp_t1, u8 *, 0x25) << 6) + ((D_8006CCE8[(u32) temp_v1_2 >> 1] * 0x20) + 0x20)), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x30), var_s5, (s32) (s16) arg4);
    }
}
