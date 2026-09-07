#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

s32 func_80095BC0();                  /* extern */
s32 func_80095BF0();                  /* extern */
s32 func_80095C20();             /* extern */
s32 func_80095C50();             /* extern */
void func_800961A8(void *);                 /* extern */
void func_800961D8(void *);                 /* extern */
extern s32 D_800FE5C0[];
#ifdef NON_MATCHING
#define D_80100000 ((s32 *)((s8 *)D_800FE5C0 + 0x1A40))
#else
#define D_80100000 ((s32 *)0x80100000)
#endif

void func_80095C80(void *arg0) {
    struct {
        s32 x;
        s32 y;
        s32 z;
        s32 pad3;
        s32 pad4;
    } sp10;
    M2C_UNK *base;
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    M2C_UNK *var_a0_3;
    M2C_UNK *var_a0_4;
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v1;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    register s32 temp_v1_3 ASM_REG("$2");
    register M2C_UNK *neg_page ASM_REG("$2");

    neg_page = (M2C_UNK *)D_80100000;
    ASM_KEEP_NV(neg_page);
    base = (M2C_UNK *)((s8 *)neg_page - 0x1A40);
    {
        if (M2C_FIELD(base, s32 *, 0xC) <= 0) {
            goto block_24_low;
        }
        if (M2C_FIELD(base, s32 *, 0x10) > 0) {
            register s32 collision_x ASM_REG("$16");
            s32 return_x;
            register s32 coord ASM_REG("$3");
            void *next_a0;
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(base, s32 *, 0xC);
            sp10.y = M2C_FIELD(arg0, s32 *, 4);
            sp10.z = M2C_FIELD(arg0, s32 *, 8);
            return_x = func_80095BC0(&sp10, 0);
            next_a0 = &sp10;
            ASM_KEEP_NV(next_a0);
            collision_x = M2C_FIELD(arg0, s32 *, 0);
            sp10.x = collision_x;
            collision_x = collision_x < (return_x << 0x10);
            ASM_KEEP_NV(collision_x);
            coord = M2C_FIELD(arg0, s32 *, 4);
            ASM_CLOBBER("$5");
            temp_a1 = M2C_FIELD(base, s32 *, 0x10);
            collision_x ^= 1;
            sp10.y = coord - temp_a1;
            coord = M2C_FIELD(arg0, s32 *, 8);
            sp10.z = coord;
            return_x = func_80095C20(next_a0, 0);
            coord = M2C_FIELD(arg0, s32 *, 4);
            return_x <<= 0x10;
            coord = coord < return_x;
            return_x = coord ^ 1;
            if (collision_x == 0) {
                var_a0 = (M2C_UNK *)D_80100000;
                if (return_x == 0) {
                    s32 angle_x;
                    s32 angle_y;
                    angle_x = M2C_FIELD(arg0, u16 *, 2);
                    angle_y = M2C_FIELD(arg0, u16 *, 6);
                    angle_x &= 0x3F;
                    angle_y &= 0x3F;
                    angle_x = angle_x < angle_y;
                    if (angle_x == 0) {
                        goto block_57;
                    }
                    goto call_a8;
                }
                goto block_8;
            }
            var_a0 = (M2C_UNK *)D_80100000;
            ASM_KEEP_NV(var_a0);
block_8:
            ASM_KEEP_NV(var_a0);
            var_a0 = (M2C_UNK *)((s8 *)var_a0 - 0x1A40);
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(var_a0, s32 *, 0xC);
            temp_v0 = M2C_FIELD(arg0, s32 *, 4);
            ASM_KEEP_NV(temp_v0);
            temp_v1 = M2C_FIELD(var_a0, s32 *, 0x10);
            ASM_CLOBBER("$5");
            temp_a1 = 0;
            ASM_KEEP_NV(temp_a1);
            sp10.y = temp_v0 - temp_v1;
            sp10.z = M2C_FIELD(arg0, s32 *, 8) - temp_v1;
            temp_v1 = M2C_FIELD(arg0, s32 *, 0) < (func_80095BC0(&sp10, temp_a1) << 0x10);
            temp_v1 ^= 1;
            if (temp_v1 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        if (M2C_FIELD(base, s32 *, 0x10) < 0) {
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(base, s32 *, 0xC);
            sp10.y = M2C_FIELD(arg0, s32 *, 4);
            sp10.z = M2C_FIELD(arg0, s32 *, 8);
            temp_s0_2 = M2C_FIELD(arg0, s32 *, 0) < (func_80095BC0(&sp10, 1) << 0x10);
            temp_s0_2 ^= 1;
            sp10.x = M2C_FIELD(arg0, s32 *, 0);
            sp10.y = M2C_FIELD(arg0, s32 *, 4) - M2C_FIELD(base, s32 *, 0x10);
            sp10.z = M2C_FIELD(arg0, s32 *, 8);
            temp_v0_4 = (func_80095C50(&sp10, 0) << 0x10) >= M2C_FIELD(arg0, s32 *, 4);
            if (temp_s0_2 == 0) {
                var_a0_2 = (M2C_UNK *)D_80100000;
                if (temp_v0_4 == 0) {
                    s32 angle_x2;
                    angle_x2 = M2C_FIELD(arg0, u16 *, 2);
                    temp_v1_3 = (s16) M2C_FIELD(arg0, u16 *, 6);
                    angle_x2 &= 0x3F;
                    ASM_KEEP_NV(angle_x2);
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    angle_x2 = angle_x2 < temp_v1_3;
                    if (angle_x2 != 0) {
                        goto call_a8;
                    }
                    goto block_57;
                }
                goto block_20;
            }
            var_a0_2 = (M2C_UNK *)D_80100000;
            ASM_KEEP_NV(var_a0_2);
block_20:
            ASM_KEEP_NV(var_a0_2);
            var_a0_2 = (M2C_UNK *)((s8 *)var_a0_2 - 0x1A40);
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(var_a0_2, s32 *, 0xC);
            temp_v0_2 = M2C_FIELD(arg0, s32 *, 4);
            ASM_KEEP_NV(temp_v0_2);
            temp_v1_2 = M2C_FIELD(var_a0_2, s32 *, 0x10);
            ASM_CLOBBER("$5");
            temp_a1 = 1;
            ASM_KEEP_NV(temp_a1);
            sp10.y = temp_v0_2 - temp_v1_2;
            sp10.z = M2C_FIELD(arg0, s32 *, 8) - temp_v1_2;
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0) >= (func_80095BC0(&sp10, temp_a1) << 0x10);
            ASM_KEEP_NV(temp_v1_2);
            if (temp_v1_2 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        goto block_24;
    }
block_24:
    {
    unsigned long neg_work;
    neg_page = (M2C_UNK *)D_80100000;
    ASM_KEEP_NV(neg_page);
block_24_low:
    neg_work = (unsigned long)((s8 *)neg_page - 0x1A40);
    {
        if (M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0xC) >= 0) {
            goto block_52_low;
        }
        if (M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0x10) > 0) {
            register s32 neg_a1 ASM_REG("$5");
            register s32 neg_coord ASM_REG("$3");
            s32 neg_return;
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0xC);
            sp10.y = M2C_FIELD(arg0, s32 *, 4);
            sp10.z = M2C_FIELD(arg0, s32 *, 8);
            temp_v0_5 = func_80095BF0(&sp10, 0);
            temp_a2 = M2C_FIELD(arg0, s32 *, 0);
            sp10.x = temp_a2;
            neg_coord = M2C_FIELD(arg0, s32 *, 4);
            neg_a1 = M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0x10);
            neg_work = temp_v0_5 << 0x10;
            neg_work = (s32)neg_work < temp_a2;
            neg_work ^= 1;
            sp10.y = neg_coord - neg_a1;
            neg_coord = M2C_FIELD(arg0, s32 *, 8);
            sp10.z = neg_coord;
            neg_return = func_80095C20(&sp10, 1, temp_a2);
            neg_coord = M2C_FIELD(arg0, s32 *, 4);
            neg_return <<= 0x10;
            neg_coord = neg_coord < neg_return;
            neg_return = neg_coord ^ 1;
            if (neg_work == 0) {
                var_a0_3 = (M2C_UNK *)D_80100000;
                if (neg_return == 0) {
                    s32 angle_y3;
                    temp_v1_3 = (s16) M2C_FIELD(arg0, u16 *, 2);
                    angle_y3 = M2C_FIELD(arg0, u16 *, 6);
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    angle_y3 &= 0x3F;
                    if (temp_v1_3 < angle_y3) {
                        goto call_a8;
                    }
                    goto block_57;
                }
                goto block_34;
            }
            var_a0_3 = (M2C_UNK *)D_80100000;
            ASM_KEEP_NV(var_a0_3);
block_34:
            ASM_KEEP_NV(var_a0_3);
            var_a0_3 = (M2C_UNK *)((s8 *)var_a0_3 - 0x1A40);
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(var_a0_3, s32 *, 0xC);
            temp_v0_3 = M2C_FIELD(arg0, s32 *, 4);
            ASM_KEEP_NV(temp_v0_3);
            neg_coord = M2C_FIELD(var_a0_3, s32 *, 0x10);
            ASM_CLOBBER("$5");
            neg_a1 = 0;
            ASM_KEEP_NV(neg_a1);
            sp10.y = temp_v0_3 - neg_coord;
            sp10.z = M2C_FIELD(arg0, s32 *, 8) - neg_coord;
            temp_v1_3 = (func_80095BF0(&sp10, neg_a1) << 0x10) < M2C_FIELD(arg0, s32 *, 0);
            temp_v1_3 ^= 1;
            if (temp_v1_3 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        if (M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0x10) < 0) {
            register s32 neg2_a1 ASM_REG("$5");
            register s32 neg2_coord ASM_REG("$3");
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0xC);
            sp10.y = M2C_FIELD(arg0, s32 *, 4);
            sp10.z = M2C_FIELD(arg0, s32 *, 8);
            temp_v0_7 = func_80095BF0(&sp10, 1);
            temp_a2_2 = M2C_FIELD(arg0, s32 *, 0);
            sp10.x = temp_a2_2;
            neg2_coord = M2C_FIELD(arg0, s32 *, 4);
            neg2_a1 = M2C_FIELD((M2C_UNK *)neg_work, s32 *, 0x10);
            neg_work = temp_v0_7 << 0x10;
            neg_work = (s32)neg_work < temp_a2_2;
            neg_work ^= 1;
            sp10.y = neg2_coord - neg2_a1;
            neg2_coord = M2C_FIELD(arg0, s32 *, 8);
            sp10.z = neg2_coord;
            temp_v1_3 = func_80095C50(&sp10, 1, temp_a2_2);
            neg2_coord = M2C_FIELD(arg0, s32 *, 4);
            temp_v1_3 <<= 0x10;
            temp_v1_3 = temp_v1_3 < neg2_coord;
            temp_v1_3 ^= 1;
            if (neg_work == 0) {
                var_a0_4 = (M2C_UNK *)D_80100000;
                if (temp_v1_3 == 0) {
                    s32 angle_y4;
                    temp_v1_3 = (s16) M2C_FIELD(arg0, u16 *, 2);
                    angle_y4 = (s16) M2C_FIELD(arg0, u16 *, 6);
                    if (temp_v1_3 < 0) {
                        temp_v1_3 = 0 - temp_v1_3;
                    }
                    temp_v1_3 &= 0x3F;
                    ASM_KEEP_NV(temp_v1_3);
                    if (angle_y4 < 0) {
                        angle_y4 = -angle_y4;
                    }
                    angle_y4 &= 0x3F;
                    if (temp_v1_3 < angle_y4) {
                        goto call_d8;
                    }
                    goto call_a8;
                }
                goto block_48;
            }
            var_a0_4 = (M2C_UNK *)D_80100000;
            ASM_KEEP_NV(var_a0_4);
block_48:
            ASM_KEEP_NV(var_a0_4);
            var_a0_4 = (M2C_UNK *)((s8 *)var_a0_4 - 0x1A40);
            sp10.x = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(var_a0_4, s32 *, 0xC);
            temp_v0_6 = M2C_FIELD(arg0, s32 *, 4);
            ASM_KEEP_NV(temp_v0_6);
            neg2_coord = M2C_FIELD(var_a0_4, s32 *, 0x10);
            ASM_CLOBBER("$5");
            neg2_a1 = 1;
            ASM_KEEP_NV(neg2_a1);
            sp10.y = temp_v0_6 - neg2_coord;
            sp10.z = M2C_FIELD(arg0, s32 *, 8) - neg2_coord;
            temp_v1_3 = (func_80095BF0(&sp10, neg2_a1) << 0x10) >= M2C_FIELD(arg0, s32 *, 0);
            ASM_KEEP_NV(temp_v1_3);
            if (temp_v1_3 != 0) {
                goto call_a8;
            }
            goto block_57;
        }
        goto block_52;
    }
    }
block_52:
    {
    M2C_UNK *final_base;
    ASM_CLOBBER("$2");
    neg_page = (M2C_UNK *)D_80100000;
    ASM_KEEP_NV(neg_page);
block_52_low:
    final_base = (M2C_UNK *)((s8 *)neg_page - 0x1A40);
    ASM_KEEP_NV(final_base);
    if (M2C_FIELD(final_base, s32 *, 0xC) == 0) {
        goto check_final_y;
    }
    if (M2C_FIELD(final_base, s32 *, 0x10) != 0) {
        goto done;
    }

call_a8:
    func_800961A8(arg0);
    goto done;

check_final_y:
    if (M2C_FIELD(final_base, s32 *, 0x10) == 0) {
        goto done;
    }

block_57:
call_d8:
    func_800961D8(arg0);
    }

done:
    return;
}
