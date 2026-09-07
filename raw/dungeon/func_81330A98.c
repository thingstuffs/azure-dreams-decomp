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

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;
extern M2C_UNK D_80167A2C;
extern PositionTableEntry D_80175DD8[];

void func_80167A98(void *arg0, void *arg1) {
    void *temp_a1;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80167A2C;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, s16 *, 6) = 0;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, s32 *, 0) = M2C_FIELD(arg1, s32 *, 0) + (D_80175DD8[M2C_FIELD(arg0, s16 *, 0x1C)].x << 0x11);
        M2C_FIELD(temp_a1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4) + (D_80175DD8[M2C_FIELD(arg0, s16 *, 0x1C)].y << 0x11);
        M2C_FIELD(temp_a1, s32 *, 8) = M2C_FIELD(arg1, s32 *, 8) + (D_80175DD8[M2C_FIELD(arg0, s16 *, 0x1C)].z << 0x11);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        if (M2C_FIELD(arg0, s16 *, 0x1C) == 0) {
            func_8003DB94(temp_s0, &D_800DE870, 0);
        }
        if (M2C_FIELD(arg0, s16 *, 0x1C) == 1) {
            func_8003DB94(temp_s0, &D_800DEE38, 0);
        }
        if (M2C_FIELD(arg0, s16 *, 0x1C) == 2) {
            func_8003DB94(temp_s0, &D_800DEDB0, 0);
        }
    }
}
/* MECHANISM: One reassigned temp_s0 spans both object-load regions, naturally forcing
   retail's 0x28 frame and s0-s3 hold set. A 0x60 signed-halfword table restores the
   index/load sequence, and u8 fields preserve the 0x80 materialization. */
