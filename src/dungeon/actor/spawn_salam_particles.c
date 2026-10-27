#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "engine/node/allocation.h"
#include "engine/node.h"

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in spawn_salam_particles */

extern void D_800CAED0(void *object, void *motion);
extern M2C_UNK D_800E03B0;


typedef struct S_800CAFDC_3 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x18];
    s16 unk_B0;
} S_800CAFDC_3;

/* Spawns two salam particles near the source with randomized positions and velocities. */
void spawn_salam_particles(ObjectNodeHeader *source, s16 effect_param, s32 render_param) {
    s16 angle;
    s32 remaining;
    S_800CAFDC_3 *effect_state;
    ObjectPosition *motion;
    ObjectNodeHeader *particle;
    SpriteFrameState *render;

    remaining = 2;
    do {
        particle = allocate_list_node(0x212, &source->next);
        if (particle != NULL) {
            particle->update_callback = &D_800CAED0;
            register_node(particle, project_sprite_chain);
            motion = particle->position;
            motion->x.w.i = (s16) ((source->position->x.w.i + (rand() & 0x3F)) - 0x20);
            motion->y.w.i = (s16) ((source->position->y.w.i + (rand() & 0x3F)) - 0x20);
            motion->z.w.i = (s16) ((source->position->z.w.i + (rand() & 0x3F)) - 0x20);
            angle = rand();
            motion->velocity_x = rcos(angle) << 5;
            motion->velocity_y = rsin(angle) << 5;
            *((s16 *)&motion->velocity_z + 1) = (s16) ((0 - (rand() & 7)) - 8);
            render = particle->sprite;
            effect_state = ((void *)particle) + 0x20;
            render->scale_y = 0x1000;
            render->scale_x = 0x1000;
            /*
             * BUG: D_800E03B0 supplies a 1x1 command at unit scale. The perspective renderer treats those
             * extents as world units, making these particles too small at the combat camera distance.
             * Found and documented by the Azure Dreams community
             * (adrando.com/guide/bugs.html).
             */
            render->source = &D_800E03B0;
            render->color.word = render_param;
            render->depth_bias = 8;
            effect_state->unk_B0 = effect_param;
            effect_state->unk_96 = (s16) ((rand() & 0xFF) | 0x80);
        }
        remaining -= 1;
    } while (remaining > 0);
}
