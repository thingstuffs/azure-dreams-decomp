#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_particle_template.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef void (*LandingParticleCallback)(u8 *, u8 *, u8 *);

void register_node(void *, void *);
s32 rand(void);
s32 func_80167088(s32);

extern void D_80165AB8(u8 *, u8 *, u8 *);

typedef struct S_8016604C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016604C_0;   /* arg0 in scatter_landing_sparks_on_grid */

typedef struct S_8016604C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8016604C_1;

typedef struct S_8016604C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016604C_2;

   /* ((S_8016604C_0 *)arg0)->unk_08 in scatter_landing_sparks_on_grid */

typedef struct S_8016604C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8016604C_4;

/* Spawn particles at random positions in a grid around the source. */
void scatter_landing_sparks_on_grid(S_8016604C_0 *source) {
    s32 x_base;
    s32 y_base;
    s32 y_random;
    s32 jitter_or_scale;
    s32 grid_y;
    s32 grid_x;
    SpriteFrameState *sprite;
    LandingParticleCallback effect_data;
    ObjectNodeHeader *particle;
    ObjectPosition *motion;

    grid_x = -2;
    effect_data = &D_80165AB8;
    do {
        grid_y = -5;
        do {
            if (!(rand() & 7)) {
                particle = allocate_flagged_object_node(0x12);
                if (particle != NULL) {
                    (particle->update_callback) = effect_data;
                    jitter_or_scale = rand();
                    x_base = ((MovingPosition *)(source->unk_08))->x + (grid_x << 6);
                    x_base -= 0x20;
                    ((S_8016604C_4 *)((particle->position)))->unk_02 = (s16) (x_base + (jitter_or_scale & 0x3F));
                    y_random = rand();
                    y_base = ((MovingPosition *)(source->unk_08))->y + (grid_y << 6);
                    y_base -= 0x20;
                    ((S_8016604C_4 *)((particle->position)))->unk_06 = (s16) (y_base + (y_random & 0x3F));
                    ((S_8016604C_4 *)((particle->position)))->unk_0A = (s16) (((MovingPosition *)(source->unk_08))->z - 0x100);
                    motion = particle->position;
                    motion->velocity_y = 0;
                    motion->velocity_x = 0;
                    ((S_8016604C_4 *)((particle->position)))->unk_14 = 0x200000;
                    register_node(particle, draw_linked_sprites_clipped);
                    sprite = particle->sprite;
                    sprite->flags = (u16) (sprite->flags & 0xFFF3);
                    jitter_or_scale = 0x1000 / (s32) (func_80167088(5) + 6);
                    sprite->color.c.r = 0xFF;
                    sprite->color.c.b = 0x20;
                    sprite->color.c.g = 0x20;
                    sprite->scale_y = (s16) jitter_or_scale;
                    sprite->scale_x = (s16) jitter_or_scale;
                    (*(Packed12 *)((u8 *)particle + 0x56)) = particle_sprite_template;
                    sprite->source = (void *) (((void *)particle) + 0x56);
                }
            }
            grid_y += 1;
        } while (grid_y <= 0);
        grid_x += 1;
    } while (grid_x < 3);
}

/* MECHANISM: True-space nested loops plus a held D_80165AB8 base produce the exact 0x30 frame and s5/s4/s3/s2 roles at cdk-G0.
   A byte-aligned 12-byte aggregate produces the retail lwl/lwr/swl/swr copy; distinct RNG/coordinate locals preserve v1/a0 allocation.
   The final 0xFF field is u8 so GCC materializes 0xff rather than canonicalizing it to -1. */
