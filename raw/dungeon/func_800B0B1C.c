/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() 0
#define M2C_SYNC() 0
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef s32 (*D_800DF2A8_fn)(void *, s16, s32);
extern D_800DF2A8_fn D_800DF2A8[];
extern u8 D_800E3D40[16];

typedef struct {
    u16 pad0;
    u16 field2;
    u8 pad2[8];
} D_80083460_t;

extern D_80083460_t D_80083460;
extern u8 D_800E3648[16];
extern s32 D_800DF258[16];

typedef struct {
    u8 pad[0x14];
    u16 flags;
    u8 pad2[2];
} StatusEntry;

extern StatusEntry D_800E39C8[];

extern void func_80099F70(s32);
extern void func_80099F04(s32);
extern s32 func_8003DB94(void *, s32, s32);

typedef struct {
    u8 pad[0x5C];
    s32 unk5C;
} Arg1Struct;

s32 func_800B627C(s32 arg0, void *arg1, s32 arg2, s8 arg3) {
    u8 *state = D_800E3D40;
    s32 temp_v0;
    StatusEntry *temp_s0;
    Arg1Struct *object = (Arg1Struct *) arg1;
    u8 *slot_base;
    s16 index = arg2;

    state[0] = arg3;
    temp_v0 = D_800DF2A8[(s16) arg0](object, index, arg2 << 0x10);
    if (temp_v0 != 0) {
        if (state[0] != 0) {
            func_80099F70(object->unk5C);
            func_80099F04(object->unk5C);
            D_80083460.field2 |= 0x812;
        }
        slot_base = (u8 *) D_800E39C8;
        temp_s0 = (StatusEntry *) (slot_base + index * 0x18);
        if (temp_s0->flags & 0x40) {
            func_8003DB94(temp_s0, D_800DF258[D_800E3648[index * 4]], 0);
            temp_s0->flags &= 0xF7FF;
        }
    }
    return temp_v0;
}
