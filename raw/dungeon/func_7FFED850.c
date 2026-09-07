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

extern void func_80053CFC(u32 *, s32);
extern s32 func_8008AC84(s32);
extern s32 func_8008ACE8(s32);
extern void func_8008AD90(s32, s32);
extern u32 *func_8008AF2C(s32, s32, s32);
extern void func_8008B058() __attribute__((noreturn));
extern s32 func_8008B058_live(void) __asm__("func_8008B058");
extern void func_8008B07C() __attribute__((noreturn));
extern s8 D_800CF720[0x8E4];
extern s32 D_801131E4[3];

s32 func_8008AFB0(s8 arg0, s8 arg1, s16 arg2, s32 arg3) {
    register s32 call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register s8 r_arg0 ASM_REG("$21") = arg0;
    register s8 r_arg1 ASM_REG("$22") = arg1;
    register s16 r_arg2 ASM_REG("$23") = arg2;
    register s32 r_arg3 ASM_REG("$18") = arg3;
    register u32 *r_ptr ASM_REG("$20");
    register s32 r_size ASM_REG("$19");
    register s32 r_remaining ASM_REG("$17");
    register s8 *r_base ASM_REG("$16");
    register s32 raw_size ASM_REG("$2");
    register s32 limit ASM_REG("$3");
    s32 call_result;

    r_ptr = func_8008AF2C(call_a0, call_a1, call_a2);
    ASM_KEEP(r_arg0);
    ASM_KEEP(r_arg1);
    ASM_KEEP(r_arg2);
    ASM_KEEP(r_ptr);
    raw_size = 0;
    if (r_ptr == NULL)
        return raw_size;

    raw_size = (u32) *r_ptr >> 0xB;
    r_size = (raw_size + 1) << 0xB;
    call_result = func_8008ACE8(r_arg3);
    limit = 0x8000;
    ASM_KEEP(limit);
    r_remaining = limit - call_result;
    if (r_size > 0x7FFF) {
        r_arg3 = 0;
        ASM_KEEP(r_arg3);
        func_8008AC84(r_arg3);
        {
            register s32 r_tail_arg ASM_REG("$4") = r_arg3;
            ASM_TAILSLOT_PIN(r_tail_arg);
            func_8008B07C();
        }
    }

    if (r_remaining < r_size) {
        register s8 *r_page ASM_REG("$2") = D_800CF720;
        register s32 r_index ASM_REG("$3") = r_arg3 << 3;
        r_base = r_page + r_index;
        ASM_TAILSLOT_PIN(r_base);
        ASM_SHAPE_D_SIBCALL_PIN(func_8008AFB0, 0x8008B04C, func_8008B058);
        func_8008B058_live();
        do {
            r_arg3--;
            r_remaining += ((s32 *)r_base)[1];
            func_8008AC84(r_arg3);
            r_base -= 8;
        } while (r_remaining < r_size);
        r_base += 8;
        ASM_KEEP(r_base);
    }
    func_8008AD90(r_arg3, r_size);
    func_8008AC84(r_arg3 + 1);
    D_800CF720[0] = r_arg0;
    M2C_FIELD(&D_800CF720[0], s8 *, 1) = r_arg1;
    M2C_FIELD(&D_800CF720[0], s16 *, 2) = r_arg2;
    M2C_FIELD(&D_800CF720[0], s32 *, 4) = r_size;
    func_80053CFC(r_ptr, D_801131E4[0]);
    return 0;
}
