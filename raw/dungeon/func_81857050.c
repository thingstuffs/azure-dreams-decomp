#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

typedef struct {
    s32 x, y, z;
    s32 vx, vy, vz;
} EffectMotion;





/* Updates effect motion, waits for its timer, then fades its sprite to black. */
void func_80024850(void *effect, EffectMotion *motion, void *sprite) {
    void *owner = *(void **)effect;
    s32 z_velocity;
    s16 state;
    u16 timer;

    *(u16 *)((s8 *)owner + 0x52) |= 0x8000;

    z_velocity = motion->vz;
    if (z_velocity != 0) {
        z_velocity -= 0x20000;
    }
    motion->vz = z_velocity;
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;

    state = *(s16 *)((s8 *)effect + 0x4C);
    switch (state) {
    case 0:
        timer = *(u16 *)((s8 *)effect + 0x48) - 1;
        *(u16 *)((s8 *)effect + 0x48) = timer;
        if ((s16)timer <= 0) {
            func_8004491C((s8 *)effect - 0x20, (s32)func_80045340);
            *(u16 *)((s8 *)effect + 0x4C) += 1;
        }
        break;

    case 1:
        func_800478B8(sprite);
        if (*(u16 *)((s8 *)sprite + 0x14) & 0x6000) {
            *(s8 *)((s8 *)sprite + 4) = 0;
            *(s8 *)((s8 *)sprite + 5) = 0;
        }
        if (*(u8 *)((s8 *)sprite + 0xC) <= *(s16 *)((s8 *)effect + 0x4A)) {
            *(u32 *)((s8 *)sprite + 0xC) = 0;
            *(u16 *)((s8 *)effect - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        {
            u8 brightness = *(u8 *)((s8 *)sprite + 0xE) - *(u8 *)((s8 *)effect + 0x4A);
            *(u8 *)((s8 *)sprite + 0xE) = brightness;
            *(u8 *)((s8 *)sprite + 0xD) = brightness;
            *(u8 *)((s8 *)sprite + 0xC) = brightness;
        }
        break;
    }
}
