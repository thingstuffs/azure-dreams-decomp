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

/* D_80083160: shared state table. offset 0x1DC holds a pointer to the
 * dungeon map cell array (6-byte cells, first s16 field is the cell
 * "type"); offset 0x1F0 (0x1DC+0x14) holds a s16 shift value used to
 * compute the row stride (row index << shift). Local (own-view)
 * declaration per merge-safety contract -- only a raw byte-offset
 * view is needed here (matches the field access shape in the asm,
 * base symbol used with explicit sub-offsets, not folded). */
typedef struct {
    u8 pad0[0x1DC];
    void *mapPtrField;  /* offset 0x1DC */
} S_800999DC_D80083160;

extern S_800999DC_D80083160 D_80083160;

extern void func_8009EEAC(void);
extern void func_8009F3D4(s16 x, s16 y, s32 color, s32 size, s32 count);

typedef struct {
    u16 type;
    s8 unk2[4];
} MapCell;

void func_8009F13C(void) {
    MapCell *mapPtr;
    u8 *shiftBase;
    s32 var_s0;
    s32 var_s1;
    s32 count;

    mapPtr = (MapCell *)D_80083160.mapPtrField;
    shiftBase = (u8 *)&D_80083160.mapPtrField;
    func_8009EEAC();
    count = 0;
    var_s1 = 1;
    do {
        var_s0 = 1;
        do {
            if (mapPtr[var_s0 + (var_s1 << *(s16 *)(shiftBase + 0x14))].type == 3) {
                func_8009F3D4(var_s0, var_s1, 0x808080, 0x10, count);
                count += 1;
            }
            var_s0 += 1;
        } while (var_s0 < 0x3F);
        var_s1 += 1;
    } while (var_s1 < 0x3F);
}
