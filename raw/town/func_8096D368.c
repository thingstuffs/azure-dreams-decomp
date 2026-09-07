/* cfail-repair: tf7-phase1-cache-v3 */
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
#define M2C_BREAK() M2C_ERROR("break")
#define M2C_SYNC() M2C_ERROR("sync")

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

typedef struct SpriteFields {
    u32 pad0;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
} SpriteFields;

typedef struct DisplayPair {
    u32 pad0;
    SpriteFields *src;
    SpriteFields *dst;
} DisplayPair;

typedef struct TownSlots {
    void **slots[97];
    DisplayPair *display;
} TownSlots;

typedef struct TownObject {
    u8 pad0[4];
    s16 field4;
    s16 field6;
    u8 pad8[7];
    u8 digit;
    u8 row;
    u8 index;
    u8 column;
    u8 pad13[0x45];
    TownSlots *town;
} TownObject;

extern u8 func_80123200(u8 value);
extern void *D_801269D0[10];
extern s16 D_80126B24[8];
extern u8 D_80127B64[16];

void func_80125800(TownObject *obj) {
    s32 row8;
    s32 offset;
    s32 slot;
    s32 value;

    row8 = obj->row << 3;
    offset = (row8 + obj->column) * 3;
    slot = offset + 33;
    value = (obj->digit << 4) + row8 + obj->column;
    if (func_80123200((u8)value) != 0) {
        s32 number = value + 1;

        *obj->town->slots[slot] = (void *)D_80127B64;
        slot = offset + 34;
        *obj->town->slots[slot] = D_801269D0[number / 10];
        slot = offset + 35;
        *obj->town->slots[slot] = D_801269D0[number % 10];
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(obj, void **, 0x58), void **, 0x184), void **, 4), s16 *, 0xA) = (s16) ((u16) D_80126B24[M2C_FIELD(obj, u8 *, 0x12) & 7] + (((s32) (D_80126B24[M2C_FIELD(obj, u8 *, 0x11) & 7] - D_80126B24[M2C_FIELD(obj, u8 *, 0x12) & 7]) / (s16) M2C_FIELD(obj, s16 *, 6)) * M2C_FIELD(obj, s16 *, 4)));
}
