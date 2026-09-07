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

M2C_UNK D_8009E714();         /* extern */
M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_800374F4();                     /* extern */
M2C_UNK func_8009DC8C();     /* extern */
M2C_UNK func_8009E918();                     /* extern */
M2C_UNK func_8009E95C();                            /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern s32 D_800D09C8[];

void func_8009E85C(void *arg0, void *arg1, void *arg2) {
    u8 *page = (u8 *)0x80010000;
    register s32 *active_base ASM_REG("$3");
    register s32 active ASM_REG("$3");
    register s32 init_flags ASM_REG("$2");
    register void *tail_self ASM_REG("$16");
    register M2C_UNK (*callback)(void *, void *, void *) ASM_REG("$3");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register void *call_a2 ASM_REG("$6");
    u16 flags;
    u8 temp_v1;

    M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *), -0x10) = D_8009E714;
    M2C_FIELD(arg0, s32 *, 0xA0) = 0xFFE00000;
    M2C_FIELD(arg1, s32 *, 8) = 0xFFE00000;
    M2C_FIELD(arg0, u8 *, 0x4C) = page[(M2C_FIELD(arg0, u8 *, 0x95) * 4) + 0x980];
    temp_v1 = page[(M2C_FIELD(arg0, u8 *, 0x95) * 4) + 0x981];
    M2C_FIELD(arg0, u8 *, 0x4D) = temp_v1;
    if (temp_v1 == 0x12) {
        M2C_FIELD(arg2, M2C_UNK **, 8) = &D_8006E240;
        func_8009E918();
        return;
    }
    func_8009DC8C(arg0, arg2, M2C_FIELD(arg0, u8 *, 0x4C), M2C_FIELD(page, s32 *, ((page[(M2C_FIELD(arg0, u8 *, 0x95) * 4) + 0x983] & 0x3F) * 0x54) + 0xA94));
    func_80033CD8(arg0, &D_80045340);
    init_flags = 0x20;
    ASM_KEEP(init_flags);
    active_base = (s32 *)0x800D0000;
    ASM_KEEP(active_base);
    M2C_FIELD(arg2, volatile s16 *, 0x10) = init_flags;
    flags = M2C_FIELD(arg2, volatile u16 *, 0x14);
    active = M2C_FIELD(active_base, volatile s32 *, 0x9C8);
    ASM_KEEP(active);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(flags | 0x1C);
    if (active == 0) {
        M2C_FIELD(arg0, s16 *, 0x6C) = func_800374F4(0x1000);
        func_8009E95C();
        return;
    }
    tail_self = arg0;
    ASM_KEEP(tail_self);
    M2C_FIELD(tail_self, s16 *, 0x6C) = 0;
    ASM_MEM_BARRIER();
    call_a0 = tail_self;
    call_a1 = arg1;
    call_a2 = arg2;
    ASM_KEEP(call_a0);
    ASM_KEEP(call_a1);
    ASM_KEEP(call_a2);
    callback = M2C_FIELD(call_a0, M2C_UNK (**)(void *, void *, void *), -0x10);
    ASM_KEEP(callback);
    D_800D09C8[0] = 0;
    callback(call_a0, call_a1, call_a2);
}

/* MECHANISM: A held 0x80010000 page recreates retail's shared a1 table base and argument lifetimes.
   A split volatile RMW plus guarded v0/v1 roles interleaves the flag and global loads without a nop.
   Pinned tail ABI roles and ASM_MEM_BARRIER keep the s0 store before a0-a2 setup and the global clear
   in the indirect-call delay slot. */
