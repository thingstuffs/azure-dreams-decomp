/* Radial burst (G00343). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B10B4. */
#include "dungeon/effect/radial_burst_g00343.h"

/* Emits scattered effects at evenly spaced angles unless the tile to the left blocks them. */
void emit_scattered_effects_unless_blocked(void *source)
{
    DungeonEffect effect;
    s32 tile_x;
    s32 tile_y;
    s32 angle;
    s32 effect_count;
    s32 angle_step;
    s32 emitted;
    u16 source_field_a;

    tile_x = *(s16 *)((u8 *)source + 2) / 64 - 1;
    tile_y = *(s16 *)((u8 *)source + 6) / 64;
    get_offset_map_cell_value_and_flags(tile_x, tile_y, 0, &effect.flags);
    if (effect.flags & 0x400) {
        spawn_randomized_radial_burst(source);
        return;
    }

    effect_count = (rand() & 7) | 4;
    angle_step = 0x1000 / effect_count;
    angle = rand();
    source_field_a = *(u16 *)((u8 *)source + 0xA);
    effect.field_16 = -4;
    effect.field_A = source_field_a;
    for (emitted = 0; emitted < effect_count; emitted++) {
        effect.x = *(u16 *)((u8 *)source + 2) +
                   (rand() & 0x1F) - 0x10;
        effect.y = *(u16 *)((u8 *)source + 6) +
                   (rand() & 0x1F) - 0x10;
        effect.field_C = func_80064584(angle) << 5;
        effect.field_10 = func_800644B8(angle) << 5;
        spawn_opposite_offset_effect(&effect, angle);
        angle += angle_step;
    }
}

/* Spawns a randomized radial burst of particles at the given position. */
void spawn_randomized_radial_burst(MovingPosition *origin)
{
    s32 particle_count;
    s32 angle_step;
    s32 angle;
    s32 particle_index;
    s32 velocity_y;
    S_800B6814_1 *motion;
    void *particle;
    SpriteFrameState *sprite;
    S_800B6814_3 *effect_state;

    particle_count = (rand() & 0xF) | 8;
    angle_step = 0x1000 / particle_count;
    particle_index = 0;
    angle = rand();
    if ((u16)particle_count != 0) {
        do {
            particle = allocate_flagged_object_node(0x212);

            if (particle != NULL) {
                motion = ((S_800B6814_0 *)particle)->unk_08;
                sprite = ((S_800B6814_0 *)particle)->unk_0C;
                ((S_800B6814_0 *)particle)->unk_10 = &D_800B63A8;
                register_node(particle, project_sprite_chain);
                motion->unk_02 =
                    origin->unk_02 + (func_80064584(angle) >> 11);
                motion->unk_06 =
                    origin->unk_06 + (func_800644B8(angle) >> 11);
                motion->unk_0A = origin->unk_0A;
                motion->unk_0C = func_80064584(angle) << 6;
                motion->unk_10 = func_800644B8(angle) << 6;
                motion->unk_14 = 0xFFFD0000;
                ((S_800B6814_0 *)particle)->unk_20 = -motion->unk_0C >> 6;
                velocity_y = motion->unk_10;
                effect_state = (u8 *)particle + 0x20;
                effect_state->unk_08 = 0x2000;
                effect_state->unk_04 = -velocity_y >> 6;
                select_record_entry_and_value(sprite, &D_800DEC00, 0);
                sprite->color.word = 0x808080;
                sprite->scale_y = 0x400;
                sprite->scale_x = 0x400;
                sprite->tpage_abr = 0x60;
                sprite->clut = 0x7E80;
                sprite->flags |= 0x10C;
                effect_state->unk_0E = (rand() & 3) | 0x10;
                effect_state->unk_16 = 0x10;
                effect_state->unk_14 = 0x10;
                effect_state->unk_18 = 8;
            }
            particle_index++;
            angle += angle_step;
        } while (particle_index < particle_count);
    }
}
