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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s32 D_80083460[3];
extern s32 D_800814A0[3];
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800A56E0();
M2C_UNK func_800BB2E4();
M2C_UNK func_800BC0A8();

typedef struct DungeonWork {
    u8 pad_00[0x30];
    s16 field_30[5];
    u8 pad_3A[2];
    s16 field_3C[5];
} DungeonWork;

void func_800BB55C(void *arg0, void *arg1, s32 arg2) {
    s32 sp20[2];
    s16 sp28[2];
    s16 sp30[2];
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    register s32 var_s2_angle ASM_REG("$18");
    s32 var_s5;
    s32 temp_a0_2;
    register s32 temp_s0 ASM_REG("$16");
    s32 saved_arg2;
    s32 var_s1;
    s32 var_s3;
    u16 temp_a3;
    u16 temp_v0_4;
    u16 temp_v1_4;
    register u16 temp_decay ASM_REG("$3");
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 *global_ptr;
    void *temp_a0;
    register DungeonWork *var_s3_2 ASM_REG("$19");
    DungeonWork *var_s6_ptr;

    sp20[0] = 0x01000340;
    sp20[1] = 0x460044;
    temp_s0 = arg0 + 0xC;
    func_800478B8(temp_s0);
    saved_arg2 = arg2;
    M2C_FIELD(arg0, s32 *, -0x14) = temp_s0;
    func_800BB2E4(NULL, NULL, sp20, 0, arg0);
    var_s5 = -0x400;
    var_s3 = 0;
    var_s2_angle = (s32) arg0;
    do {
        temp_s0 = (s16)var_s5;
        sp28[0] = (func_80064584(temp_s0) >> 7) + 0x362;
        sp28[1] = (func_800644B8(temp_s0) >> 7) + 0x122;
        temp_s0 += 0x999;
        sp30[0] = (func_80064584(temp_s0) >> 7) + 0x362;
        temp_v0 = (func_800644B8(temp_s0) >> 7) + 0x122;
        sp30[1] = temp_v0;
        temp_v0_2 = func_800A07D0(sp28[0], sp28[1], sp30[0], temp_v0);
        sp30[0] = (u16) sp28[0] + ((s32) (func_80064584(temp_v0_2) * M2C_FIELD(var_s2_angle, s16 *, 0x30)) >> 0xB);
        sp30[1] = (u16) sp28[1] + ((s32) (func_800644B8(temp_v0_2) * M2C_FIELD(var_s2_angle, s16 *, 0x30)) >> 0xB);
        M2C_FIELD(var_s2_angle, s16 *, 0x3C) = var_s5;
        var_s5 += 0x999;
        func_800BB2E4(sp28, sp30, sp20, 0, NULL);
        var_s3 += 1;
        var_s2_angle += 2;
    } while (var_s3 < 5);
    var_s5 = -0x400;
    ASM_KEEP_NV(var_s5);
    ASM_KEEP_NV(arg0);
    ASM_SET(var_s3_2);
    var_s3_2 = arg0;
    temp_s0 = var_s5 << 0x10;
    do {
        temp_s0 >>= 0x10;
        sp28[0] = (func_80064584((s16) temp_s0) >> 7) + 0x362;
        sp28[1] = (func_800644B8((s16) temp_s0) >> 7) + 0x122;
        var_s2_angle = var_s5;
        var_s1 = 0;
        if (var_s3_2->field_30[0] > 0) {
            var_s6_ptr = var_s3_2;
            temp_s0 = var_s2_angle + 0x19;
            do {
                var_s2_angle = temp_s0;
                ASM_KEEP_NV(temp_s0);
                sp30[0] = (func_80064584((s16)temp_s0) >> 7) + 0x362;
                sp30[1] = (func_800644B8((s16)temp_s0) >> 7) + 0x122;
                func_800BB2E4(sp28, sp30, sp20, 0, NULL);
                sp28[0] = (u16) sp30[0];
                sp28[1] = (u16) sp30[1];
                temp_s0 = var_s2_angle + 0x19;
            } while (++var_s1 < var_s6_ptr->field_30[0]);
        }
        temp_v0_3 = (u16) var_s3_2->field_30[0] + 1;
        var_s3_2->field_30[0] = temp_v0_3;
        var_s5 += 0x333;
        if (temp_v0_3 >= 0x1F) {
            var_s3_2->field_30[0] = 0x1F;
            if (M2C_FIELD(arg0, s16 *, 0x4A) == 0) {
                if (M2C_FIELD(arg0, s32 (**)(), 0x60)() != 0) {
                    M2C_FIELD(arg0, s16 *, 0x50) = 0x120;
                    M2C_FIELD(arg0, s16 *, 0x4A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) + 1);
                    func_800A56E0(0x603);
                }
            }
            M2C_FIELD(arg0, s16 *, 0x4C) = 0x20;
        }
        var_s3_2 = (DungeonWork *)((u8 *)var_s3_2 + 2);
        temp_s0 = var_s5 << 0x10;
    } while ((s32) var_s3_2 < (s32) (arg0 + 0xA));
    func_800BB2E4(NULL, NULL, sp20, 1, NULL);
    M2C_FIELD(arg0, s32 *, -0x14) = saved_arg2;
    if (M2C_FIELD(arg0, s16 *, 0x4A) != 0) {
        M2C_FIELD(arg0, u16 *, 0x4E) = (u16) (M2C_FIELD(arg0, u16 *, 0x4E) + 0x100);
        var_s3_2 = (DungeonWork *) 0;
        do {
            var_s3_2 = (DungeonWork *)((s32) var_s3_2 + 1);
            temp_a3 = M2C_FIELD(arg0, u16 *, 0x4E) + 0x400;
            M2C_FIELD(arg0, u16 *, 0x4E) = temp_a3;
            func_800BC0A8(M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), (s16) temp_a3, (s32) M2C_FIELD(arg0, s16 *, 0x50), (s32) M2C_FIELD(arg0, s16 *, 0x58), M2C_FIELD(arg0, s32 *, 0x5C), 6);
        } while ((s32) var_s3_2 < 4);
        if (M2C_FIELD(arg0, s16 *, 0x58) < 0x20) {
            M2C_FIELD(arg0, s16 *, 0x58) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x58) + 1);
        }
        if (M2C_FIELD(arg0, s16 *, 0x4A) == 1) {
            temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x64) + 1;
            M2C_FIELD(arg0, u16 *, 0x64) = temp_v0_4;
            if ((s16) temp_v0_4 >= 0x21) {
                temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x4A) + 1;
                M2C_FIELD(arg0, u16 *, 0x64) = 0x10U;
                M2C_FIELD(arg0, u16 *, 0x4A) = temp_v1_4;
                return;
            }
        } else {
            ASM_SET(temp_decay);
            temp_v1 = (u8) M2C_FIELD(arg0, s32 *, 0x5C);
            temp_a0 = arg0 + 0x5C;
            M2C_FIELD(temp_a0, u8 *, 0) = (u8) (temp_v1 - ((s32) temp_v1 / (s16) M2C_FIELD(arg0, u16 *, 0x64)));
            temp_v1_2 = M2C_FIELD(temp_a0, u8 *, 1);
            M2C_FIELD(temp_a0, u8 *, 1) = (u8) (temp_v1_2 - ((s32) temp_v1_2 / (s16) M2C_FIELD(arg0, u16 *, 0x64)));
            temp_v1_3 = M2C_FIELD(temp_a0, u8 *, 2);
            M2C_FIELD(temp_a0, u8 *, 2) = (u8) (temp_v1_3 - ((s32) temp_v1_3 / (s16) M2C_FIELD(arg0, u16 *, 0x64)));
            temp_a0_2 = (s16) M2C_FIELD(arg0, s16 *, 0x50) / (s16) M2C_FIELD(arg0, u16 *, 0x64);
            temp_decay = M2C_FIELD(arg0, u16 *, 0x64) - 1;
            M2C_FIELD(arg0, u16 *, 0x64) = temp_decay;
            M2C_FIELD(arg0, s16 *, 0x50) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x50) - temp_a0_2);
            if ((temp_decay << 0x10) <= 0) {
                global_ptr = (u8 *)D_80083460;
                M2C_FIELD(global_ptr, u16 *, 0xA) = (u16) (M2C_FIELD(global_ptr, u16 *, 0xA) - 1);
                M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                D_800814A0[0] = D_800814A0[0] | 0x8000;
            }
        }
    }
}
