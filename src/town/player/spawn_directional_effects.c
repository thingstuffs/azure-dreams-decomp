#include "common.h"
#include "town/person/effects.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
} UnkStack;

s32 rsin(s32);
s32 rcos(s32);
s32 rand(void);

/* Spawns effects near the source with randomized positions and evenly spaced directions. */
void spawn_directional_effects(void *source, s32 effect_count)
{
    UnkStack effect;
    s32 angle;
    s32 spawned;
    s32 angle_step;

    if (effect_count != 0) {
        angle_step = 0x1000 / effect_count;
        spawned = 0;
        angle = rand();
        effect.field_A = *(u16 *)((u8 *)source + 0xA);
        effect.field_16 = -4;
        if (effect_count > 0) {
            do {
                spawned++;
                effect.x = (*(u16 *)((u8 *)source + 2) +
                            (rand() & 0x1F)) - 0x10;
                effect.y = (*(u16 *)((u8 *)source + 6) +
                            (rand() & 0x1F)) - 0x10;
                effect.field_C = rcos(angle) << 5;
                effect.field_10 = rsin(angle) << 5;
                spawn_person_offset_effect(&effect, (s16)angle);
                angle += angle_step;
            } while (spawned < effect_count);
        }
    }
}

