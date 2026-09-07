#include "common.h"

typedef struct {
    u8 pad0[0x92];
    s16 field92;
    u8 pad94[2];
    s16 field96;
    u8 pad98[3];
    u8 field9B;
} State;

typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[4];
    s32 fieldC;
    s32 field10;
    s32 field14;
} Motion;

typedef struct {
    u8 pad0[0x1C];
    u16 field1C;
    u16 field1E;
    u8 pad20[4];
    u8 field24;
    u8 field25;
} Params;

typedef struct {
    u8 pad0[0x1C];
    s32 field1C;
    u8 pad20[0x6A];
    u16 field8A;
} Extra;

extern volatile s16 D_80013714[8];
extern void func_800A2B04(Motion *, u8, u8);
extern s32 func_800644B8(s32);

s32 func_800ABDBC(State *arg0, Motion *arg1, Params *arg2, Extra *arg3) {
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_a0;
    u16 temp_v0;
    s16 temp_v0_2;

    temp_v1 = arg0->field9B;
    switch (temp_v1) {
    case 0:
        arg0->field96 = 0x10;
        arg3->field1C &= 0xFFFBFFFF;
        if ((*D_80013714 & 2) != 0) {
            func_800A2B04(arg1, arg2->field24, arg2->field25);
            arg2->field1C = 0x1000;
            arg2->field1E = 0x1000;
            arg0->field9B = 2;
        } else {
            arg0->field9B = (u8) (arg0->field9B + 1);
            arg3->field8A = 0x800 / arg0->field96;
        }
        return 0;

    case 1:
        if ((arg0->field96 + 2) >= 0x10) {
            arg1->field10 = 0;
            arg1->fieldC = 0;
        } else {
            temp_a0 = arg0->field96 - 2;
            if (temp_a0 > 0) {
                temp_v1 = arg1->field6;
                temp_v1 -= 0x20;
                arg1->fieldC = (((arg2->field24 << 6) - (temp_v1_2 = arg1->field2 - 0x20)) << 16) / temp_a0;
                arg1->field10 = (((arg2->field25 << 6) - temp_v1) << 16) / (arg0->field96 - 2);
            } else {
                arg1->field10 = 0;
                arg1->fieldC = 0;
                func_800A2B04(arg1, arg2->field24, arg2->field25);
            }
        }
        if (arg0->field96 != 0) {
            arg1->field14 = ((-(func_800644B8(arg0->field96 << 6) >> 4) - (temp_v1 = arg0->field92 + 0x20)) << 16) / arg0->field96;
        }
        temp_v0 = arg2->field1C + arg3->field8A;
        arg2->field1C = temp_v0;
        arg2->field1E = temp_v0;
        temp_v0_2 = (u16) arg0->field96 - 1;
        arg0->field96 = temp_v0_2;
        if ((s16) temp_v0_2 < 0) {
            arg1->field14 = 0;
            arg1->field10 = 0;
            arg1->fieldC = 0;
            func_800A2B04(arg1, arg2->field24, arg2->field25);
            arg0->field92 = -0x20;
            arg0->field9B = (u8) (arg0->field9B + 1);
        }
        return 0;

    case 2:
        return 1;

    default:
        return 0;
    }
}
