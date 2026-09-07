#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_8006E854(s16 *rect, u8 *image);

extern s32 D_80084D5C;
extern u8 D_805305B8[];
extern u8 D_805305D8[];
extern u8 D_805305F8[];
extern u8 D_80530638[];

typedef struct CallbackState {
    u8 pad_00[0x5C];
    s16 state;
    u16 timer;
} CallbackState;

typedef struct CallbackOwner {
    u16 flags;
    CallbackState state;
} CallbackOwner;

void func_8052DC78(CallbackState *arg0)
{
    s16 rect[4];
    s16 phase;
    u8 *image;
    s32 timer;

    rect[2] = 0x10;
    rect[3] = 1;

    switch (FIELD(arg0, s16, 0x5C)) {
    case 0:
        FIELD(arg0, u16, 0x5E) = 0x78;
        FIELD(arg0, u16, 0x5C)++;
        break;
    case 1:
        break;
    default:
        return;
    }

    rect[1] = 0x1D0;
    if ((FIELD(arg0, u16, 0x5E) >> 1) & 1) {
        image = D_805305D8;
        rect[0] = 0x40;
        func_8006E854(rect, image);
        rect[0] = 0x50;
        func_8006E854(rect, image - 0x20);
    } else {
        image = D_805305B8;
        rect[0] = 0x40;
        func_8006E854(rect, image);
        rect[0] = 0x50;
        func_8006E854(rect, image + 0x20);
    }

    rect[1] = 0x1F8;
    phase = (s16)FIELD(arg0, u16, 0x5E) % 3;
    switch (phase) {
    case 0:
        image = D_80530638;
        rect[0] = 0xC0;
        func_8006E854(rect, image);
        rect[0] = 0xD0;
        rect[2] = 0x20;
        func_8006E854(rect, image - 0x40);
        break;
    case 1:
        rect[0] = 0xE0;
        func_8006E854(rect, D_805305F8);
        image = D_805305F8;
        rect[0] = 0xC0;
        rect[2] = 0x20;
        func_8006E854(rect, image + 0x20);
        break;
    case 2:
        rect[0] = 0xC0;
        rect[2] = 0x30;
        func_8006E854(rect, D_805305F8);
        break;
    default:
        break;
    }

    timer = FIELD(arg0, u16, 0x5E) - 1;
    FIELD(arg0, u16, 0x5E) = timer;
    if ((s16)timer <= 0) {
        CallbackOwner *owner = (CallbackOwner *)((u8 *)arg0 - 2);

        *(u16 *)owner |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}
