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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern void func_80158988(void) __attribute__((noreturn));
extern void func_80158A00(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80158A7C;
extern M2C_UNK D_80158EA8;
extern M2C_UNK D_8015C038;
extern M2C_UNK D_8015C088;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80FF3000")
    __attribute__((section(".text.func_80FF3000"), aligned(4))) = {
    0x801588a8, 0x80158a7c, 0x801592b8, 0x801592b8,
    0x801592b8, 0x801592e4, 0x80159264, 0x80159264,
    0x80159264, 0x801591f4, 0x801591e4, 0x801592e4,
    0x801592e4, 0x801592a8, 0x8015aac4, 0x8015aabc,
    0x8015aab4, 0x8015aacc, 0x8015aa74, 0x8015aa6c,
    0x8015aa64, 0x89824081, 0x40819382, 0x93829082,
    0x83829982, 0x85828882, 0x7c818482, 0x90829582,
    0x00004481, 0x92824081, 0x96828582, 0x81828582,
    0x85828c82, 0x40818482, 0x94828982, 0x40819382,
    0x92829482, 0x85829582, 0x90824081, 0x97828f82,
    0x92828582, 0x65004481,
};
__asm__(".globl func_80FF3000\n"
        ".size func_80FF3000, 636");
#define BODY_NAME func_80FF30A8
#else
#define BODY_NAME func_80FF3000
#endif

void *BODY_NAME(s32, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80FF3000")))
#endif
    ;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    register void *var_s0 ASM_REG("$16");
    register void *temp_v0 ASM_REG("$17");
    register s16 saved_arg3 ASM_REG("$18");
    register s32 saved_arg0 ASM_REG("$19");
    register void *temp_s4 ASM_REG("$20");
    register s8 saved_arg2 ASM_REG("$21");
    register s8 saved_arg1 ASM_REG("$22");
    register s32 final_arg0 ASM_REG("$23");
    register s32 temp_v1 ASM_REG("$3");
    register s32 high_arg0 ASM_REG("$2");
    void *temp_s2;
    void *temp_s5;

    saved_arg0 = arg0;
    var_s0 = NULL;
    ASM_KEEP_NV(var_s0);
    ASM_KEEP_NV(saved_arg0);
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        final_arg0 = saved_arg0;
        ASM_SCHED_BARRIER();
        var_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80158A7C;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x28;
        func_8004491C(temp_v0, &D_80045340);
        high_arg0 = (s32) &D_8015C038;
        temp_s4 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s4, s16 *, 0xA) = saved_arg3;
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = saved_arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x25) = saved_arg2;
        temp_s5 = var_s0;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = (void *) high_arg0;
        M2C_FIELD(temp_s2, s8 *, 0x24) = saved_arg1;
        if (temp_v1 == 1) {
            high_arg0 = M2C_FIELD(var_s0, s32 *, 0x14);
            temp_v1 = M2C_FIELD(var_s0, s32 *, 0x1C);
            high_arg0 |= 0x6000;
            temp_v1 |= 0x6000;
            ASM_KEEP_NV(high_arg0);
            ASM_TAILSLOT_PIN(temp_v1);
            ASM_KEEP(high_arg0);
            func_80158988();
        }
        high_arg0 = temp_v1 < 2;
        if (!high_arg0) {
            high_arg0 = M2C_FIELD(var_s0, s32 *, 0x14);
            temp_v1 = M2C_FIELD(var_s0, s32 *, 0x1C);
            high_arg0 |= 0x2000;
            temp_v1 |= 0x2000;
            M2C_FIELD(var_s0, s32 *, 0x14) = high_arg0;
            M2C_FIELD(var_s0, s32 *, 0x1C) = temp_v1;
            func_80158A00();
        }
        high_arg0 = saved_arg0 & ~3;
        if ((high_arg0 << 0x10) == 0) {
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
                if (func_800A6D30() & 1) {
                    M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                    M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8015C088;
                }
            }
        }
        func_800A9C18(temp_v0, temp_s4, temp_s2, (s16)(s32) final_arg0);
        M2C_FIELD(temp_s5, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(temp_s5, s8 *, 0x9C) = -1;
        M2C_FIELD(temp_s5, M2C_UNK **, 0x8C) = &D_80158EA8;
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
        return var_s0;
    }
    return var_s0;
}
