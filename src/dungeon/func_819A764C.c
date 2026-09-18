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
extern s32 D_800814A0[3];
extern void func_8004491C();
extern s16 func_8006649C();
extern s32 func_80069EF8(void);

/* Update randomized intermediate points and advance the effect state. */
void func_80024E4C(void *self)
{
    s16 point_step[3];
    s32 state;
    s32 point_index;
    void *point_slot;
    void *object_base;
    S_819A764C_1 *linked_object;
    u8 *message;

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
    return;

high_states:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    message = D_80024B20;

    func_8004491C(object_base, message);

state_one:
    ((S_819A764C_0 *)self)->unk_3E = (func_80069EF8() & 3) + 2;
    ((S_819A764C_0 *)self)->unk_38 += 0xFFF7F7F8;
    ((S_819A764C_0 *)self)->unk_42 = func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8);
    ((S_819A764C_0 *)self)->unk_3C.u++;
    return;

state_two:

    ((S_819A764C_0_pre *)self)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
