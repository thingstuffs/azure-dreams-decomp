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
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    u16 fieldA;
    u8 padC[0x18];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    void *field2C;
} Func812A5000Child;

typedef struct {
    u8 pad0[8];
    Func812A5000Child *child1;
    Func812A5000Child *child0;
    void *field10;
} Func812A5000Parent;

typedef struct {
    u8 pad0[0x13];
    u8 field13;
    u32 field14;
    u8 pad18[4];
    u32 field1C;
    u8 pad20[0xA];
    s16 field2A;
    u8 pad2C[0x60];
    void *field8C;
    u8 pad90[2];
    s16 field92;
    u8 pad94[6];
    u8 field9A;
    u8 pad9B;
    s8 field9C;
} Func812A5000Entity;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80175C30[];
extern u8 D_80171FA4[];
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_800A9C18(); /* extern */
M2C_UNK func_800AA36C(); /* extern */
s32 func_800F6D28();                          /* extern */
extern volatile void *D_800FBE1C[];
extern u8 D_80170A4C[];

void *func_812A50AC(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    Func812A5000Parent *parent;
    Func812A5000Child *child0;
    Func812A5000Child *child1;
    Func812A5000Entity *entity;

    entity = NULL;
    parent = func_8003FD64(0x112, D_80083498);
    if (parent != NULL) {
        if (D_800FBE1C[0] == 0) {
            D_800FBE1C[0] = parent;
        }
        entity = (Func812A5000Entity *)((u8 *)parent + 0x20);
        parent->field10 = D_80170A4C;
        entity->field13 = 0x39;
        func_8004491C(parent, D_80045340);
        child0 = parent->child0;
        child1 = parent->child1;
        child0->field24 = arg1;
        child0->field25 = arg2;
        child0->field2C = D_80175C30;
        child1->field2 = (s16)((child0->field24 << 6) + 0x20);
        child1->field6 = (s16)((child0->field25 << 6) + 0x20);
        child1->fieldA = arg3;
        entity->field2A = (s16)(func_800F6D28(child1) << 9);
        entity->field13 = 2;
        entity->field14 |= 0x6000;
        entity->field1C |= 0x6000;
        func_800A9C18(parent, child1, child0, arg0);
        entity->field9A = 0xFF;
        entity->field9C = -1;
        entity->field8C = D_80171FA4;
        entity->field92 = -0x20;
        entity->field13 = 0x39;
        entity->field1C |= 0x40000;
        func_800AA36C(entity, child1, child0, entity);
    }
    return entity;
}
