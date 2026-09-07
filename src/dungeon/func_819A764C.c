#include "common.h"

typedef struct S_819A764C_0_pre {
    u16 unk_00;
} S_819A764C_0_pre;   /* the 0x2 bytes before self in func_819A764C, addressed as self[-1] */

typedef struct S_819A764C_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x1A];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x8];
    s32 unk_38;
    union { s16 s; u16 u; } unk_3C;   /* accessed as both */
    u16 unk_3E;
    u8 pad_40[0x2];
    s16 unk_42;
} S_819A764C_0;   /* self in func_819A764C */

typedef struct S_819A764C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_819A764C_1;   /* inner in func_819A764C */

typedef struct S_819A764C_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_819A764C_2;   /* dst in func_819A764C */

typedef struct S_819A764C_3 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_819A764C_3;   /* (void *)page_base in func_819A764C */



extern u8 D_80024B20[];
#ifndef NON_MATCHING
extern u8 D_80020000[];
__asm__(".set D_80020000, 0x80020000");
#else
#define D_80020000 (D_80024B20 - 0x4B20)
#endif
extern void func_80025038(void) __attribute__((noreturn));
extern void func_8004491C();
extern s16 func_8006649C();
extern s32 func_80069EF8(void);

void func_819A764C(void *arg0)
{
    s16 delta[3];
    s32 state;
    s32 i;
    register void *dst ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    void *tail_arg;
    S_819A764C_1 *inner;
    register u32 page_base ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u8 *message;
    register void *self ASM_REG("$18") = arg0;   /* MATCH pin: load-bearing for the whole function shape */

    ASM_KEEP(self);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    inner = ((S_819A764C_0 *)self)->unk_00;
    inner->unk_52 |= 0x8000;

    delta[0] = (((S_819A764C_0 *)self)->unk_24 - ((S_819A764C_0 *)self)->unk_04.s) >> 2;
    delta[1] = (((S_819A764C_0 *)self)->unk_26 - ((S_819A764C_0 *)self)->unk_06.s) >> 2;
    delta[2] = (((S_819A764C_0 *)self)->unk_28 - ((S_819A764C_0 *)self)->unk_08.s) >> 2;
    i = 1;
    dst = self + 8;

    do {
        ((S_819A764C_2 *)dst)->unk_04 = ((S_819A764C_0 *)self)->unk_04.u + delta[0] * i
                            + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)dst)->unk_06 = ((S_819A764C_0 *)self)->unk_06.u + delta[1] * i
                            + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)dst)->unk_08 = ((S_819A764C_0 *)self)->unk_08.u + delta[2] * i++
                            - (func_80069EF8() & 0x3F);
        dst += 8;
    } while (i < 4);

    ((S_819A764C_0 *)self)->unk_2C = ((((S_819A764C_0 *)self)->unk_3E & 3) << 5) + 0x80;
    state = ((S_819A764C_0 *)self)->unk_3C.s;
    ((S_819A764C_0 *)self)->unk_2E = ((s16)((S_819A764C_0 *)self)->unk_3E >> 2) << 5;

    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto high_states;
    }
    tail_arg = self - 0x20;
    if (state == 0) {
        goto state_zero;
    }
    func_80025038();

high_states:
    if (state == 2) {
        goto state_two;
    }
    func_80025038();

state_zero:
    message = D_80020000;
    ASM_KEEP(message);   /* MATCH pin: retail delay-slot fill depends on it */
    message += 0x4B20;
    func_8004491C(tail_arg, message);

state_one:
    ((S_819A764C_0 *)self)->unk_3E = (func_80069EF8() & 3) + 2;
    ((S_819A764C_0 *)self)->unk_38 += 0xFFF7F7F8;
    ((S_819A764C_0 *)self)->unk_42 = func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8);
    ((S_819A764C_0 *)self)->unk_3C.u++;
    func_80025038();

state_two:
    page_base = 0x80080000;
    ASM_KEEP(page_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_819A764C_0_pre *)self)[-1].unk_00 |= 0x8000;
    ((S_819A764C_3 *)((void *)page_base))->unk_14A0 |= 0x8000;
}
