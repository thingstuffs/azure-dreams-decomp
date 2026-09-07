/* cfail-repair: tf7-phase1-cache-v3 */
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
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() ((void)0)
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

M2C_UNK func_8006BFA0();
s32 func_8006D9DC();
M2C_UNK func_8006DBBC();
M2C_UNK func_8006DD4C();
M2C_UNK func_8006F49C();
extern u8 *D_8012F130;

s32 func_8080DAB8(void *arg0) {
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a1;
    register s32 temp_s0 ASM_REG("$16");
    register M2C_UNK *temp_s1 ASM_REG("$17");
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_v1;
    u32 temp_v1_2;
    u32 coord0_shifted;
    u32 coord1_shifted;
    s32 coord0_signed;
    s32 coord1_signed;
    register u32 temp_low ASM_REG("$3");
    register void *temp_a0_2 ASM_REG("$4");
    void *temp_a1_2;
    register void *var_s3 ASM_REG("$19");
    register u8 **rootp ASM_REG("$20");
    register u8 *scratch0;
    register u8 *scratch1 ASM_REG("$22");
    register u8 *scratch2 ASM_REG("$23");
    register u8 *bound_base0 ASM_REG("$5");
    register u8 *bound_base1 ASM_REG("$4");
    register u32 mask_low ASM_REG("$18");
    register u32 mask_high ASM_REG("$21");
    register u32 bound_const ASM_REG("$2");

    var_s3 = arg0;
    rootp = &D_8012F130;
    scratch0 = (u8 *)0x1F800000;
    scratch1 = (u8 *)0x1F800100;
    scratch2 = (u8 *)0x1F800180;
    mask_low = 0x00FFFFFF;
    mask_high = 0xFF000000;
    do {
        func_8006BFA0(var_s3 + 8, scratch0, scratch1, scratch2, scratch2, 2);
        var_v1 = 0;
        ASM_KEEP_NV(var_v1);
        temp_s0 = M2C_FIELD(*rootp, s32 *, 0x8D0);
        if (temp_s0 != 0) {
            temp_v1 = temp_s0 + 0x14;
            bound_base0 = (u8 *)*rootp;
            ASM_KEEP_NV(bound_base0);
            bound_const = 0x108D4;
            var_v1 = temp_v1 & (0 - ((u32)(bound_base0 + bound_const) >= temp_v1));
        }
        M2C_FIELD(*rootp, s32 *, 0x8D0) = var_v1;
        var_v1_2 = 0;
        ASM_KEEP_NV(var_v1_2);
        temp_s1 = M2C_FIELD(*rootp, s32 *, 0x8D0);
        if (temp_s1 != 0) {
            temp_v1_2 = (u8 *)temp_s1 + 0xC;
            bound_base1 = (u8 *)*rootp;
            ASM_KEEP_NV(bound_base1);
            bound_const = 0x108D4;
            var_v1_2 = temp_v1_2 & (0 - ((u32)(bound_base1 + bound_const) >= temp_v1_2));
        }
        M2C_FIELD(*rootp, s32 *, 0x8D0) = var_v1_2;
        func_8006F49C((s32 *)temp_s1, 0, 0, func_8006D9DC(0, 0, 0, 0) & 0xFFFF, 0);
        M2C_FIELD(temp_s0, s32 *, 4) = (s32)M2C_FIELD(var_s3, s32 *, 0x18);
        M2C_FIELD(temp_s0, s32 *, 0xC) = (s32)M2C_FIELD(var_s3, s32 *, 0x1C);
        func_8006DD4C((s32 *)temp_s0);
        func_8006DBBC((s32 *)temp_s0, 1);
        M2C_FIELD(temp_s0, s32 *, 8) = (s32)*(s32 *)scratch0;
        M2C_FIELD(temp_s0, s32 *, 0x10) = (s32)*(s32 *)(scratch0 + 4);
        temp_v0 = *(volatile u16 *)scratch1;
        coord0_shifted = temp_v0 << 0x10;
        temp_v0_2 = *((volatile u16 *)scratch1 + 1);
        ASM_SCHED_BARRIER();
        coord0_signed = (s32)coord0_shifted >> 0x10;
        coord1_shifted = temp_v0_2 << 0x10;
        coord1_signed = (s32)coord1_shifted >> 0x10;
        coord0_shifted = (u32)((s32)coord0_shifted >> 0x13);
        if (coord0_signed >= coord1_signed) {
            coord0_shifted = (u32)((s32)coord1_shifted >> 0x13);
        }
        temp_a1 = (s32)(coord0_shifted << 0x10) >> 0xE;
        M2C_FIELD(temp_s0, s32 *, 0) = (s32)((M2C_FIELD(temp_s0, s32 *, 0) & mask_high) | (M2C_FIELD((u8 *)((u32)temp_a1 + (u32)*rootp), s32 *, 0xB0) & mask_low));
        temp_a0_2 = (void *)((u32)temp_a1 + (u32)*rootp);
        temp_low = temp_s0 & mask_low;
        M2C_FIELD(temp_a0_2, s32 *, 0xB0) = (s32)((M2C_FIELD(temp_a0_2, s32 *, 0xB0) & mask_high) | temp_low);
        *temp_s1 = (s32)((*temp_s1 & mask_high) | (M2C_FIELD((u8 *)((u32)temp_a1 + (u32)*rootp), s32 *, 0xB0) & mask_low));
        temp_a1 = temp_a1 + (u8 *)*rootp;
        temp_low = (u32)temp_s1 & mask_low;
        M2C_FIELD((u8 *)temp_a1, s32 *, 0xB0) = (s32)((M2C_FIELD((u8 *)temp_a1, s32 *, 0xB0) & mask_high) | temp_low);
        temp_a0 = M2C_FIELD(var_s3, s32 *, -8);
        var_s3 = temp_a0 + 0x20;
    } while (temp_a0 != 0);
    ASM_KEEP_NV(temp_a0);
    return 0;
}
