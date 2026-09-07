#include "common.h"

typedef struct {
    u8 pad_00_8c[0x8c];
    u8 *field_8c;
    u8 pad_90_96[6];
    u16 field_96;
    u8 pad_98_9b[3];
    u8 field_9b;
} S810AF65C_0;

typedef struct {
    u8 pad_00_02[2];
    s16 field_02;
    u8 pad_04_06[2];
    s16 field_06;
    u8 pad_08_0c[4];
    s32 field_0c;
    s32 field_10;
    s32 field_14;
} S810AF65C_1;

typedef struct {
    u8 pad_00_14[0x14];
    u16 field_14;
    u8 pad_16_24[0x0e];
    u8 field_24;
    u8 field_25;
} S810AF65C_2;

typedef struct {
    u8 pad_00_1c[0x1c];
    s32 field_1c;
    u8 pad_20_28[8];
    u8 field_28;
    u8 pad_29_6a[0x41];
    u16 field_6a;
} S810AF65C_3;

extern u8 D_80173C94[];
extern s32 D_80083460[3];
extern u8 D_80170E54[];
extern s16 D_8006CCE8[];
extern s16 D_8006CCD8[];

extern void func_800A2B04(S810AF65C_1 *, u8, u8);
extern void func_800AAA54(S810AF65C_0 *, S810AF65C_1 *, S810AF65C_2 *, u8 *);
extern void func_800AD4D0(S810AF65C_3 *);

void func_80172E5C(S810AF65C_0 *arg0, S810AF65C_1 *arg1,
                   S810AF65C_2 *arg2, S810AF65C_3 *arg3) {
    s32 timer;
    s32 index;
    s32 state;
    s32 value;
    s32 rounded;
    s32 other;
    s32 other_rounded;
    s32 value_2;
    s32 rounded_2;
    s32 *base;

    timer = arg0->field_96 - 1;
    index = ((u16)arg3->field_6a >> 9) & 7;
    state = arg0->field_9b;
    arg0->field_96 = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(arg3);
    arg0->field_96 = 2;
    arg0->field_9b = arg0->field_9b + 1;
    if (arg3->field_28 == 0) {
        arg1->field_14 = 0;
        arg1->field_10 = 0;
        arg1->field_0c = 0;
        arg0->field_96 = 0;
        func_800AAA54(arg0, arg1, arg2, D_80173C94);
        goto done;
    }
    if ((arg2->field_14 & 0x8000) != 0) {
        arg0->field_9b = 3;
        goto done;
    }
    goto state_1;

state_1:
    if ((s16)arg0->field_96 > 0) {
        goto done;
    }
    arg1->field_0c = (s16)D_8006CCD8[index] << 18;
    arg1->field_10 = (s16)D_8006CCE8[index] << 18;
    value = 5;
    if ((arg3->field_1c & 0x228) != 0) {
        value = 8;
    }
    arg0->field_96 = value;
    other = arg1->field_0c;
    rounded = other;
    if (other < 0) {
        rounded = other + 3;
    }
    value_2 = arg1->field_10;
    arg1->field_0c = other - (rounded >> 2);
    rounded_2 = value_2;
    if (value_2 < 0) {
        rounded_2 = value_2 + 3;
    }
    arg1->field_10 = value_2 - (rounded_2 >> 2);
    arg0->field_9b = arg0->field_9b + 1;
    goto state_tail;

state_2:
    arg1->field_0c = arg1->field_0c - ((s16)D_8006CCD8[index] << 15);
    arg1->field_10 = arg1->field_10 - ((s16)D_8006CCE8[index] << 15);
    if ((s16)arg0->field_96 != 0) {
        goto done;
    }
    if (arg3->field_28 == 0) {
        arg1->field_14 = 0;
        arg1->field_10 = 0;
        arg1->field_0c = 0;
        func_800AAA54(arg0, arg1, arg2, D_80173C94);
        goto done;
    }
    arg0->field_96 = 4;
    arg0->field_9b = arg0->field_9b + 1;

state_tail:
    goto done;

state_3:
    if ((timer << 16) == 0) {
        goto reset;
    }
    {
        s32 coordinate;
        s32 delta;

        coordinate = arg2->field_24 << 6;
        delta = arg1->field_02 - 0x20;
        arg1->field_0c = (coordinate - delta) << 15;
    }
    {
        s32 coordinate;
        s32 delta;

        coordinate = arg2->field_25 << 6;
        delta = arg1->field_06 - 0x20;
        arg1->field_10 = (coordinate - delta) << 15;
    }
    if ((s16)arg0->field_96 > 0) {
        goto done;
    }

reset:
    arg1->field_14 = 0;
    arg1->field_10 = 0;
    arg1->field_0c = 0;
    func_800A2B04(arg1, arg2->field_24, arg2->field_25);
    base = D_80083460;
    if (base[4] == (s32)((u8 *)arg3 - 0x20)) {
        base[4] = base[4] & 0x7fffffff;
    }
    arg0->field_8c = D_80170E54;

done:
    return;
}
