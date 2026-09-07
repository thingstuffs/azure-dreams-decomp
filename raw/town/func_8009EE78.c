#include "common.h"

extern void func_80033D08(void *arg0);
extern u8 D_80080000[0x14A4];
__asm__(".set D_80080000, 0x80080000");
void func_8009C5D8(void *arg0, void *arg1, u8 *arg2)
{
    s32 temp_v0;

    temp_v0 = arg2[0xE] - 6;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }
    arg2[0xE] = temp_v0;
    arg2[0xD] = temp_v0;
    arg2[0xC] = temp_v0;
    if (temp_v0 != 0) {
        return;
    }
    func_80033D08(arg0);
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    *(s32 *)(D_80080000 + 0x14A0) |= 0x8000;
}
