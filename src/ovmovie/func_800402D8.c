#include "common.h"

extern void func_80067014(s32 arg0);
extern void func_800671A8();

void func_800402D8(s32 arg0) {
    s16 sp10[4];
    s16 temp;
    s32 z;

    func_80067014(0);
    temp = 0x1E0;
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = temp;
    if (arg0 == 0) {
        temp = 0x1C0;
    }
    z = 0;
    sp10[3] = temp;
    func_800671A8(sp10, z, z, z);
    func_80067014(0);
}
