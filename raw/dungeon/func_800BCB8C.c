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

void func_80041E70(void *);             /* extern */
s32 func_80042900();            /* extern */
M2C_UNK func_8008D344(); /* extern */
M2C_UNK func_80098864();           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
s32 func_800C248C();                                /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_800DDE84[];
extern M2C_UNK D_800E1580;
extern M2C_UNK D_800E15A2;
extern s32 D_800E3D7C;
extern void *D_800E3DF0[];

s32 func_800C22EC(void *arg0, s32 arg1, s16 arg2, M2C_UNK arg3) {
    s32 temp_v1;
    s32 mask;
    s32 var_s2;
    void *temp_a0;
    void *temp_s0;

    var_s2 = 0;
    if (arg2 == 0xD) {
        func_80098864(arg1, arg3);
        return func_800C248C();
    }
    if (arg0 == D_800E3D7C) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, arg0);
        func_800C248C();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, ((u16 *)D_800DDE84)[M2C_FIELD(arg0, u8 *, 0x13)] & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C248C();
            return 1;
        }
        /* Duplicate return node #16. Try simplifying control flow for better match */
        func_80098B38(arg1);
        {
            register void *counter ASM_REG("$4");

            counter = &D_80083460;
            M2C_FIELD(counter, u16 *, 0xA) = (u16) (M2C_FIELD(counter, u16 *, 0xA) - 1);
        }
        return 1;
    }
    temp_a0 = *(void **)((u8 *)&D_80082E80 + 0x34);
    if (M2C_FIELD(temp_a0, u8 *, 1) == 0x13) {
        temp_v1 = M2C_FIELD(temp_a0, u8 *, 3) & 0x1F;
        if (temp_v1 < 0x14) {
            temp_s0 = D_800E3DF0[temp_v1];
            if ((func_80042900(temp_s0, 0xE, arg2) << 0x10) != 0) {
                register void *call_a0 ASM_REG("$4");

                mask = 0xFBFFFFFF;
                call_a0 = temp_s0;
                M2C_FIELD(temp_s0, s8 *, 0x28) = (s8) (((u8) M2C_FIELD(temp_s0, u8 *, 0x29) >> 1) + 1);
                M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x1C) & mask);
                var_s2 = 1;
                func_80041E70(call_a0);
                func_80099844(temp_s0, &D_800E1580);
            }
        }
    }
    if (var_s2 == 0) {
        func_800997FC(&D_800E15A2);
    }
    func_80098B38(arg1);
    {
        register void *counter ASM_REG("$4");

        counter = &D_80083460;
        M2C_FIELD(counter, u16 *, 0xA) = (u16) (M2C_FIELD(counter, u16 *, 0xA) - 1);
    }
    return 1;
}

/* MECHANISM: The natural arg0/arg1/status lifetimes produce retail's 0x20 frame and s0-s2 saves.
   Exact callee arity plus typed u16/pointer tables recover the call schedule and table strides.
   Scoped a0 pins hold the fixup call argument and D_80083460 tail base without backend fences. */
