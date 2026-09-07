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

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();                  /* extern */
extern s16 D_80083D78[];

void func_800B5B20(void *arg0) {
    s32 table_index;
    volatile s16 sp10;
    volatile s16 sp12;
    volatile s16 sp14;
    volatile s16 sp16;
    void *temp_s1 = arg0;
    void *temp_s0;
    s16 *table_a0;

    
    if (M2C_FIELD(temp_s1, s32 *, 0xD4) != 0) {
        func_80067014(0);
        table_a0 = D_80083D78;
        table_index = M2C_FIELD(temp_s1, s16 *, 8);
        temp_s0 = M2C_FIELD(temp_s1, void * volatile *, 0x14);
        M2C_FIELD(temp_s1, s32 *, 0xD0) = 0;
        M2C_FIELD(temp_s1, s32 *, 0xD4) = 0;
        table_a0[table_index * 2] = M2C_FIELD(temp_s1, u16 *, 0xA);
        table_a0[(M2C_FIELD(temp_s1, s16 *, 8) * 2) + 1] = M2C_FIELD(temp_s1, u16 *, 0x10);
        
        sp10 = ((u8) M2C_FIELD(temp_s0, u8 *, 8) >> 2) + ((M2C_FIELD(temp_s0, u16 *, 4) << 6) & 0x3C0);
        sp12 = M2C_FIELD(temp_s0, u8 *, 9) + ((M2C_FIELD(temp_s0, u16 *, 4) * 0x10) & 0x100);
        sp14 = (s16) ((u8) M2C_FIELD(temp_s0, u8 *, 0xA) >> 2);
        sp16 = (s16) M2C_FIELD(temp_s0, u8 *, 0xB);
        func_800672D8(&sp10, M2C_FIELD(temp_s1, s32 *, 0xE0));
        if (M2C_FIELD(temp_s1, s16 *, 8) != 0) {
            volatile s16 *sp10_a0 = &sp10;
            u16 temp_v1;
            s32 offset_a1;
            s32 base_v0;

            
            sp10 = (M2C_FIELD(temp_s0, u16 *, 6) & 0x3F) * 0x10;
            temp_v1 = M2C_FIELD(temp_s0, u16 *, 6);
            sp14 = 0x10;
            sp16 = 1;
            temp_v1 >>= 6;
            sp12 = (s16) temp_v1;
            
            offset_a1 = M2C_FIELD(temp_s1, s32 *, 0x10);
            base_v0 = M2C_FIELD(temp_s1, s32 *, 0xE0);
            offset_a1 <<= 5;
            offset_a1 += 0x200;
            
            func_800672D8(sp10_a0, base_v0 + offset_a1);
        }
        func_80067014(0);
    }
    M2C_FIELD(temp_s1, s32 *, 0xE0) = 0;
}

/* MECHANISM: Four volatile s16 frame objects preserve the 0x28 frame and all sibling stores.
   arg0 stays pinned in s1 while the cross-call nested pointer allocates naturally to s0.
   Pinned table/a0 and split v1/a1 live ranges reproduce the table, branch-slot, and tail order. */
