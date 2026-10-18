#include "modules/dungeon_ovl_18d0850.h"

void write_fixed_palette_pixels(void *unused0, void *unused1, void *unused2) {
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
