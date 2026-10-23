#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

extern void register_node(void *, u8 *, s32, void *);
extern s32 rsin(s32);
extern s32 rcos(s32);

extern u8 D_80099B18[];
extern s32 D_800DEDB0[3];
extern M2C_UNK D_800DEE38;

typedef struct S_80099C58_2 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80099C58_2;   /* s2 in spawn_radial_particle_burst */

typedef struct S_80099C58_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80099C58_3;   /* v1 in spawn_radial_particle_burst */

/* Spawns a central particle and sixteen particles moving radially from the given position. */
void spawn_radial_particle_burst(s16 x, s16 y, s16 z, s16 flags)
{
    ObjectNodeHeader *particle;
    ObjectPosition *motion;
    S_80099C58_2 *effect_state;
    SpriteFrameState *sprite;
    S_80099C58_3 *texture_data;
    void *texture;
    s32 spokes_left;
    s32 angle;
    s32 color;

    particle = allocate_flagged_object_node(0x212);
    if (particle != NULL) {
        effect_state = (s8 *)particle + 0x20;
        motion = particle->position;
        particle->unk_10 = D_80099B18;
        motion->x.w.i = x;
        effect_state->unk_12 = x;
        motion->y.w.i = y;
        effect_state->unk_14 = y;
        motion->z.w.i = z;
        effect_state->unk_16 = z;
        effect_state->unk_10 = 0;
        sprite = particle->sprite;
        if (flags & 2) {
            texture = D_800DEDB0;
            sprite->unk_00 = texture;
            color = 0x808080;
        } else if (flags & 4) {
            texture = &D_800DEE38;
            sprite->unk_00 = texture;
            color = 0x808080;
        } else {
            texture = effect_sprite_sources;
            sprite->unk_00 = texture;
            color = 0x808080;
        }
        texture_data = sprite->unk_00;
        texture_data = texture_data->unk_04;
        sprite->flags |= 0x8C;
        sprite->tpage_abr = 0x20;
        sprite->color.word = color;
        sprite->scale_y = ONE;
        sprite->scale_x = ONE;
        sprite->source = texture_data;
        register_node(particle, project_sprite_chain, color, sprite);
    }

    for (spokes_left = 0x10; spokes_left > 0; spokes_left--) {
        particle = allocate_flagged_object_node(0x212);
        if (particle != NULL) {
            effect_state = (s8 *)particle + 0x20;
            angle = spokes_left << 8;
            motion = particle->position;
            particle->unk_10 = D_80099B18;
            effect_state->unk_0E = 1;
            motion->x.w.i = x;
            effect_state->unk_12 = x;
            motion->y.w.i = y;
            effect_state->unk_14 = y;
            motion->z.w.i = z;
            effect_state->unk_16 = z;
            motion->velocity_z = rcos(angle) << 7;
            motion->velocity_x = rsin(angle) << 7;
            effect_state->unk_10 = 0;
            sprite = particle->sprite;
            if (flags & 2) {
                texture = D_800DEDB0;
                sprite->unk_00 = texture;
                color = 0x808080;
            } else if (flags & 4) {
                texture = &D_800DEE38;
                sprite->unk_00 = texture;
                color = 0x808080;
            } else {
                texture = effect_sprite_sources;
                sprite->unk_00 = texture;
                color = 0x808080;
            }
            texture_data = sprite->unk_00;
            texture_data = texture_data->unk_04;
            sprite->flags |= 0x8C;
            sprite->tpage_abr = 0x20;
            sprite->color.word = color;
            sprite->scale_y = ONE;
            sprite->scale_x = ONE;
            sprite->source = texture_data;
            register_node(particle, project_sprite_chain, color, sprite);
        }
    }
}
