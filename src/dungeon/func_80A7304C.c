#include "common.h"


extern void func_80047784();
extern void func_8009C12C();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_80170E54;
extern u8 D_80174140;
extern u8 D_80174170;


typedef struct S_8017284C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017284C_0;   /* arg0 in func_8017284C */

typedef struct S_8017284C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017284C_1;   /* arg2 in func_8017284C */

typedef struct S_8017284C_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_8017284C_2;   /* arg3 in func_8017284C */

typedef struct S_8017284C_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017284C_3;   /* arg1 in func_8017284C */

void func_8017284C(S_8017284C_0 *arg0, S_8017284C_3 *arg1, S_8017284C_1 *arg2, void *arg3)
{
    s16 timer;
    s32 table_y;
    s32 index;
    s32 wrapped;
    s32 decay_x;
    s32 decay_y;
    s32 z_velocity;
    s32 scaled;
    s32 state_value;
    s32 state;
    register u8 increment_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    state = arg0->unk_9B;
    if (state == 1) {
        goto state1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto done;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

state0:
    if (arg2->unk_14 & 0x8000) {
        arg0->unk_9B = 3;
        arg0->unk_96.s = 0;
        arg2->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_8017284C_2 *)arg3)->unk_2A, 1);
        goto done;
    }

    state_value = ((u16)((S_8017284C_2 *)arg3)->unk_2A >> 9) & 7;
    index = state_value + 4;
    wrapped = index;
    if (index < 0) {
        wrapped = state_value + 11;
    }
    index -= wrapped & 0x18;
    arg1->unk_0C =
        (*(s16 *)((u8 *)(&D_8006CCD8) + (index * 2))) * 0x60000;
    table_y = (*(s16 *)((u8 *)(&D_8006CCE8) + (index * 2)));
    arg1->unk_14 = 0;
    arg1->unk_10 = table_y * 0x60000;
    arg2->unk_2C = &D_80174140;
    func_80047784(arg2,
        (*(u8 *)((u8 *)(&D_80174140) + (((D_80083228[0] + ((S_8017284C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7))),
        0);
    increment_value = arg0->unk_9B;
    arg0->unk_96.s = 0;
    goto increment_state;

state1:
    decay_x = arg1->unk_0C;
    decay_y = arg1->unk_10;
    arg1->unk_0C = decay_x - (decay_x >> 2);
    arg1->unk_10 = decay_y - (decay_y >> 2);
    if (arg2->unk_14 & 0xE000) {
        arg2->unk_2C = &D_80174170;
        func_80047784(arg2,
            (*(u8 *)((u8 *)(&D_80174170) + (((D_80083228[0] + ((S_8017284C_2 *)arg3)->unk_2A + 0x100) >> 9) & 7))),
            0);
        increment_value = arg0->unk_9B;
        arg0->unk_96.s = 0x14;
        goto increment_state;
    }
    goto done;

state2:
    timer = arg0->unk_96.u - 1;
    z_velocity = arg1->unk_14;
    arg0->unk_96.s = timer;
    if (timer < 12) {
        z_velocity += 0x1400;
    } else {
        z_velocity += 0x20000;
    }
    arg1->unk_14 = z_velocity;
    arg0->unk_90 += z_velocity;

    if (arg0->unk_96.s == 0x11) {
        func_800A56E0(0x808);
        index = ((u16)((S_8017284C_2 *)arg3)->unk_2A >> 9) & 7;
        scaled = (*(s16 *)((u8 *)(&D_8006CCD8) + (index * 2))) * 0x30000;
        arg1->unk_0C = scaled + (scaled >> 2);
        scaled = (*(s16 *)((u8 *)(&D_8006CCE8) + (index * 2))) * 0x30000;
        arg1->unk_10 = scaled + (scaled >> 2);
    }

    if (((arg2->unk_04 == 3) &&
         (arg2->unk_14 & 0x1000)) ||
        (arg2->unk_14 & 0x8000)) {
        func_8009C12C(arg3, arg2, ((S_8017284C_2 *)arg3)->unk_2A, 1);
    }

    if (((arg2->unk_04 == 5) &&
         (arg2->unk_14 & 0x1000)) ||
        (arg2->unk_14 & 0x8000)) {
        arg1->unk_0C =
            ((((arg2->unk_24 << 6) + 0x20) << 16) -
             arg1->unk_00) / arg0->unk_96.s;
        arg1->unk_10 =
            ((((arg2->unk_25 << 6) + 0x20) << 16) -
             arg1->unk_04) / arg0->unk_96.s;
    }

    if ((arg0->unk_96.s <= 0) ||
        (arg2->unk_14 & 0x8000)) {
        increment_value = arg0->unk_9B;
        goto increment_state;
    }
    goto done;

increment_state:
    increment_value++;
    arg0->unk_9B = increment_value;
    goto done;

state3:
    if ((arg0->unk_96.s <= 0) ||
        (arg2->unk_14 & 0x8000)) {
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800AD594(arg3, 0x100);
        arg0->unk_8C = &D_80170E54;
        D_8008346C[0] = 0;
        arg0->unk_98 &= 0xFFF7;
        func_800A4ACC(arg3);
        if (((S_8017284C_2 *)arg3)->unk_6D == 0) {
            ((S_8017284C_2 *)arg3)->unk_46 &= 0x7FFF;
            goto done;
        }
        D_800E3DE8[0] = (u8 *)arg3 - 0x20;
    }
    goto done;

done:
    return;
}
