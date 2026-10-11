#include "modules/dungeon_ovl_184c800.h"


/* Move the effect, count down its timer, then fade its sprite to black. */
void func_80024D44(void *effect, S_8182D544_2 *motion, S_8182D544_3 *sprite)
{
    s16 state;
    s32 delta_y;
    s32 delta_z;
    s32 fade_step;
    u16 timer;
    u8 brightness;
    S_8182D544_1 *object;

    object = ((S_8182D544_0 *)effect)->unk_00;
    object->unk_0C |= 0x8000;

    delta_y = motion->unk_10;
    delta_z = motion->unk_14;
    motion->unk_00 += motion->unk_0C;
    motion->unk_04 += delta_y;
    motion->unk_08 += delta_z;

    state = ((S_8182D544_0 *)effect)->unk_4C.s;
    switch (state) {
    case 0:
        timer = ((S_8182D544_0 *)effect)->unk_48 - 1;
        ((S_8182D544_0 *)effect)->unk_48 = timer;
        if ((timer << 16) <= 0) {
            func_8004491C((u8 *)effect - 0x20, func_80045340);
            ((S_8182D544_0 *)effect)->unk_4C.u++;
        }
        break;

    case 1:
        func_800478B8(sprite);
        if (sprite->unk_14 & 0x6000) {
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
        }

        fade_step = (rand() & 0xF) + 9;
        if (fade_step >= sprite->unk_0C.at00.v) {
            sprite->unk_0C.at00u.v = 0;
            ((S_8182D544_0_pre *)effect)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }

        brightness = sprite->unk_0C.at02.v - fade_step;
        sprite->unk_0C.at02.v = brightness;
        sprite->unk_0C.at01.v = brightness;
        sprite->unk_0C.at00.v = brightness;
        break;
    }
}
