#include "common.h"

extern s16 D_800267B8[5];
extern s32 D_800814A0[3];

/* Updates a timed brightness pulse and clears the linked object flag on completion. */
void func_800252E4(u8 *effect, void *unused, u8 *target)
{
    u8 *object;
    u8 *linked_object;
    s16 timer;
    s32 intensity;
    s32 global_flags;
    u16 linked_flags;

    object = *(u8 **)(effect + 0x3C);
    D_800267B8[0] = 1;
    if ((u32)(object[0x13] - 0x33) < 4U) {
        *(u16 *)(effect - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u16 *)(effect + 2) -= 1;
    linked_object = *(u8 **)(*(u8 **)(effect + 0x3C) - 0x14);
    *(u16 *)(target + 0x14) &= 0xFF7F;
    *(u16 *)(linked_object + 0x14) |= 0x80;

    timer = *(s16 *)(effect + 2);
    if (timer < 20) {
        intensity = ((20 - timer) * 96) / 20 + 32;
        target[0xC] = intensity;
        target[0xD] = intensity;
        target[0xE] = intensity;
    } else if (timer < 40) {
        intensity = ((timer - 20) * 96) / 20 + 32;
        target[0xC] = intensity;
        target[0xD] = intensity;
        target[0xE] = intensity;
    }

    if (*(s16 *)(effect + 2) <= 0) {
        *(u16 *)(effect - 2) |= 0x8000;
        global_flags = D_800814A0[0];
        linked_flags = *(u16 *)(linked_object + 0x14);
        global_flags |= 0x8000;
        linked_flags &= 0xFF7F;
        D_800814A0[0] = global_flags;
        *(u16 *)(linked_object + 0x14) = linked_flags;
    }
}
