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
extern s32 D_800BA6B8;
void func_800403BC(s32 *);                  /* extern */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
typedef struct S_8006DE24_Entry {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} S_8006DE24_Entry;
extern S_8006DE24_Entry D_8006DE24[];
void func_800BA764(u16, u16, s16, u32);      /* extern */
s16 func_800BCB04();                   /* extern */
typedef struct S_800B50B0_Entity {
    u8 pad00[0x13];
    u8 kind13;
    u8 pad14[0x16];
    u16 angle2a;
    u8 pad2c[0x1c];
    u8 kind48;
    u8 pad49[0x17];
    void *child60;
    u8 pad64[0x24];
    s16 height88;
} S_800B50B0_Entity;
extern S_800B50B0_Entity *D_800DF374;
extern u16 D_800DF378;
extern u16 D_800DF37A;
extern u8 D_800DF380[];

void func_800BA810(S_800B50B0_Entity *arg0, s16 arg1) {
    s32 temp_s0;
    s16 var_a2;
    s16 var_a2_2;
    s16 var_a2_3;
    register s32 *var_a0 ASM_REG("$4");
    register s32 temp_a2;
    register s32 temp_a1 ASM_REG("$5");
    register s32 temp_entry ASM_REG("$2");
    register s32 temp_mode ASM_REG("$3");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s1_2 ASM_REG("$17");
    register s32 var_s1_3 ASM_REG("$17");
    u32 var_s2;
    u32 var_s3;
    u8 temp_a0;
    u8 temp_v1_2;
    u16 temp_angle;
    void *temp_a0_2;
    void *temp_v0_4;
    void *temp_v1;

    if (arg0 == NULL) {
        D_800DF374 = NULL;
        func_800403BC(&D_800BA6B8);
        return;
    }
    if (D_800DF374 == arg0) {
        ASM_KEEP_NV(arg1);
        if (D_800DF37A == (s16) arg0->angle2a) {
            var_a0 = &D_800BA6B8;
            if (D_800DF378 != (arg1 & 0xFFFF)) {
                goto block_6;
            }
        } else {
            var_a0 = &D_800BA6B8;
            goto block_7;
        }
    } else {
block_6:
        var_a0 = &D_800BA6B8;
block_7:
        temp_angle = arg0->angle2a;
        do { D_800DF374 = arg0; } while (0);
        ASM_KEEP_NV(arg1);
        D_800DF378 = arg1;
        ASM_KEEP_NV(arg1);
        D_800DF37A = temp_angle;
        func_800403BC(var_a0);
        do { temp_a1 = arg1 & 0x3FFF; } while (0);
        ASM_KEEP_NV(temp_a1);
        temp_v1 = M2C_FIELD(arg0, void **, -0x18);
        temp_s0 = arg0->height88;
        temp_entry = (u16) M2C_FIELD(temp_v1, u16 *, 2);
        var_s3 = (u32) temp_entry >> 6;
        var_s2 = (u16) M2C_FIELD(temp_v1, u16 *, 6) >> 6;
        temp_mode = temp_a1;
        temp_a2 = (arg0->angle2a >> 9) & 7;
        if (temp_mode == 8) {
            var_s1 = 1;
            if ((arg0->kind13 == 0x16) && (arg0->kind48 == 0xF)) {
                var_s1 = 0xA;
            }
            if (var_s1 > 0) {
                do {
                    var_a2 = temp_s0 - 0x20;
                    var_s3 += (s16) D_8006CCD8[temp_a2];
                    var_s2 += (s16) D_8006CCE8[temp_a2];
                    temp_s0 = func_800BCB04(((var_s3 << 6) + 0x20) & 0xFFE0, ((var_s2 << 6) + 0x20) & 0xFFE0, var_a2);
                    if (temp_s0 >= 0x201) {
                        break;
                    }
                    func_800BA764(var_s3 & 0xFFFF, var_s2 & 0xFFFF, temp_s0, 0xFF);
                    var_s1 -= 1;
                } while (var_s1 > 0);
            } else {
                return;
            }
            return;
        }
        if (temp_mode == 11) {
            var_s1_2 = 1;
            do {
                var_a2_2 = temp_s0 - 0x20;
                var_s3 += (s16) D_8006CCD8[temp_a2];
                var_s2 += (s16) D_8006CCE8[temp_a2];
                temp_s0 = func_800BCB04(((var_s3 << 6) + 0x20) & 0xFFE0, ((var_s2 << 6) + 0x20) & 0xFFE0, var_a2_2);
                if (temp_s0 >= 0x201) {
                    break;
                }
                func_800BA764(var_s3 & 0xFFFF, var_s2 & 0xFFFF, temp_s0, 0xFF00);
                var_s1_2 -= 1;
            } while (var_s1_2 > 0);
            return;
        }
        if (temp_mode == 12) {
            func_800BA764(var_s3 & 0xFFFF, var_s2 & 0xFFFF, temp_s0, 0xFFFF);
            return;
        }
        temp_entry = temp_a1;
        temp_entry -= 1;
        if ((u32) temp_entry >= 3U) {
            return;
        }
        temp_mode -= 1;
        temp_entry = temp_mode * 3;
        temp_a0 = *((u8 *) arg0 + temp_entry + 8);
        temp_v1_2 = D_8006DE24[temp_a0].type;
        if (temp_v1_2 == 1) {
            temp_entry = D_800DF380[temp_a0];
            var_s1_3 = temp_entry & 0x1F;
            if (var_s1_3 > 0) {
                do {
                    var_a2_3 = temp_s0 - 0x20;
                    var_s3 += (s16) D_8006CCD8[temp_a2];
                    var_s2 += (s16) D_8006CCE8[temp_a2];
                    temp_s0 = func_800BCB04(((var_s3 << 6) + 0x20) & 0xFFE0, ((var_s2 << 6) + 0x20) & 0xFFE0, var_a2_3);
                    if (temp_s0 >= 0x201) {
                        break;
                    }
                    func_800BA764(var_s3 & 0xFFFF, var_s2 & 0xFFFF, temp_s0, 0xFF);
                    var_s1_3 -= 1;
                } while (var_s1_3 > 0);
            }
        } else if (temp_v1_2 == 2) {
            temp_a0_2 = arg0->child60;
            if (temp_a0_2 != NULL) {
                temp_v0_4 = M2C_FIELD(temp_a0_2, void **, -0x18);
                func_800BA764((u16) M2C_FIELD(temp_v0_4, u16 *, 2) >> 6, (u16) M2C_FIELD(temp_v0_4, u16 *, 6) >> 6, ((S_800B50B0_Entity *)temp_a0_2)->height88, 0xFF);
            }
        }
    }
}
/* Warning: struct S_8006DE24_Entry is not defined (only forward-declared) */
