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

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                 /* extern */
extern M2C_UNK D_80170CEC;
extern M2C_UNK D_80170E2C;

void func_80171790(void *arg0, void *arg1) {
    void *saved_arg0;
    void *saved_arg1;
    register s32 saved_obj_angle ASM_REG("$18");
    register s32 saved_data_scale ASM_REG("$17");
    register void *saved_tail ASM_REG("$16");
    register void *init_obj ASM_REG("$4");
    void *copy_dst;
    u8 byte1;
    u8 byte2;

    saved_arg0 = arg0;
    saved_arg1 = arg1;
    saved_obj_angle = (s32) func_8003FC64(0x212);
    if (saved_obj_angle != 0) {
        init_obj = (void *) saved_obj_angle;
        saved_tail = (void *) saved_obj_angle + 0x20;
        ASM_KEEP(saved_tail);
        M2C_FIELD(saved_tail, s16 *, 0x18) = 6;
        M2C_FIELD(saved_tail, s16 *, 0x1A) = 6;
        M2C_FIELD((void *) saved_obj_angle, M2C_UNK **, 0x10) = &D_80170E2C;
        func_8004491C(init_obj, &D_80170CEC);
        saved_data_scale = (s32) M2C_FIELD((void *) saved_obj_angle, void **, 0xC);
        M2C_FIELD((void *) saved_data_scale, s16 *, 0x10) = 0x60;
        M2C_FIELD((void *) saved_data_scale, u16 *, 0x14) =
            (u16) (M2C_FIELD((void *) saved_data_scale, u16 *, 0x14) | 0xC);
        copy_dst = M2C_FIELD((void *) saved_obj_angle, void **, 8);
        M2C_FIELD(copy_dst, u16 *, 2) = M2C_FIELD(saved_arg1, u16 *, 2);
        M2C_FIELD(copy_dst, u16 *, 6) = M2C_FIELD(saved_arg1, u16 *, 6);
        M2C_FIELD(copy_dst, s16 *, 0xA) =
            (s16) (M2C_FIELD(saved_arg1, u16 *, 0xA) - 0x50);
        saved_data_scale = (s32) M2C_FIELD((void *) saved_obj_angle, void **, 0xC);
        M2C_FIELD((void *) saved_data_scale, s16 *, 0x1E) = 0x1000;
        M2C_FIELD((void *) saved_data_scale, s16 *, 0x1C) = 0x1000;
        M2C_FIELD((void *) saved_data_scale, u8 *, 0xC) = rand();
        M2C_FIELD((void *) saved_data_scale, u8 *, 0xD) = rand();
        M2C_FIELD((void *) saved_data_scale, u8 *, 0xE) = rand();
        M2C_FIELD((void *) saved_obj_angle, u8 *, 0x20) =
            M2C_FIELD((void *) saved_data_scale, u8 *, 0xC);
        byte1 = M2C_FIELD((void *) saved_data_scale, u8 *, 0xD);
        ASM_SCHED_BARRIER();
        M2C_FIELD(saved_tail, u8 *, 1) = byte1;
        ASM_SCHED_BARRIER();
        byte2 = M2C_FIELD((void *) saved_data_scale, u8 *, 0xE);
        M2C_FIELD(saved_tail, s16 *, 0x60) = 0;
        M2C_FIELD(saved_tail, s16 *, 0x5C) = 0;
        M2C_FIELD(saved_tail, s16 *, 0x58) = 0;
        M2C_FIELD(saved_tail, u8 *, 2) = byte2;
        saved_obj_angle = rand() & 0xFFF;
        saved_data_scale =
            (M2C_FIELD(saved_arg0, s16 *, 0xAE) * func_80064584(saved_obj_angle)) >> 0xC;
        M2C_FIELD(saved_tail, s16 *, 0x62) =
            (M2C_FIELD(saved_arg0, s16 *, 0xAE) * func_800644B8(saved_obj_angle)) >> 0xC;
        saved_obj_angle = rand() & 0xFFF;
        M2C_FIELD(saved_tail, s16 *, 0x5A) =
            (saved_data_scale * func_80064584(saved_obj_angle)) >> 0xC;
        M2C_FIELD(saved_tail, s16 *, 0x5E) =
            (saved_data_scale * func_800644B8(saved_obj_angle)) >> 0xC;
    }
}

/* MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
   reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body.
   Two scheduler seams retain the byte1 load-delay nop, while a split byte2 live range hoists its lbu. */
