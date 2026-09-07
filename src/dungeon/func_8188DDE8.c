#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void func_800649A0(s32);
extern void func_80064A40(void);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 D_80026472[5];
extern s32 D_800814A0;

void func_800255E8(void *arg0, void *arg1, void *arg2)
{
    u16 input[3];
    s32 output[8];
    u16 *scratch = (u16 *)0x1F800000;
    void *state = arg1;
    u16 *page;
    s32 delta10;
    u16 coord;
    u16 page_value;
    u16 scratch_value;
    s32 b0;
    s32 b1;
    s32 b2;
    s32 b3;
    register s32 b4 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 b5 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 q0;
    s32 q1;
    s32 q2;
    s32 q3;
    register s32 q4 ASM_REG("$11");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 q5 ASM_REG("$9");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 remaining;
    s32 remaining_test;

    scratch[0x70 / 2] = U16_AT(arg0, 0x34) - U16_AT(state, 2);
    scratch[0x78 / 2] = U16_AT(arg0, 0x3C) - U16_AT(state, 2);
    scratch[0x80 / 2] = U16_AT(arg0, 0x44) - U16_AT(state, 2);
    scratch[0x88 / 2] = U16_AT(arg0, 0x4C) - U16_AT(state, 2);
    scratch[0x72 / 2] = U16_AT(arg0, 0x36) - U16_AT(state, 6);
    scratch[0x7A / 2] = U16_AT(arg0, 0x3E) - U16_AT(state, 6);
    scratch[0x82 / 2] = U16_AT(arg0, 0x46) - U16_AT(state, 6);
    scratch[0x8A / 2] = U16_AT(arg0, 0x4E) - U16_AT(state, 6);
    scratch[0x74 / 2] = U16_AT(arg0, 0x38) - U16_AT(state, 0xA);
    scratch[0x7C / 2] = U16_AT(arg0, 0x40) - U16_AT(state, 0xA);
    page = (u16 *)0x80020000;

    page_value = page[0x6472 / 2];
    coord = U16_AT(arg0, 0x48);
    delta10 = U16_AT(state, 0xA);
    page_value++;
    scratch_value = coord - delta10;
    page[0x6472 / 2] = page_value;
    scratch[0x84 / 2] = scratch_value;
    scratch[0x8C / 2] = U16_AT(arg0, 0x50) - U16_AT(state, 0xA);
    func_800649A0(delta10);

    input[0] = U16_AT(arg2, 0x16);
    input[1] = U16_AT(arg2, 0x18);
    input[2] = 0;
    output[7] = 0;
    output[6] = 0;
    output[5] = 0;
    func_80065820(input, output);
    func_80064D80(output);
    func_80064CF0(output);

    func_80065320(scratch + 0x70 / 2, scratch + 0x98 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x78 / 2, scratch + 0xA0 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x80 / 2, scratch + 0xA8 / 2,
                  scratch + 0x94 / 2);
    func_80065320(scratch + 0x88 / 2, scratch + 0xB0 / 2,
                  scratch + 0x94 / 2);
    func_80064A40();

    S32_AT(state, 0) = S32_AT(state, 0) + S32_AT(state, 0xC);
    S32_AT(state, 4) = S32_AT(state, 4) + S32_AT(state, 0x10);
    S32_AT(state, 8) = S32_AT(state, 8) + S32_AT(state, 0x14);

    U16_AT(arg0, 0x34) = scratch[0x98 / 2] + U16_AT(state, 2);
    U16_AT(arg0, 0x3C) = scratch[0xA0 / 2] + U16_AT(state, 2);
    U16_AT(arg0, 0x44) = scratch[0xA8 / 2] + U16_AT(state, 2);
    U16_AT(arg0, 0x4C) = scratch[0xB0 / 2] + U16_AT(state, 2);
    U16_AT(arg0, 0x36) = scratch[0x9A / 2] + U16_AT(state, 6);
    U16_AT(arg0, 0x3E) = scratch[0xA2 / 2] + U16_AT(state, 6);
    U16_AT(arg0, 0x46) = scratch[0xAA / 2] + U16_AT(state, 6);
    U16_AT(arg0, 0x4E) = scratch[0xB2 / 2] + U16_AT(state, 6);
    U16_AT(arg0, 0x38) = scratch[0x9C / 2] + U16_AT(state, 0xA);

    b0 = U8_AT(arg0, 0x54);
    ASM_KEEP_NV(b0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    q0 = b0 / S16_AT(arg0, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    b1 = U8_AT(arg0, 0x55);
    ASM_KEEP_NV(b1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    q1 = b1 / S16_AT(arg0, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    b2 = U8_AT(arg0, 0x56);
    ASM_KEEP_NV(b2);   /* MATCH pin: load-bearing for the whole function shape */
    q2 = b2 / S16_AT(arg0, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    b3 = U8_AT(arg0, 0x58);
    ASM_KEEP_NV(b3);   /* MATCH pin: retail register colouring depends on it */
    q3 = b3 / S16_AT(arg0, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    b4 = U8_AT(arg0, 0x59);
    q4 = b4 / S16_AT(arg0, 0x1A);
    ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    b5 = U8_AT(arg0, 0x5A);
    q5 = b5 / S16_AT(arg0, 0x1A);

    U16_AT(arg0, 0x40) = scratch[0xA4 / 2] + U16_AT(state, 0xA);
    U16_AT(arg0, 0x48) = scratch[0xAC / 2] + U16_AT(state, 0xA);
    U16_AT(arg0, 0x50) = scratch[0xB4 / 2] + U16_AT(state, 0xA);
    remaining = (u16)S16_AT(arg0, 0x1A) - 1;
    S16_AT(arg0, 0x1A) = remaining;
    remaining_test = remaining << 16;

    b0 -= q0;
    b1 -= q1;
    b2 -= q2;
    b3 -= q3;
    b4 -= q4;
    b5 -= q5;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    U8_AT(arg0, 0x54) = b0;
    U8_AT(arg0, 0x55) = b1;
    U8_AT(arg0, 0x56) = b2;
    U8_AT(arg0, 0x58) = b3;
    U8_AT(arg0, 0x59) = b4;
    U8_AT(arg0, 0x5A) = b5;

    if (remaining_test <= 0) {
        U16_AT(arg0, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
