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

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800672D8();              /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801747B8;

void func_80174910(void *arg0, s32 arg1) {
    u16 sp10[4];                                    /* compiler-managed */
    s16 temp_v0_5;
    s32 var_s1;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_6;
    u8 entry_flags;
    u8 *var_v1;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *object_callback;
    u8 *callback_page;

    var_s1 = 0;
    object_callback = &D_801747B8;
    callback_page = (u8 *) 0x80170000;
    do {
        temp_v0 = func_8003FD64(0x12, arg0);
        temp_v1 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, void **, 0x10) = object_callback;
            M2C_FIELD(temp_v1, void **, 0x18) = (void *) M2C_FIELD(arg0, void **, 0xC);
            M2C_FIELD(temp_v1, void **, 0x1C) = (void *) M2C_FIELD(arg0, void **, 8);
            temp_v0_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
            M2C_FIELD(temp_v1, u16 *, 0x24) = temp_v0_2;
            M2C_FIELD(temp_v1, u16 *, 0x22) = temp_v0_2;
            M2C_FIELD(temp_v1, u16 *, 0x20) = temp_v0_2;
            temp_v0_3 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
            M2C_FIELD(temp_v1, u16 *, 0x2A) = temp_v0_3;
            M2C_FIELD(temp_v1, u16 *, 0x28) = temp_v0_3;
            M2C_FIELD(temp_v1, u16 *, 0x26) = temp_v0_3;
            temp_v0_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
            M2C_FIELD(temp_v1, s32 *, 0xC) = arg1;
            M2C_FIELD(temp_v1, s16 *, 0x34) = var_s1;
            M2C_FIELD(temp_v1, u16 *, 0x30) = temp_v0_4;
            M2C_FIELD(temp_v1, u16 *, 0x2E) = temp_v0_4;
            M2C_FIELD(temp_v1, u16 *, 0x2C) = temp_v0_4;
            temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
            func_8004491C(temp_v0, &D_80045340);
            if (var_s1 == 0) {
                var_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u8 **, 8);
                do {
                    entry_flags = *var_v1;
                    var_v1 += 0xC;
                } while (entry_flags & 0x20);
                var_v1 -= 0xC;
                ASM_KEEP(var_v1);
                temp_v0_6 = M2C_FIELD(var_v1, u16 *, 6);
                sp10[3] = 1;
                sp10[2] = 0x10;
                sp10[0] = 0;
                sp10[1] = (s16) ((u32) (((temp_v0_6 & 0xFFC0) - 0x40) & 0xFFFF) >> 6);
                do {
                    func_800672D8((s16 *) sp10, callback_page + 0x5F70);
                    temp_v0_5 = sp10[0] + 0x10;
                    sp10[0] = temp_v0_5;
                } while (temp_v0_5 < 0x100);
            }
            temp_v1_3 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_v1_3, u16 *, 0x12) = (u16) (M2C_FIELD(temp_v1_3, u16 *, 0x12) - 0x40);
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s16 *, 0x10) = 0x20;
        }
        var_s1 += 1;
    } while (var_s1 < 3);
}

/* MECHANISM: Explicit object and 0x80170000 page bases restore the s4/s3 holds
   and the exact 0x38 frame; one four-halfword array preserves every call-visible slot.
   A 32-bit outer counter removes sign extensions, and ASM_KEEP at the pointer
   decrement prevents lhu -6 folding, emitting retail's addiu -0xC; lhu +6 seam. */
