#include "common.h"

extern void func_800478B8();
extern s32 D_800814A0;

/* Advances and darkens a moving effect, updates its visual, and propagates status flags. */
void func_8002609C(u8 *effect, u8 *motion, u8 *visual)
{
    s32 velocity;
    s32 acceleration;
    s32 next_velocity;
    s32 position;
    u8 shade;

    velocity = *(s32 *)(motion + 0x14);
    if (velocity != 0) {
        acceleration = 0x18000;
        next_velocity = velocity;
        ASM_KEEP(next_velocity);
        position = *(s32 *)(motion + 8);
        next_velocity += acceleration;
        *(s32 *)(motion + 0x14) = next_velocity;
        do {
            position += velocity;
        } while (0);
        *(s32 *)(motion + 8) = position;

        shade = visual[0xE] - 0x20;
        visual[0xE] = shade;
        visual[0xD] = shade;
        visual[0xC] = shade;
    }

    func_800478B8(visual, motion, velocity);
    if (*(u16 *)(visual + 0x14) & 0x6000) {
        *(u16 *)(effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
