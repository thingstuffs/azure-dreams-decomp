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

M2C_UNK func_80048A44(); /* extern */
s32 func_80094F74();  /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s16 D_80083464;
extern void *D_80088810[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD040[];
extern u8 D_800DD058[];

void func_8008E264(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const sw_keep[13] = {
        &&case_0, &&case_1, &&case_default, &&case_default,
        &&case_default, &&case_default, &&case_default, &&case_default,
        &&case_0, &&case_1, &&case_0, &&case_1, &&case_12
    };
    s16 temp_v0;
    register s32 delta_v1 ASM_REG("$3");
    register s32 var_v0 ASM_REG("$2");
    u32 swi;
    u8 *state_base0;
    u8 *state_base1;
    u8 temp_v1;
    s32 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    swi = temp_v1;
    if (swi >= 13) {
        goto case_default;
    }
    (void)sw_keep;
    goto *D_80088810[swi];
case_0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x9B);
            if (temp_v1_2 != 0) {
                goto temp_nonzero;
            }
            ASM_KEEP(temp_v1_2);
            var_v0 = 0xFFF00000;
            goto temp_join;
temp_nonzero:
            var_v0 = 8;
            if (temp_v1_2 != var_v0) {
                var_v0 = 0xFFEC0000;
                goto temp_join;
            }
            var_v0 = 0xFFF80000;
temp_join:
            ASM_KEEP(var_v0);
            M2C_FIELD(arg1, s32 *, 0x14) = var_v0;
            func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
            func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
            state_base0 = (u8 *)&D_80083460;
            M2C_FIELD(state_base0, u16 *, 2) = (u16) (M2C_FIELD(state_base0, u16 *, 2) | 0x812);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
            M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD040;
            func_80048A44(arg2, D_800DD040[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800A56E0(0x50A);
            return;
        }
case_default:
        return;
case_1:
        state_base1 = (u8 *)&D_80083460;
        if (M2C_FIELD(state_base1, s16 *, 4) != 0) {
            var_v0 = M2C_FIELD(arg2, u8 *, 0x24) << 6;
            delta_v1 = M2C_FIELD(arg1, s16 *, 2);
            delta_v1 -= 0x20;
            var_v0 = (var_v0 - delta_v1) << 0x10;
            M2C_FIELD(arg1, s32 *, 0xC) = var_v0 / M2C_FIELD(state_base1, s16 *, 4);
            delta_v1 = M2C_FIELD(arg1, s16 *, 6);
            var_v0 = M2C_FIELD(arg2, u8 *, 0x25);
            ASM_KEEP(delta_v1);
            delta_v1 -= 0x20;
            var_v0 <<= 6;
            var_v0 -= delta_v1;
            ASM_MEM_BARRIER();
            delta_v1 = M2C_FIELD(state_base1, s16 *, 4);
            var_v0 <<= 0x10;
            M2C_FIELD(arg1, s32 *, 0x10) = var_v0 / delta_v1;
        }
        temp_v0 = (u16) M2C_FIELD(state_base1, s16 *, 4) - 1;
        M2C_FIELD(state_base1, s16 *, 4) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(state_base1, s16 *, 4) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if ((u8) M2C_FIELD(arg0, u8 *, 0x9B) >= 0xAU) {
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD058;
                func_80048A44(arg2, D_800DD058[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0, 1);
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                M2C_FIELD(state_base1, s16 *, 4) = 1;
                return;
            }
            goto block_15;
        }
        return;
case_12:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            D_80083464 = 0;
            goto block_15;
        }
        return;
block_15:
        if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
        }
}

/* MECHANISM: External jump-table dispatch and two distinct D_80083460 base live ranges fixed layout.
   A widened selector fence plus guarded v0/v1 pins preserved the retail inner CFG and divide roles.
   Moving case 12 before the shared join and fencing the divisor reload closed the final schedule. */
