#include "common.h"

#ifdef NON_MATCHING
extern void func_800240BC(s32, s32) __attribute__((noreturn));
extern void func_8002416C(s32, u8 *, s32) __attribute__((noreturn));
#else
extern void func_800240BC(void) __attribute__((noreturn));
extern void func_8002416C(void) __attribute__((noreturn));
#endif
extern s32 func_800990FC(s32, s32);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(u8 *, s32);
extern void func_80099844(u8 *, u8 *);
extern s32 func_8009D218(u8 *, s32);
extern void func_800A5720(s32);
extern s32 func_800A6D30(void);
extern void func_800B4C7C(s32, u8 *, s32, s32);

extern u8 D_800E20D6[];
extern u8 D_800E20FC[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_81904800")
    __attribute__((section(".text.func_81904800"), aligned(4))) = {
    0x800257d0,
    0x01000340,
    0x00540060,
    0x01540340,
    0x00040004,
    0x00000020,
    0x00200020,
    0x00200000,
    0x0020ffe0,
    0x0000ffe0,
    0xffe0ffe0,
    0xffe00000,
    0xffe00020,
    0x00000000,
    0x800258ec,
    0x80025960,
    0x80025c28,
    0x80025e48,
    0x80026490,
    0x800265f0,
    0x80026634,
    0x80026730,
    0x800266cc,
};
__asm__(".globl func_81904800\n"
        ".size func_81904800, 400");
#define BODY_NAME func_8190485C
#else
#define BODY_NAME func_81904800
#endif

void BODY_NAME(u8 *arg0, u8 arg1) {
    s32 value;
    s32 result;
    s32 index;
    s32 count;
    register s32 remainder ASM_REG("$3");   /* MATCH pin: retail basic-block layout depends on it */
    register s32 condition ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 tail_a1 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u8 *call_arg;

    if (func_8009D218(arg0, 2) != 0) {
        return;
    }

    value = func_800A6D30() & 0xffff;
    if (arg0[3] != 0) {
        remainder = value % arg0[3];
        ASM_KEEP(remainder);   /* MATCH pin: retail basic-block layout depends on it */
#ifdef NON_MATCHING
        func_800240BC(value, arg1 & 0xff);
#else
        tail_a1 = arg1 & 0xff;
        ASM_TAILSLOT_PIN(tail_a1);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800240BC();
#endif
        return;
    }

    remainder = 0;
    ASM_KEEP(remainder);   /* MATCH pin: retail basic-block layout depends on it */
    index = arg1 & 0xff;
    condition = remainder < (index << 5);
    call_arg = (u8 *)value;
    if (!condition) {
        call_arg = arg0;
        if (index != 0xff) {
            goto fallback_call;
        }
    }
    if (arg0[0x27] >= 2) {
        count = (arg0[0x27] + 1) >> 1;
        arg0[0x27] -= count;
        {
            s32 raw;
            register s32 fixed ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 carrier ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */

            raw = func_800990FC((s32)call_arg, index);
            fixed = 8;
            carrier = raw;
            ASM_KEEP(carrier);   /* MATCH pin: retail schedule: same instructions, different order without it */
            result = carrier;
            raw = func_8009929C(fixed, carrier);
            raw = func_80099734(arg0, raw);
            raw = func_80099194(D_800E20D6, raw);
            func_80099290(raw);
        }
        func_800A5720(result);
#ifdef NON_MATCHING
        func_8002416C(0x53, arg0, count);
#else
        {
            register s32 tail_a0 ASM_REG("$4") = 0x53;   /* MATCH pin: retail schedule: same instructions, different order without it */
            register u8 *tail_a1_ptr ASM_REG("$5") = arg0;   /* MATCH pin: retail register colouring depends on it */
            register s32 tail_a2 ASM_REG("$6") = count;   /* MATCH pin: retail delay-slot contents depend on it */

            ASM_USE2(tail_a0, tail_a1_ptr);   /* MATCH pin: retail basic-block layout depends on it */
            ASM_TAILSLOT_PIN(tail_a2);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            func_8002416C();
        }
#endif
        return;
    }

    call_arg = arg0;
fallback_call:
    func_80099844(call_arg, D_800E20FC);
    func_800B4C7C(0x53, arg0, -1, 1);
}
