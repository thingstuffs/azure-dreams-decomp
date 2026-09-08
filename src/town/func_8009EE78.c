#include "common.h"

extern void func_80033D08(void *arg0);
extern u8 D_80080000[0x14A4];
__asm__(".set D_80080000, 0x80080000");
// Fade the primitive to black, then finalize the object and set completion flags.
void func_8009C5D8(void *object, void *unusedContext, u8 *primitive)
{
    s32 brightness;

    brightness = primitive[0xE] - 6;
    if (brightness < 0) {
        brightness = 0;
    }
    primitive[0xE] = brightness;
    primitive[0xD] = brightness;
    primitive[0xC] = brightness;
    if (brightness != 0) {
        return;
    }
    func_80033D08(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    *(s32 *)(D_80080000 + 0x14A0) |= 0x8000;
}
