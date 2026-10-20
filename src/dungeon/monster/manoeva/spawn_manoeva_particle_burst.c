#include "shared/object_node.h"
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

typedef struct S_80E3CC80_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80E3CC80_2;   /* arg1 in spawn_manoeva_particle_burst */

typedef struct S_80E3CC80_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80E3CC80_3;   /* b in spawn_manoeva_particle_burst */

   /* arg0 in spawn_manoeva_particle_burst */

extern void register_node(void *object, void *data);
extern void select_sprite_entry(void *object, s32 table_index, s32 entry_index);
extern s32 rand(void);
extern u8 D_801763D0[];

/* Spawns up to sixteen particles with randomized offsets and velocities. */
void spawn_manoeva_particle_burst(MovingPosition *origin, S_80E3CC80_2 *source_sprite) {
    s32 remaining;
    s32 image;
    u16 sprite_flags;
    u16 source_y;
    S_80E3CC80_0 *particle;
    SpriteFrameState *sprite;
    S_80E3CC80_3 *motion;

    remaining = 0x10;
    do {
        particle = func_8003FC64(0x300);
        if (particle != NULL) {
            particle->unk_10 = D_801763D0;
            register_node(particle, project_sprite_chain);
            sprite = particle->unk_0C;
            sprite->scale_y = 0x800;
            sprite->scale_x = 0x800;
            sprite->color.word = 0x808080;
            sprite->tpage_abr = 0x20;
            image = ((SpriteFrameState *)source_sprite)->unk_28;
            sprite->unk_28 = image;
            sprite_flags = sprite->flags;
            source_y = ((SpriteFrameState *)source_sprite)->clut;
            sprite->flags = sprite_flags | 0xC;
            sprite->clut = source_y - 0x80;
            select_sprite_entry(sprite, 0x41, 0);
            motion = particle->unk_08;
            motion->unk_02 = origin->unk_02;
            motion->unk_06 = origin->unk_06;
            motion->unk_0A = origin->unk_0A - (rand() & 0x1F);
            motion->unk_16 = ((0 - (rand() & 0xF)) - 8) * 2;
            motion->unk_0C = ((rand() & 3) - 2) << 0x10;
            motion->unk_10 = ((rand() & 3) - 2) << 0x10;
            particle->unk_40 = 0x10;
        }
        remaining -= 1;
    } while (remaining > 0);
}

/* MECHANISM: Named word and halfword read locals extend the arg1 value live ranges, reproducing
   retail's load-before-store emission order in the setup block. */
