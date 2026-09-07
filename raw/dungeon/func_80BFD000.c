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

static const u32 func_8015E800_bank[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4), used)) = {
    0x8015e878, 0x00000000, 0x8015f470, 0x8015f470,
    0x8015f470, 0x8015f49c, 0x8015f41c, 0x8015f41c,
    0x8015f41c, 0x8015f3e4, 0x8015f3e4, 0x8015f49c,
    0x8015f49c, 0x8015f460, 0x801606c0, 0x801606b8,
    0x801606b0, 0x801606c8, 0x80160670, 0x80160668,
    0x80160660, 0x00000000, 0x80161d4c, 0x80161d60,
    0x80161da4, 0x80161e84, 0x80161f58, 0x801620bc,
    0x80162158, 0x801621d8,
};

__asm__(".globl func_8015E800\n.size func_8015E800, 600");

#ifdef __mips__
#define BODY_NAME func_8015E878
#else
#define BODY_NAME func_8015E800
#endif

extern u8 D_80083498[];
extern u8 D_8015EA58[];
extern u8 D_80045340[];
void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_8015F014;
extern M2C_UNK D_8016220C;
extern M2C_UNK D_8016225C;

__attribute__((section(".text.func_8015E800")))
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp24;
    s32 unksp28;
    s32 temp_v1;
    register void *var_s0 ASM_REG("$16") = NULL;
    register void *temp_v0 ASM_REG("$17");
    void *temp_s2;
    register void *temp_s4 ASM_REG("$20");
    void *actor;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    unksp28 = (s32) *(s8 *)0x21D8;
    unksp24 = (s32) *(s8 *)-0xBA0;
    temp_v0 = func_8003FD64(0x112, D_80083498);
    if (temp_v0 != NULL) {
        var_s0 = temp_v0 + 0x20;
        actor = var_s0;
        M2C_FIELD(temp_v0, u8 **, 0x10) = D_8015EA58;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x10;
        func_8004491C(temp_v0, D_80045340);
        temp_s4 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s4, s16 *, 0xA) = saved_arg3;
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x25) = saved_arg2;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8016220C;
        M2C_FIELD(temp_s2, s8 *, 0x24) = saved_arg1;
        if (temp_v1 == 1) {
            left = M2C_FIELD(var_s0, s32 *, 0x14) | 0x6000;
            right = M2C_FIELD(var_s0, s32 *, 0x1C) | 0x6000;
            goto write_kind;
        }
        if (temp_v1 < 2) {
            goto normal_path;
        }
        left = M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000;
        right = M2C_FIELD(var_s0, s32 *, 0x1C) | 0x2000;
write_kind:
        M2C_FIELD(var_s0, s32 *, 0x14) = left;
        M2C_FIELD(var_s0, s32 *, 0x1C) = right;
        goto common_path;
normal_path:
        if (((arg0 & ~3) << 0x10) == 0) {
            call_a0 = temp_v0;
            ASM_USE_NV(call_a0);
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
                call_a1 = temp_s4;
                ASM_KEEP(call_a1);
                temp_v1 = func_800A6D30(call_a0);
                if (temp_v1 & 1) {
                    func_800A48F0(var_s0, 1, (func_800A6D30(call_a0) & 0x3F) | 0x20);
                    M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_8016225C;
                }
            }
        }
common_path:
        func_800A9C18(temp_v0, temp_s4, temp_s2, arg0);
        M2C_FIELD(actor, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(actor, s8 *, 0x9C) = -1;
        M2C_FIELD(actor, M2C_UNK **, 0x8C) = &D_8015F014;
        M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x40000);
        M2C_FIELD(actor, s16 *, 0x92) = -0x20;
        func_800AA36C(actor, temp_s4, temp_s2, var_s0);
    }
    return var_s0;
}
