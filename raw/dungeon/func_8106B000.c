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
#define M2C_VOL_FIELD(expr, type_ptr, offset) (*(volatile type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void func_8015EA10(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8015EAA4;
extern M2C_UNK D_8015EF68;
extern M2C_UNK D_80161FB8;
extern M2C_UNK D_80162000;

#ifdef __mips__
void func_8015E800(void);
static const u32 data_bank[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    0x8015E898, 0x8015EAA4, 0x8015F394, 0x8015F394,
    0x8015F394, 0x8015F3C0, 0x8015F340, 0x8015F340,
    0x8015F340, 0x8015F2EC, 0x8015F324, 0x8015F3C0,
    0x8015F3C0, 0x8015F384, 0x80160AF0, 0x80160AE8,
    0x80160AE0, 0x80160AF8, 0x80160AA0, 0x80160A98,
    0x80160A90, 0x97824081, 0x8E828582, 0x40819482,
    0x85828282, 0x93829282, 0x92828582, 0x44818B82,
    0x00000000, 0x00000000, 0x80161CBC, 0x80161D60,
    0x80161DD8, 0x80161E10, 0x80161CBC, 0x80161D60,
    0x80161DD8, 0x80161E70,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800,676");
#define BODY_NAME func_8015E898
#else
#define BODY_NAME func_8015E800
#endif

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3) {
    void *var_s0;
    s32 temp_v1;
    u16 flags98;
    void *temp_s2;
    register void *temp_s4 ASM_REG("$20");
    void *temp_s5;
    void *temp_v0;
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    var_s0 = NULL;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 == NULL) {
        goto done;
    }
    {
        var_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015EAA4;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x2B;
        func_8004491C(temp_v0, &D_80045340);
        temp_s4 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s4, s16 *, 0xA) = saved_arg3;
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x25) = saved_arg2;
        temp_s5 = var_s0;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80161FB8;
        M2C_FIELD(temp_s2, s8 *, 0x24) = saved_arg1;
        if (temp_v1 == 1) {
            flags98 = M2C_FIELD(var_s0, u16 *, 0x98);
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x6000);
            M2C_FIELD(var_s0, u16 *, 0x98) = (u16) (flags98 | 0x4000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x6000);
            func_8015EA10();
        }
        if (temp_v1 >= 2) {
            flags98 = M2C_FIELD(var_s0, u16 *, 0x98);
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000);
            M2C_FIELD(var_s0, u16 *, 0x98) = (u16) (flags98 | 0x4000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x2000);
            func_8015EA10();
        }
        call_a0 = temp_v0;
        if (((arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
                call_a1 = temp_s4;
                ASM_KEEP(call_a0);
                ASM_KEEP(call_a1);
                temp_v1 = func_800A6D30();
                call_a0 = temp_v0;
                if (!(temp_v1 & 1)) {
                    goto call_a1_setup;
                }
                M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x200);
                func_800A48F0(var_s0, 1, (func_800A6D30() & 0x3F) | 0x20);
                M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80162000;
                ASM_SCHED_BARRIER();
                goto post_a6d30;
            }
        }
        goto call_a1_setup;
post_a6d30:
        call_a0 = temp_v0;
call_a1_setup:
        func_800A9C18(call_a0, temp_s4, temp_s2, arg0);
        M2C_FIELD(temp_s5, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(temp_s5, s8 *, 0x9C) = -1;
        M2C_FIELD(temp_s5, M2C_UNK **, 0x8C) = &D_8015EF68;
        M2C_FIELD(temp_s2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s5, s16 *, 0xAA) = (s16) ((u16) M2C_FIELD(var_s0, s32 *, 0x14) & 7);
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
    }
done:
    return var_s0;
}
