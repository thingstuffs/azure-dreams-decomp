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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern u8 D_A0700000[0x1000];
extern CallbackOwner *D_A0700F58[4];

extern s32 func_80700304(void);
extern void func_8070049C(void) __attribute__((noreturn));
extern void func_80700590(s32, u8 *);
extern s32 func_80700DC0(s16);

s32 func_808B2B98(s32 arg0) {
    register s32 temp_v0 ASM_REG("$2");
    s32 temp_a0;
    s32 var_s0;
    u8 *temp_a1;
    void *temp_v1;
    s32 temp_result;

    var_s0 = arg0;
    if (func_80700304() > 0) {
        temp_v0 = *(s16 *)(D_A0700000 + (var_s0 * 2) + 0xF34);
        ASM_KEEP(temp_v0);
        temp_a0 = temp_v0;
        if (temp_v0 < 0) {
            temp_a0 = temp_v0 + 0x1F;
        }
        temp_a0 >>= 5;
        temp_a1 = *(u8 **)0xA0700F40 + temp_a0;
        temp_a0 <<= 5;
        temp_a0 = temp_v0 - temp_a0;
        *temp_a1 |= 1 << temp_a0;
        func_80700590(temp_a0, temp_a1);
        func_8070049C();
    }
    D_A0700F58[0]->callback(2);
    temp_v1 = *(void **)0xA0700F40;
    M2C_FIELD(temp_v1, u8 *, 0xE) = (u8) M2C_FIELD(temp_v1, u8 *, 0xE);
    temp_result = func_80700DC0(*(s16 *)0xA0700F2A);
    if (temp_result == 0) {
        if (D_A0700F58[0]->callback(2) != 0) {
            var_s0 += 1;
        }
        *(s32 *)0xA0700F3C = var_s0;
        temp_v0 = var_s0;
        ASM_TAILSLOT_PIN_TIED(temp_v0);
        func_8070049C();
    }
    {
        register s32 final_value ASM_REG("$16");
        final_value = *(s32 *)0xA0700F3C;
        ASM_KEEP(final_value);
        return final_value;
    }
}
