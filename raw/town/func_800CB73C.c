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

typedef void (*Callback)(void *, s32, void *);

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

M2C_UNK func_800C2C80();
M2C_UNK func_800C2CB0();
s32 func_800C2E1C();
s32 func_800C2F14();
M2C_UNK func_800C8F4C();

void func_800C8E9C(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0;

    M2C_FIELD(arg0, Callback *, 0x50)(arg0, arg1, arg2);
    if (!(M2C_FIELD(arg0, u16 *, -2) & 0x8000)) {
        temp_v0 = func_800C2E1C(M2C_FIELD(arg0, s16 *, 0x72), M2C_FIELD(arg0, s16 *, 0x64));
        if (M2C_FIELD(arg0, s16 *, 0x74) != temp_v0) {
            func_800C2CB0(arg0, arg2, M2C_FIELD(arg0, M2C_UNK **, 0x78)[temp_v0], M2C_FIELD(arg2, s8 *, 4));
            M2C_FIELD(arg0, s16 *, 0x74) = temp_v0;
        }
        if ((func_800C2F14(M2C_FIELD(arg0, s16 *, 0x72), M2C_FIELD(arg0, s16 *, 0x64)) << 0x10) != 0) {
            u16 bit_value = M2C_FIELD(arg2, u16 *, 0x14) | 1;
            ASM_TAILSLOT_PIN(bit_value);
            func_800C8F4C();
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (s16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
        ASM_SCHED_BARRIER();
        func_800C2C80(arg0, arg2, 0, 0);
    }
}
