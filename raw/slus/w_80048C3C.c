#include "common.h"

/* close_gap PERM base: REGALLOC_SWAP reg_map={'v0': 's1'}. Feed to permute.sh; wrap the diagnosed temps in PERM_VAR(...) or permute decl order. */
/* first_pass warm draft: compiles, best score 23 @ 2.7.2-cdk */
#include "common.h"
#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(v) __asm__("" : "=r"(v) : "0"(v))
#endif
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

M2C_UNK DrawSync();                          /* extern */
M2C_UNK func_8003E4FC();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8003F80C(); /* extern */
M2C_UNK func_80046F88();                      /* extern */
M2C_UNK func_80047200();    /* extern */
M2C_UNK func_80048B8C();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89[9];

void *func_80048C3C(s32 arg0) {
    void *temp_s0;
    register void *temp_s1 ASM_REG("$17");
    void *temp_s2;
    register s32 six ASM_REG("$4");
    register s32 one ASM_REG("$5");
    register void *call0 ASM_REG("$4");

    temp_s1 = (void *)(arg0 * 8);
    six = 6;
    ASM_KEEP(six);
    temp_s1 = (u8 *)temp_s1 + (u32)D_80071210;
    func_8003E4FC(six, M2C_FIELD(temp_s1, s32 *, 0), 0);
    func_8003F320();
    temp_s2 = M2C_FIELD(temp_s1, void **, 4);
    temp_s0 = temp_s2 + M2C_FIELD(temp_s2, s32 *, 0x1C);
    func_8003F80C(temp_s0, 0x7A00, M2C_FIELD(temp_s2, s32 *, 0x20), 2);
    DrawSync(0);
    call0 = temp_s0;
    ASM_KEEP(call0);
    one = 1;
    ASM_KEEP(one);
    func_80047200(call0, one, one);
    func_8003F80C(temp_s0, 0x7980, M2C_FIELD(temp_s2, s32 *, 0x20), 2);
    func_80046F88(temp_s2);
    func_80048B8C(temp_s2);
    temp_s1 = (u8 *)temp_s1 + 4;
    ASM_KEEP(temp_s1);
    D_80080A89[0] = 0;
    return temp_s1;
}
