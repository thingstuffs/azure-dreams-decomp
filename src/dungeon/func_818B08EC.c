#include "common.h"

extern void func_800672D8();
extern void func_80067014();

/* Write two single-pixel values to VRAM and wait for completion. */
void func_800240EC(void) {
    s16 rect[4];
    u16 pixel;

    pixel = 0;
    rect[0] = 0x340;
    rect[1] = 0x100;
    rect[2] = 1;
    rect[3] = 1;
    func_800672D8(rect, &pixel);

    pixel = 0xFC00;
    rect[0] = 0x340;
    rect[1] = 0x180;
    rect[2] = 1;
    rect[3] = 1;
    func_800672D8(rect, &pixel);

    func_80067014(0);
}
