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

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

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

M2C_UNK func_8003DB94();  /* extern */
s32 func_8003DE58(void *, void *, Vec3u16 *, s32);     /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047738();              /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern s32 D_80045340[];
extern s32 D_800814A0;
extern s16 D_80083228[];
extern s32 D_800D586C[];
extern s32 D_800DE870[];

void func_800D58D8(void *arg0, void *arg1, void *arg2) {
    Vec3u16 delta;
    s16 temp_s0;
    void *temp_v0;
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_a1;
    void *temp_s0_2;
    void *temp_v0_3;

    temp_s0 = ((s32) (D_80083228[0] + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7;
    if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0) {
        temp_v0 = M2C_FIELD(arg2, s32 *, 0x2C);
        if (temp_v0 != 0) {
            func_80047738(arg2, *((u8 *)temp_v0 + temp_s0), M2C_FIELD(arg2, s8 *, 4));
        }
        M2C_FIELD(arg0, s16 *, 0x94) = temp_s0;
    }
    func_800478B8(arg2);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        temp_v0_3 = func_8003FC64(0x12);
        if (temp_v0_3 != NULL) {
            func_8004491C(temp_v0_3, &D_80045340);
            temp_a0 = M2C_FIELD(temp_v0_3, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
            temp_s0_2 = M2C_FIELD(temp_v0_3, void **, 8);
            M2C_FIELD(temp_s0_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
            M2C_FIELD(temp_s0_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
            M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
            temp_a0 = M2C_FIELD(temp_v0_3, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1800;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1800;
            M2C_FIELD(temp_a0, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_a0, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_a0, u8 *, 0xC) = 0x80;
            M2C_FIELD(temp_a0, u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 6);
            M2C_FIELD(temp_v0_3, M2C_UNK **, 0x10) = &D_800D586C;
            temp_a1 = M2C_FIELD(arg0, void **, -0x14);
            if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &delta, 0) != 0) {
                M2C_FIELD(temp_s0_2, u16 *, 2) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 2) + delta.x);
                M2C_FIELD(temp_s0_2, u16 *, 6) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 6) + delta.y);
                M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0xA) + delta.z);
            }
            func_8003DB94(M2C_FIELD(temp_v0_3, void **, 0xC), &D_800DE870, 0);
        }
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A six-byte Vec3u16 output object forces the retail 0x30 frame and s0-s4 save set.
   Reusing temp_a0 across disjoint render-pointer live ranges colors both reloads as $a0.
   A scalar global RMW removes the displacement cascade; u8 stores materialize positive 0x80. */
