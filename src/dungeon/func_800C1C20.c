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

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 z;
} DungeonCoord;

typedef struct {
    u8 pad0[8];
    void *image;
    s32 color;
    s16 width;
    s16 pad12;
    s16 blend;
    u16 blend2;
    s16 shade;
    s16 pad1A;
    s16 size;
    s16 limit;
    s16 flags;
    u16 depth;
} DungeonRender;

typedef struct {
    void *parent;
    u8 pad4[9];
    s8 angle;
    u8 pad14[2];
    s16 mode;
    s16 value;
    u8 pad20[4];
    s16 height;
    s16 frame;
    s16 speed;
    s16 limit;
} DungeonState;

typedef struct {
    s32 arg1;
    u16 arg3_low;
    s32 arg3;
    s32 arg4;
} DungeonHomes;

typedef struct {
    u8 pad0[8];
    DungeonCoord *coord;
    DungeonRender *render;
    void *callback;
    u8 pad20[12];
    DungeonState state;
} DungeonObject;

extern void func_8003DB6C(void *, void *, s32);
extern DungeonObject *func_8003FD64(s32, void *);
extern void func_8004491C(DungeonObject *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u8 D_80045C34[];
extern u8 D_800777E8[];
extern u8 D_80083498[];
extern u8 D_800BB0A8[];
extern u8 D_800BB14C[];
extern u8 D_800D0774[];
extern u8 D_800DF3B4[];

DungeonObject *func_800C7380(s16 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4) {
    DungeonHomes homes;
    s32 color;
    DungeonObject *temp_s4;
    DungeonObject *temp_v0;
    DungeonState *var_s2;
    DungeonCoord *temp_s3;
    DungeonCoord *temp_s0;
    DungeonRender *temp_a2;
    void *temp_a0;
    s16 var_s7;
    s32 var_fp;
    s32 var_s6;

    homes.arg1 = arg1;
    homes.arg3 = arg3;
    homes.arg4 = arg4;
    temp_s4 = func_8003FD64(0x12, D_80083498);
    homes.arg3_low = (u16) homes.arg3;
    if (temp_s4 != NULL) {
        s16 var_s5;
        temp_s4->callback = D_800BB0A8;
        func_8004491C(temp_s4, D_80045C34);
        color = 0x404040;
        var_s2 = &temp_s4->state;
        var_fp = 0xB;
        var_s7 = -0xAA7;
        temp_s3 = temp_s4->coord;
        temp_s3->x = (s16) (((s32) (arg0 << 0x10) >> 0xA) + 0x20);
        var_s6 = 0xEA7;
        temp_s3->z = arg2;
        temp_s3->y = (s16) (((s32) (homes.arg1 << 0x10) >> 0xA) + 0x20);
        temp_a2 = temp_s4->render;
        temp_a2->image = D_800777E8;
        temp_a2->limit = 0x1800;
        temp_a2->size = 0x1800;
        temp_a2->width = 0x20;
        temp_a2->depth = 0xFFFB;
        temp_a2->color = color;
        temp_a2->flags = (s16) 0xFFFF;
        temp_a2->blend = (s16) (temp_a2->blend | 0xC);
        var_s5 = 0x37;
        var_s2->mode = arg0;
        var_s2->value = (u16) homes.arg1;
        var_s2->limit = 0x14;
        var_s2->height = (u16) homes.arg3;
        var_s2->speed = (u16) homes.arg4;
        do {
            temp_v0 = func_8003FD64(0x12, temp_s4);
            if (temp_v0 != NULL) {
                temp_v0->callback = D_800BB14C;
                func_8004491C(temp_v0, D_800D0774);
                temp_s0 = temp_v0->coord;
                temp_s0->x = (s16) (temp_s3->x + (func_80064584(var_s6) >> 7));
                temp_s0->y = (s16) (temp_s3->y + (func_800644B8(var_s6) >> 7));
                temp_s0->z = temp_s3->z;
                temp_a2 = temp_v0->render;
                temp_a2->blend2 = 0xFC00;
                temp_a2->shade = var_s7;
                temp_a2->size = 0x410;
                var_s2 = &temp_v0->state;
                if (var_s2->height < 0) {
                    temp_a2->width = 0x40;
                }
                temp_a0 = (void *) ((u8 *) temp_v0 + 0x24);
                var_s2->height = homes.arg3_low;
                temp_a2->image = temp_a0;
                func_8003DB6C(temp_a0, D_800DF3B4, 3);
                var_s2->angle = (s8) (var_s5 & 0xBF);
                var_s2->frame = var_s5;
                var_s2->parent = temp_s4;
            }
            var_s7 += 0x155;
            var_s6 -= 0x155;
            var_fp -= 1;
            var_s5 -= 5;
        } while (var_fp > 0);
    }
    return temp_s4;
}
