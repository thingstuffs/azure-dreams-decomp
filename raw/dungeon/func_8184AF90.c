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

void func_80024908() __attribute__((noreturn));  /* extern */
M2C_UNK func_8003DB94();      /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800246AC;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEB28;

s32 func_80024790(void *arg0, s32 arg1) {
    register s32 held_arg1 ASM_REG("$20") = arg1;
    register s32 temp_s2 ASM_REG("$18");
    register s32 sign_temp ASM_REG("$2");
    register s32 return_value ASM_REG("$2");
    s16 temp_v0_3;
    s32 var_a2;
    register s32 temp_s5 ASM_REG("$21");
    s32 temp_v1;
    s32 var_a0;
    s32 final_value;
    s8 temp_v0_2;
    register u8 *global_page ASM_REG("$2");
    u8 *global_addr;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s3;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s5 = held_arg1;
        ASM_KEEP(temp_s5);
        ASM_KEEP(held_arg1);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800246AC;
        M2C_FIELD(temp_v0, u16 *, 0x20) = (u16) M2C_FIELD(arg0, u16 *, 2);
        temp_s3 = temp_v0 + 0x20;
        M2C_FIELD(temp_s3, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 6);
        ASM_SCHED_BARRIER();
        sign_temp = held_arg1 << 16;
        temp_s2 = sign_temp >> 16;
        ASM_KEEP(sign_temp);
        ASM_KEEP(temp_s2);
        temp_v1 = temp_s2 << 8;
        var_a0 = temp_v1;
        M2C_FIELD(temp_s3, u16 *, 4) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        if (temp_v1 < 0) {
            var_a0 = temp_v1 + 0xFFF;
        }
        var_a2 = temp_s2;
        M2C_FIELD(temp_s3, s16 *, 8) = (s16) (temp_v1 - ((var_a0 >> 0xC) << 0xC));
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v0_2 = ~(temp_s5 * 8);
        M2C_FIELD(temp_s0, s8 *, 0xE) = temp_v0_2;
        M2C_FIELD(temp_s0, s8 *, 0xD) = temp_v0_2;
        M2C_FIELD(temp_s0, s8 *, 0xC) = temp_v0_2;
        ASM_KEEP(temp_s5);
        global_page = (u8 *) 0x800E0000;
        ASM_KEEP(global_page);
        global_addr = global_page - 0x14D8;
        if (temp_s2 < 0) {
            var_a2 = temp_s2 + 7;
        }
        func_8003DB94(temp_s0, global_addr, (s16) (7 - (temp_s2 - ((var_a2 >> 3) * 8))));
        temp_v0_3 = (temp_s2 << 6) + 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = temp_v0_3;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = temp_v0_3;
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        func_8004491C(temp_v0, &D_80045340);
        ASM_KEEP(temp_s2);
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0_2, s16 *, 2) = (s16) (M2C_FIELD(temp_v0, u16 *, 0x20) + ((s32) (func_800644B8(M2C_FIELD(temp_s3, s16 *, 8)) * 2) >> 8));
        M2C_FIELD(temp_s0_2, s16 *, 6) = (s16) (M2C_FIELD(temp_s3, u16 *, 2) + ((s32) (func_80064584(M2C_FIELD(temp_s3, s16 *, 8)) * 2) >> 8));
        return_value = (s32) temp_v0;
        final_value = M2C_FIELD(temp_s3, u16 *, 4) - (held_arg1 * 8);
        ASM_KEEP(return_value);
        M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) final_value;
        func_80024908(held_arg1 * 8);
    }
    return 0;
}

/* MECHANISM: Distinct s4/s5/s2 runtime roles force the retail 0x30 frame; a split sign extension
   and held 0x800e page reproduce the v0 temporaries and branch-delay address formation.
   The noreturn tail contract plus a v0 return hold across named final_value forces v1 and the +0xA delay-slot store. */
