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
#define M2C_ERROR(desc) (0)

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80DAD000")
    __attribute__((section(".text.func_80DAD000"), aligned(4))) = {
    0x80152874, 0x80152A3C, 0x80153208, 0x80153208,
    0x80153208, 0x80153234, 0x801531B4, 0x801531B4,
    0x801531B4, 0x80153144, 0x80153134, 0x80153234,
    0x80153234, 0x801531F8, 0x8015498C, 0x80154984,
    0x8015497C, 0x80154994, 0x8015493C, 0x80154934,
    0x8015492C, 0x95824081, 0x85829382, 0x40818482,
    0x99828882, 0x8E829082, 0x93828F82, 0x93828982,
    0x6F004481,
};
__asm__(".globl func_80DAD000\n"
        ".size func_80DAD000,572");
#define BODY_NAME func_80DAD074
#define BODY_ATTR __attribute__((used, section(".text.func_80DAD000")))
#else
#define BODY_NAME func_80DAD000
#define BODY_ATTR
#endif

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_80152954(void) __attribute__((noreturn));
void *func_801529C0(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80152A3C;
extern M2C_UNK D_80152E68;
extern M2C_UNK D_8015586C;

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) BODY_ATTR;
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp24;
    s32 sp24;
    s32 temp_v1;
    void *temp_s2;
    register void *temp_s4 ASM_REG("$20");
    register void *temp_v0 ASM_REG("$17");
    void *temp_s5;
    register void *var_s0 ASM_REG("$16") = NULL;
    register s8 saved_arg1 ASM_REG("$22");
    register s8 saved_arg2 ASM_REG("$21");
    register s16 saved_arg3 ASM_REG("$18");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    M2C_ERROR(/* Read from unset register $t0 */) | 0x4481;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    unksp24 = (s32) *(s8 *)-0x56D4;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80152A3C;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x1A;
        func_8004491C(temp_v0, &D_80045340);
        temp_s4 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s4, s16 *, 0xA) = saved_arg3;
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x25) = saved_arg2;
        temp_s5 = var_s0;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8015586C;
        M2C_FIELD(temp_s2, s8 *, 0x24) = saved_arg1;
        if (temp_v1 == 1) {
            register s32 flags0 ASM_REG("$2");
            register s32 flags1 ASM_REG("$3");

            flags0 = M2C_FIELD(var_s0, s32 *, 0x14) | 0x6000;
            flags1 = M2C_FIELD(var_s0, s32 *, 0x1C) | 0x6000;
            ASM_KEEP(flags0);
            ASM_TAILSLOT_PIN(flags1);
            return func_80152954();
        }
        if (temp_v1 >= 2) {
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x2000);
            func_801529C0();
        }
        call_a0 = temp_v0;
        if (((arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
                call_a1 = temp_s4;
                ASM_KEEP_NV(call_a0);
                ASM_KEEP(call_a1);
                if (func_800A6D30() & 1) {
                    M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                }
            }
        }
        func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
        M2C_FIELD(temp_s5, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(temp_s5, s8 *, 0x9C) = -1;
        M2C_FIELD(temp_s5, M2C_UNK **, 0x8C) = &D_80152E68;
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
    }
    return var_s0;
}
