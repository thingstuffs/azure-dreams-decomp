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

typedef struct {
    s32 value;
} __attribute__((packed)) M2C_UNALIGNED_WORD;

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

s32 func_800B2130();
M2C_UNK func_800B2190();
M2C_UNK *func_800B2280();
M2C_UNK func_800B23C0();
s32 func_800B25B4();
s32 func_800B29A4();

s32 func_800B2400(void *arg0) {
    M2C_UNK *temp_v0_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v1;
    u8 temp_byte;
    void *temp_a0;
    void *temp_s0;
    void *temp_s2;
    void *temp_v1_5;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_sp;

    temp_v0 = func_800B2130(M2C_FIELD(arg0, s32 *, 0x18));
    temp_v1_5 = arg0 + (M2C_FIELD(arg0, s32 *, 0x18) * 0x10);
    if (M2C_FIELD(temp_v1_5, s32 *, 0x28) >= temp_v0) {
        var_v1 = 1;
        if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
            var_v1 = 2;
            ASM_TAILSLOT_PIN_TIED(var_v1);
            return func_800B25B4();
        }
        goto done;
    }
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x14);
    temp_a0 = arg0 + (temp_v1 * 0x10);
    if (M2C_FIELD(temp_a0, s32 *, 0x28) == 0) {
        var_v1 = 4;
        ASM_TAILSLOT_PIN_TIED(var_v1);
        return func_800B25B4(temp_a0);
    }
    temp_s2 = M2C_FIELD((M2C_FIELD(temp_a0, s32 *, 0x24) * 4) + M2C_FIELD(((temp_v1 * 4) + arg0), s32 *, 0x3C), s32 *, 0);
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        temp_byte = M2C_FIELD(temp_s2, u8 *, 1);
        if (temp_byte == 0x13) {
            var_v1 = 3;
            goto done;
        }
    }
    {
        ASM_MEM_BARRIER();
        temp_s0 = M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x18) * 4) + arg0), s32 *, 0x3C) + (func_800B29A4(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x18) * 4) + arg0), s32 *, 0x3C)) * 4);
        temp_v0_2 = func_800B2280(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x18) * 4) + arg0), s32 *, 0x3C), M2C_FIELD(arg0, s32 *, 0x18), temp_v0);
        *(M2C_UNALIGNED_WORD *)temp_v0_2 = *(M2C_UNALIGNED_WORD *)temp_s2;
        M2C_FIELD(temp_s0, M2C_UNK **, 0) = temp_v0_2;
        M2C_FIELD(temp_s0, s32 *, 4) = 0;
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x14);
        func_800B2190(M2C_FIELD(((temp_v1_2 * 4) + arg0), s32 *, 0x3C), (temp_sp = arg0 + (temp_v1_2 * 0x10), M2C_FIELD(temp_sp, s32 *, 0x24)));
        temp_v1_3 = (M2C_FIELD(arg0, s32 *, 0x14) * 0x10) + arg0;
        M2C_FIELD(temp_v1_3, s32 *, 0x28) = (s32) (M2C_FIELD(temp_v1_3, s32 *, 0x28) - 1);
        func_800B23C0(arg0 + ((M2C_FIELD(arg0, s32 *, 0x14) * 0x10) + 0x1C));
        temp_v1_4 = arg0 + (M2C_FIELD(arg0, s32 *, 0x18) * 0x10);
        M2C_FIELD(temp_v1_4, s32 *, 0x28) = (s32) (M2C_FIELD(temp_v1_4, s32 *, 0x28) + 1);
        func_800B23C0(arg0 + ((M2C_FIELD(arg0, s32 *, 0x18) * 0x10) + 0x1C));
        var_v1 = 0;
    }
done:
    return var_v1;
}
