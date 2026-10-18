#include "shared/object_flags.h"
#include "common.h"

extern void func_80033D08(void *object);
// Fade the primitive to black, then finalize the object and set completion flags.
void fade_object_primitive(void *object, void *unusedContext, u8 *primitive)
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
    object_flag_block.flags |= 0x8000;
}
