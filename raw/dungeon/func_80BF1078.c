#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
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

extern u8 D_80083498[];
extern u8 D_8016AA58[];
extern u8 D_80045340[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern void func_8016A958(void) __attribute__((noreturn));
extern void func_8016A9C4(void) __attribute__((noreturn));
extern M2C_UNK D_8016B014;
extern M2C_UNK D_8016E20C;
extern M2C_UNK D_8016E25C;

void *func_8016A878(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp28;
    s32 temp_v1;
    s32 state_flags0;
    s32 state_flags1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v0;
    void *temp_s5;
    void *var_s0 = NULL;

    unksp28 = (s32) *(s8 *)-0x1E28;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 == NULL) {
        goto done;
    }
    var_s0 = temp_v0 + 0x20;
    M2C_FIELD(temp_v0, u8 **, 0x10) = D_8016AA58;
    M2C_FIELD(var_s0, s8 *, 0x13) = 0x10;
    func_8004491C(temp_v0, D_80045340);
    temp_s4 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_s4, s16 *, 0xA) = arg3;
    temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
    temp_v1 = arg0 & 3;
    M2C_FIELD(temp_s2, s8 *, 0x25) = arg2;
    temp_s5 = var_s0;
    M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8016E20C;
    M2C_FIELD(temp_s2, s8 *, 0x24) = arg1;
    if (temp_v1 == 1) {
        state_flags0 = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x6000);
        state_flags1 = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x6000);
        func_8016A958();
    }
    if (temp_v1 >= 2) {
        state_flags0 = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000);
        state_flags1 = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x2000);
        M2C_FIELD(var_s0, s32 *, 0x14) = state_flags0;
        M2C_FIELD(var_s0, s32 *, 0x1C) = state_flags1;
        func_8016A9C4();
    }
    if (((arg0 & ~3) << 0x10) == 0) {
        if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
            if (func_800A6D30(temp_v0, temp_s4) & 1) {
                func_800A48F0(var_s0, 1, (func_800A6D30(temp_v0) & 0x3F) | 0x20);
                M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8016E25C;
            }
        }
    }
    func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
    M2C_FIELD(var_s0, s8 *, 0x9A) = 0xFF;
    M2C_FIELD(var_s0, s8 *, 0x9C) = -1;
    M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_8016B014;
    M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x40000);
    M2C_FIELD(var_s0, s16 *, 0x92) = -0x20;
    func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
done:
    return var_s0;
}
