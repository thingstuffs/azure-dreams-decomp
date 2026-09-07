#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 field8;
    s32 unkC;
    s32 field10;
} PadState;

typedef struct {
    s32 unk0;
    s32 field4;
    s32 field8;
    s32 unkC;
    s32 field10;
    s32 pad14[23];
    s32 field70;
} MenuState;

extern PadState D_80083160;
extern void func_80026370(s32, s32);
extern s32 func_80026388(s32, s32, s32);
extern s16 func_80053DA8(s32);

void func_8002640C(MenuState *arg0) {
    s32 direction = 0;
    s32 buttons;
    s32 cursor;
    s32 value;
    PadState *pad = &D_80083160;

    if (pad->field8 != 0) {
        if (pad->field10 & 0xC) {
            arg0->field4 = 0;
            buttons = pad->field10;
            if (buttons & 4) {
                direction = -1;
            } else if (buttons & 8) {
                direction = 1;
            }
        } else if (pad->field8 & 0xC) {
            cursor = arg0->field4;
            if (cursor >= 9) {
                arg0->field4 = cursor - 1;
                buttons = pad->field8;
                if (buttons & 4) {
                    direction = -1;
                } else if (buttons & 8) {
                    direction = 1;
                }
            } else {
                arg0->field4 = cursor + 1;
            }
        }

        if (direction != 0) {
            func_80053DA8(0x502);
            value = func_80026388(direction, arg0->field8, arg0->field10);
            arg0->field8 = value;
            func_80026370(arg0->field70, value);
        }
    }
}
