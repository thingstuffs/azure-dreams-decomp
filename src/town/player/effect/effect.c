#include "common.h"
#include "engine/window.h"
#include "town/player.h"
#include "town/player/effect.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} UnkStackData;

extern UnkStackData D_80088D60;

/* Decrements an object's countdown and triggers a randomized update when it expires. */
void tick_random_radial_spawns(void *object, s32 target)
{
    UnkStackData update_data;
    u16 ticks_left;

    update_data = D_80088D60;
    ticks_left = *(u16 *)((u8 *)object + 0x6C) - 1;
    *(u16 *)((u8 *)object + 0x6C) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        *(u16 *)((u8 *)object + 0x6C) = (u16)(scale_random_to_unsigned_halfword_limit(0xA) + 5);
        spawn_radial_objects(target, &update_data, (scale_random_to_unsigned_halfword_limit(2) & 0xFFFF) + 1);
    }
}
