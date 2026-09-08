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

/* Update randomized intermediate points and advance the effect state. */
void func_819A764C(void *effect_data)
{
    s16 point_step[3];
    s32 state;
    s32 point_index;
    register void *point_slot ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *object_base;
    S_819A764C_1 *linked_object;
    register u32 page_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *message;
    register void *self ASM_REG("$18") = effect_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    linked_object = ((S_819A764C_0 *)self)->unk_00;
    linked_object->unk_52 |= 0x8000;

    point_step[0] = (((S_819A764C_0 *)self)->unk_24 - ((S_819A764C_0 *)self)->unk_04.s) >> 2;
    point_step[1] = (((S_819A764C_0 *)self)->unk_26 - ((S_819A764C_0 *)self)->unk_06.s) >> 2;
    point_step[2] = (((S_819A764C_0 *)self)->unk_28 - ((S_819A764C_0 *)self)->unk_08.s) >> 2;
    point_index = 1;
    point_slot = self + 8;

    do {
        ((S_819A764C_2 *)point_slot)->unk_04 = ((S_819A764C_0 *)self)->unk_04.u + point_step[0] * point_index
                            + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)point_slot)->unk_06 = ((S_819A764C_0 *)self)->unk_06.u + point_step[1] * point_index
                            + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)point_slot)->unk_08 = ((S_819A764C_0 *)self)->unk_08.u + point_step[2] * point_index++
                            - (func_80069EF8() & 0x3F);
        point_slot += 8;
    } while (point_index < 4);

    ((S_819A764C_0 *)self)->unk_2C = ((((S_819A764C_0 *)self)->unk_3E & 3) << 5) + 0x80;
    state = ((S_819A764C_0 *)self)->unk_3C.s;
    ((S_819A764C_0 *)self)->unk_2E = ((s16)((S_819A764C_0 *)self)->unk_3E >> 2) << 5;

    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto high_states;
    }
    object_base = self - 0x20;
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
    ASM_KEEP(message);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    message += 0x4B20;
    func_8004491C(object_base, message);

state_one:
    ((S_819A764C_0 *)self)->unk_3E = (func_80069EF8() & 3) + 2;
    ((S_819A764C_0 *)self)->unk_38 += 0xFFF7F7F8;
    ((S_819A764C_0 *)self)->unk_42 = func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8);
    ((S_819A764C_0 *)self)->unk_3C.u++;
    func_80025038();

state_two:
    page_base = 0x80080000;
    ASM_KEEP(page_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ((S_819A764C_0_pre *)self)[-1].unk_00 |= 0x8000;
    ((S_819A764C_3 *)((void *)page_base))->unk_14A0 |= 0x8000;
}
