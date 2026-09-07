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

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80099FDC();                      /* extern */
M2C_UNK func_8009A21C();             /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A2B04();              /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D2664;
extern M2C_UNK D_800D28E4;
extern M2C_UNK D_800E221C;

void *func_800D24A8(s16 arg0, u8 arg1, u8 arg2, s16 arg3) {
    M2C_UNK var_a2;
    register s16 hold_arg0 ASM_REG("$16");
    register void *temp_s0 ASM_REG("$16");
    register void *temp_s1 ASM_REG("$17");
    register void *temp_v0 ASM_REG("$19");
    register void *var_s2 ASM_REG("$18");
    register u8 hold_arg1 ASM_REG("$22");
    register s16 hold_arg3 ASM_REG("$20");
    register u8 hold_arg2 ASM_REG("$21");
    register s32 kind ASM_REG("$2");
    u8 call_x;
    u8 call_y;

    hold_arg0 = arg0;
    var_s2 = NULL;
    hold_arg1 = arg1;
    hold_arg3 = arg3;
    hold_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s2 = temp_v0 + 0x20;
        M2C_FIELD(var_s2, s8 *, 0x13) = 0x34;
        kind = (s16) hold_arg0;
        if (kind == 1) {
            M2C_FIELD(var_s2, s32 *, 0x14) = (s32) (M2C_FIELD(var_s2, s32 *, 0x14) | 0x2000);
            M2C_FIELD(var_s2, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s2, s32 *, 0x1C) | 0x2000);
        }
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, s16 *, 0xA) = hold_arg3;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, M2C_UNK **, 8) = &D_800E221C;
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1400;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1400;
        M2C_FIELD(temp_s0, u8 *, 0x24) = hold_arg1;
        M2C_FIELD(temp_s0, u8 *, 0x25) = hold_arg2;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800D2664;
        M2C_FIELD(var_s2, M2C_UNK **, 0x8C) = &D_800D28E4;
        M2C_FIELD(temp_s0, s8 *, 0x26) = func_8009FB34(M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25));
        func_800A2B04(temp_s1, M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25));
        M2C_FIELD(var_s2, s16 *, 0x88) = func_800BCB04(M2C_FIELD(temp_s1, u16 *, 2), M2C_FIELD(temp_s1, u16 *, 6), M2C_FIELD(temp_s1, s16 *, 0xA));
        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x2C808080;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x8000);
        func_80099FDC(temp_v0);
        call_x = M2C_FIELD(temp_s0, u8 *, 0x24);
        call_y = M2C_FIELD(temp_s0, u8 *, 0x25);
        var_a2 = 0x3000;
        if (M2C_FIELD(var_s2, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A21C(call_x, call_y, var_a2);
        M2C_FIELD(var_s2, s8 *, 0x9A) = 0xE;
        M2C_FIELD(var_s2, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s2, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s2, s32 *, 0x1C) | 0x40000200);
    }
    return var_s2;
}
/* MECHANISM: The exact 0x30 frame comes from one named live range for each
   retail s0/s2/s6/s4/s5/s3/s1 role, with s0 reused for the later object base.
   Preloading call bytes removes the displacement cascade; u8 color fields and
   the 2.7.2-cdk-G0 scheduler produce the final literal and load-slot ordering. */
