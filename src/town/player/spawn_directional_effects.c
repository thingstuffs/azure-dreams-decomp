#include "common.h"
#include "town/person/effects.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "town/player.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 z;
    s32 velocity_x;
    s32 velocity_y;
    u8 pad14[2];
    s16 field_16;
} UnkStack;

/* Spawns effects near the source with randomized positions and evenly spaced directions. */
void spawn_directional_effects(ObjectPosition *source, s32 effect_count)
{
    UnkStack effect;
    s32 angle;
    s32 spawned;
    s32 angle_step;

    if (effect_count != 0) {
        angle_step = 0x1000 / effect_count;
        spawned = 0;
        angle = rand();
        effect.z = source->z.unsigned_parts.integer;
        effect.field_16 = -4;
        if (effect_count > 0) {
            do {
                spawned++;
                effect.x = (source->x.unsigned_parts.integer +
                            (rand() & 0x1F)) - 0x10;
                effect.y = (source->y.unsigned_parts.integer +
                            (rand() & 0x1F)) - 0x10;
                effect.velocity_x = rcos(angle) << 5;
                effect.velocity_y = rsin(angle) << 5;
                spawn_person_offset_effect(&effect, (s16)angle);
                angle += angle_step;
            } while (spawned < effect_count);
        }
    }
}

