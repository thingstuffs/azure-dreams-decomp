#include "common.h"

extern void func_800672D8();
extern void func_80067014();

void func_800240EC(void) {
    s16 first[4];
    u16 second;

    second = 0;
    first[0] = 0x340;
    first[1] = 0x100;
    first[2] = 1;
    first[3] = 1;
    func_800672D8(first, &second);

    second = 0xFC00;
    first[0] = 0x340;
    first[1] = 0x180;
    first[2] = 1;
    first[3] = 1;
    func_800672D8(first, &second);

    func_80067014(0);
}
