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

void *func_800373DC();                       /* extern */
M2C_UNK func_8003BC18();           /* extern */
s32 func_80071494();                                /* extern */
extern u8 D_8003C558[];
extern u8 D_802843E8[];
extern s32 D_802843EC[];
extern u8 D_8052FA64[];

void func_80814D60(void *arg0) {
    u32 page;
    register u16 flags ASM_REG("$2");
    s32 global_word;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, void **, 0x10) = D_8052FA64;
        func_8003BC18(temp_v0, &D_8003C558);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) + 0xFFF90000);
        M2C_FIELD(temp_s1, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 0xFFFD0000);
        M2C_FIELD(temp_s1, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0xC) >> 1);
        M2C_FIELD(temp_s1, s32 *, 0x14) = (s32) (((func_80071494() & 0x1FF) - 0x100) << 0xA);
        page = 0x00800000;
        ASM_KEEP(page);
        M2C_FIELD(temp_s0, volatile s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_s0, volatile s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_s0, volatile s16 *, 0x10) = 0x60;
        flags = M2C_FIELD(temp_s0, volatile u16 *, 0x14);
        ASM_KEEP(flags);
        M2C_FIELD(temp_s0, void * volatile *, 0) = D_802843E8;
        ASM_SCHED_BARRIER();
        M2C_FIELD(temp_s0, volatile u16 *, 0x14) = flags | 0xD;
        global_word = D_802843EC[0];
        page |= 0x80F0;
        M2C_FIELD(temp_s0, volatile s8 *, 4) = 0;
        M2C_FIELD(temp_s0, volatile s8 *, 5) = 0;
        M2C_FIELD(temp_s0, volatile s32 *, 0xC) = page;
        M2C_FIELD(temp_s0, volatile s32 *, 8) = global_word;
    }
}
/* MECHANISM: Symbol-typed hi/lo globals preserve the 0x20 frame and natural s2/s1/s0 held roles.
   A guarded v0 flags pin plus volatile tail fields and one scheduler fence reproduce the lhu/address/store order.
   A named 0x00800000 page kept live splits the late ori and fills the global-load delay. */
