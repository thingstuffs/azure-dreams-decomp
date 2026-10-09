#include "modules/dungeon_ovl_185e800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"



/* Waits for the effect delay, then moves and fades the sprite until it expires. */
void func_80024688(void *effect, DelayPosition *motion, void *sprite) {
    void *owner;
    s16 phase;
    u16 delay;
    u8 shade;
    DelayPosition *position = motion;

    owner = *(void **)effect;
    *(u16 *)((u8 *)owner + 0x52) |= 0x8000;
    phase = *(s16 *)((u8 *)effect + 0x4C);
    switch (phase) {
    case 0:
        delay = *(u16 *)((u8 *)effect + 0x48) - 1;
        *(u16 *)((u8 *)effect + 0x48) = delay;
        if ((delay << 0x10) <= 0) {
            func_8004491C((u8 *)effect - 0x20, func_80045340);
            *(u16 *)((u8 *)effect + 0x4C) += 1;
        }
        break;

    case 1:
        position->f0 += position->fC;
        position->f4 += position->f10;
        func_800478B8(sprite);

        if (*(u16 *)((u8 *)sprite + 0x14) & 0x6000) {
            *(u8 *)((u8 *)sprite + 4) = 0;
            *(u8 *)((u8 *)sprite + 5) = 0;
        }

        if ((s32)*(u8 *)((u8 *)sprite + 0xC) <= *(s16 *)((u8 *)effect + 0x4A)) {
            *(s32 *)((u8 *)sprite + 0xC) = 0;
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }

        shade = *(u8 *)((u8 *)sprite + 0xD) - *(u8 *)((u8 *)effect + 0x4A);
        *(u8 *)((u8 *)sprite + 0xD) = shade;
        *(u8 *)((u8 *)sprite + 0xC) = shade;
        *(u8 *)((u8 *)sprite + 0xE) -= *(u8 *)((u8 *)effect + 0x4A) * 2;
        break;
    }
}
