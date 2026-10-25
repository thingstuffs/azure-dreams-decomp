#include "shared/object_node.h"
#include "dungeon/monster/manoeva.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80E3CC80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x2C];
    s16 unk_40;
} S_80E3CC80_0;   /* object in spawn_manoeva_particle_burst */

   /* arg0 in spawn_manoeva_particle_burst */

extern void register_node(void *object, void *data);
extern void select_sprite_entry(void *object, s32 table_index, s32 entry_index);
extern s32 rand(void);

/* Spawns up to sixteen particles with randomized offsets and velocities. */
void spawn_manoeva_particle_burst(MovingPosition *origin, SpriteFrameState *source_sprite) {
    s32 remaining;
    s32 image;
    u16 sprite_flags;
    u16 source_y;
    S_80E3CC80_0 *particle;
    SpriteFrameState *sprite;
    ObjectPosition *motion;

    remaining = 0x10;
    do {
        particle = allocate_flagged_object_node(0x300);
        if (particle != NULL) {
            particle->unk_10 = update_an_effect_s_lifetime_fades_color_advances_motion;
            register_node(particle, project_sprite_chain);
            sprite = particle->unk_0C;
            sprite->scale_y = 0x800;
            sprite->scale_x = 0x800;
            sprite->color.word = 0x808080;
            sprite->tpage_abr = 0x20;
            image = source_sprite->animation_resource;
            sprite->animation_resource = image;
            sprite_flags = sprite->flags;
            source_y = source_sprite->clut;
            sprite->flags = sprite_flags | 0xC;
            sprite->clut = source_y - 0x80;
            select_sprite_entry(sprite, 0x41, 0);
            motion = particle->unk_08;
            motion->x.w.i = origin->x;
            motion->y.w.i = origin->y;
            motion->z.w.i = origin->z - (rand() & 0x1F);
            *((s16 *)&motion->velocity_z + 1) = ((0 - (rand() & 0xF)) - 8) * 2;
            motion->velocity_x = ((rand() & 3) - 2) << 0x10;
            motion->velocity_y = ((rand() & 3) - 2) << 0x10;
            particle->unk_40 = 0x10;
        }
        remaining -= 1;
    } while (remaining > 0);
}

/* MECHANISM: Named word and halfword read locals extend the arg1 value live ranges, reproducing
   retail's load-before-store emission order in the setup block. */
