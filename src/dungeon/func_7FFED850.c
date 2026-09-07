#include "common.h"
#include "m2c_compat.h"

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

typedef struct S_8008AFB0_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s16 unk_02;
    s32 unk_04;
} S_8008AFB0_0;   /* &D_800CF720[0] in func_8008AFB0 */

s32 func_8008AFB0(s8 arg0, s8 arg1, s16 arg2, s32 arg3) {
    register s32 call_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_a1 ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 call_a2 ASM_REG("$6");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s8 r_arg0 = arg0;
    s8 r_arg1 = arg1;
    s16 r_arg2 = arg2;
    s32 r_arg3 = arg3;
    u32 *r_ptr;
    s32 r_size;
    register s32 r_remaining ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s8 *r_base ASM_REG("$16");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 raw_size;
    register s32 limit ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 call_result;

    r_ptr = func_8008AF2C(call_a0, call_a1, call_a2);
    ASM_KEEP(r_arg0);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(r_arg1);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ASM_KEEP(r_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    raw_size = 0;
    if (r_ptr == NULL)
        return raw_size;

    raw_size = (u32) *r_ptr >> 0xB;
    r_size = (raw_size + 1) << 0xB;
    call_result = func_8008ACE8(r_arg3);
    limit = 0x8000;
    r_remaining = limit - call_result;
    if (r_size > 0x7FFF) {
        r_arg3 = 0;
        ASM_KEEP(r_arg3);   /* MATCH pin: retail delay-slot fill depends on it */
        func_8008AC84(r_arg3);
        {
            register s32 r_tail_arg ASM_REG("$4") = r_arg3;   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_TAILSLOT_PIN(r_tail_arg);   /* MATCH pin: load-bearing for the whole function shape */
            func_8008B07C();
        }
    }

    if (r_remaining < r_size) {
        register s8 *r_page ASM_REG("$2") = D_800CF720;   /* MATCH pin: keeps a statement from moving across a call/branch */
        register s32 r_index ASM_REG("$3") = r_arg3 << 3;   /* MATCH pin: load-bearing for the whole function shape */
        r_base = r_page + r_index;
        func_8008B058_live();
        do {
            r_arg3--;
            r_remaining += ((s32 *)r_base)[1];
            func_8008AC84(r_arg3);
            r_base -= 8;
        } while (r_remaining < r_size);
        r_base += 8;
        ASM_KEEP(r_base);   /* MATCH pin: retail basic-block layout depends on it */
    }
    func_8008AD90(r_arg3, r_size);
    func_8008AC84(r_arg3 + 1);
    D_800CF720[0] = r_arg0;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_01 = r_arg1;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_02 = r_arg2;
    ((S_8008AFB0_0 *)(&D_800CF720[0]))->unk_04 = r_size;
    func_80053CFC(r_ptr, D_801131E4[0]);
    return 0;
}
