#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_800672D8();

extern u8 D_80024640[];
extern u8 D_80024660[];
extern u8 D_80024680[];
extern u8 D_800246C0[];
extern s32 D_800814A0[];

void func_80023BCC(void *arg0)
{
    s16 rect[4];
    s16 phase;
    u8 *image;
    u16 timer;

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
        image = D_80024660;
        rect[0] = 0x40;
        func_800672D8(rect, image);
        rect[0] = 0x50;
        func_800672D8(rect, image - 0x20);
    } else {
        image = D_80024640;
        rect[0] = 0x40;
        func_800672D8(rect, image);
        rect[0] = 0x50;
        func_800672D8(rect, image + 0x20);
    }

    rect[1] = 0x1F8;
    phase = (s16)FIELD(arg0, u16, 0x5E) % 3;
    switch (phase) {
    case 0:
        image = D_800246C0;
        rect[0] = 0xC0;
        func_800672D8(rect, image);
        rect[0] = 0xD0;
        rect[2] = 0x20;
        func_800672D8(rect, image - 0x40);
        break;
    case 1:
        image = (u8 *)0x80020000;
        ASM_KEEP(image);
        image += 0x4680;
        rect[0] = 0xE0;
        func_800672D8(rect, image);
        rect[0] = 0xC0;
        rect[2] = 0x20;
        func_800672D8(rect, image + 0x20);
        break;
    case 2:
        rect[0] = 0xC0;
        rect[2] = 0x30;
        func_800672D8(rect, D_80024680);
        break;
    default:
        break;
    }

    timer = FIELD(arg0, u16, 0x5E) - 1;
    FIELD(arg0, u16, 0x5E) = timer;
    if ((s16)timer <= 0) {
        u8 *page = (u8 *)0x80080000;
        FIELD(arg0, u16, -2) |= 0x8000;
        ASM_KEEP(page);
        (*(s32 *)(page + 0x14A0)) |= 0x8000;
    }
}
