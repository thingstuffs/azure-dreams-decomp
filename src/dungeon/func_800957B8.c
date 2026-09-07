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

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0A[0xA];
    s16 height;
} FuncArg1;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern void *D_800E3D7C;
s32 func_8009A350();            /* extern */
s32 func_8009B128();                          /* extern */
s32 func_8009B12C();                                /* extern */
void *func_8009B25C();           /* extern */
s32 func_800A0548();                        /* extern */
s16 func_800BCB04();                   /* extern */
extern s8 D_800DD7DC;

s32 func_8009AF18(u32 arg0, FuncArg1 *arg1, void *arg2, u16 arg3) {
    u16 sp10[5];
    u16 *sp20;
    s32 temp_base;
    register s32 temp_a2 ASM_REG("$6");
    s32 temp_fp;
    register s32 temp_s2;
    s32 temp_v1;
    s32 temp_s1;
    register s32 var_s5 ASM_REG("$21");
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s4 ASM_REG("$20");
    void *temp_v0;

    var_s5 = 1;
    ASM_KEEP_NV(var_s5);
    D_800DD7DC = 0;
    var_s3 = M2C_FIELD(arg2, u8 *, 0x24);
    var_s4 = M2C_FIELD(arg2, u8 *, 0x25);
    temp_a2 = (arg0 >> 9) & 7;
    sp10[4] = arg3;
    var_s7 = (var_s3 << 6) | 0x20;
    var_s6 = (var_s4 << 6) | 0x20;
    if ((arg3 << 0x10) > 0) {
        temp_fp = temp_a2;
        temp_base = (s32)D_8006CCD8;
        temp_s2 = temp_fp << 1;
        sp20 = (u16 *)(temp_base + temp_s2);
loop_2:
        temp_s1 = (s16) var_s3;
        if (func_800A0548(temp_s1, (s16) var_s4) != 0) {
            register s32 tail_value ASM_REG("$2");
            tail_value = (var_s5 - 1) << 0x10;
            ASM_TAILSLOT_PIN(tail_value);
            return func_8009B12C();
        }
        if ((func_8009A350(temp_s1, (s16) var_s4, temp_fp, sp10) << 0x10) == 0) {
            goto call_fail;
        }
        var_s3 += *sp20;
            var_s4 += *(u16 *)((u8 *)D_8006CCE8 + temp_s2);
            if (sp10[0] & 0x3300) {
                {
                    extern void *D_800E3D7C;
                    temp_v0 = func_8009B25C(D_800E3D7C, var_s3 & 0xFFFF, var_s4 & 0xFFFF, M2C_FIELD(D_800E3D7C, s16 *, 0x88));
                    ASM_CLOBBER("$16");
                }
                if (temp_v0 != NULL) {
                    var_v0 = var_s5 << 0x10;
                    if (M2C_FIELD(temp_v0, u8 *, 0x13) == 0x1F) {
                        var_v0 = var_s5 << 0x10;
                        if (!(M2C_FIELD(temp_v0, s32 *, 0x1C) & 0x228)) {
                            var_v0 = var_s5 << 0x10;
                            {
                                if (M2C_FIELD(M2C_FIELD(D_800E3D7C, void **, 0x124), s8 *, 0x13) < 0) {
                                D_800DD7DC = 1;
                                M2C_FIELD(temp_v0, s32 *, 0x14) |= 0x800000;
                                return func_8009B128(temp_v0);
                                }
                            }
                        }
                    }
                    /* Duplicate return node #20. Try simplifying control flow for better match */
                    return (s16)var_s5;
                }
                goto block_19;
            }
            var_s7 += *(u16 *)((u8 *)D_800DCEAC + temp_s2);
            var_s6 += *(u16 *)((u8 *)D_800DCEBC + temp_s2);
            temp_v1 = var_s5 + 1;
            if (func_800BCB04(var_s7 & 0xFFFF, var_s6 & 0xFFFF, arg1->height) < 0x200) {
                goto loop_increment;
            }
            {
                register s32 tail_value ASM_REG("$2");
                tail_value = (var_s5 - 1) << 0x10;
                ASM_TAILSLOT_PIN(tail_value);
                return func_8009B12C();
            }
call_fail:
            {
                register s32 tail_value ASM_REG("$2");
                tail_value = (var_s5 - 1) << 0x10;
                ASM_TAILSLOT_PIN(tail_value);
            }
            return func_8009B12C();
loop_increment:
            var_s5 = temp_v1;
            if ((sp10[4] << 0x10) >= (temp_v1 << 0x10)) {
                goto loop_2;
            }
            goto block_19;
    }
block_19:
    var_v0 = var_s5 << 0x10;
    return var_v0 >> 0x10;
}
