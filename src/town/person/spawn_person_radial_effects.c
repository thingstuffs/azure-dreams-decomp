#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libgte.h"
#include "sdk/libc.h"
#include "town/person/effects.h"


typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    u16 z;
    s32 a;
    s32 b;
    s16 unk14;
    s16 c;
} StackRecord;

   /* base in spawn_person_radial_effects */

/* Spawns effects near the source position in evenly spaced directions. */
void spawn_person_radial_effects(void *source) {
    MovingPosition *origin;
    StackRecord effect;
    s32 angle;
    s32 effect_count;
    s32 angle_step;
    s32 effects_spawned;
    s16 effect_angle;
    __typeof__(effect_count != 0) cond_1;

    origin = source;
    effect_count = (rand() & 7) | 4;
    angle_step = 0x1000 / effect_count;
    effects_spawned = 0;
    angle = rand();
    effect.z = origin->z;
    effect.c = -4;
    cond_1 = effect_count != 0;
    if (cond_1) {
        do {
            effects_spawned += 1;
            effect.x = (origin->x + (rand() & 0x1F)) - 0x10;
            effect.y = (origin->y + (rand() & 0x1F)) - 0x10;
            effect.a = rcos(angle) << 5;
            effect.b = rsin(angle) << 5;
            effect_angle = angle;
            spawn_person_offset_effect(&effect, effect_angle);
            angle += angle_step;
        } while (effects_spawned < effect_count);
    }
}

