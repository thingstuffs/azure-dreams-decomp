#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor.h"

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in spawn_salam_particles */

void *allocate_list_node();               /* extern */
s32 register_node();           /* extern */
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_800CAED0;
extern M2C_UNK D_800E03B0;


typedef struct S_800CAFDC_3 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x18];
    s16 unk_B0;
} S_800CAFDC_3;

/* Spawns two salam particles near the source with randomized positions and velocities. */
void spawn_salam_particles(EntityRec *source, s16 effect_param, s32 render_param) {
    s16 angle;
    s32 remaining;
    S_800CAFDC_3 *effect_state;
    ObjectPosition *motion;
    ObjectNodeHeader *particle;
    SpriteFrameState *render;

    remaining = 2;
    do {
        particle = allocate_list_node(0x212, source);
        if (particle != NULL) {
            particle->unk_10 = &D_800CAED0;
            register_node(particle, project_sprite_chain);
            motion = particle->position;
            motion->x.w.i = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_02 + (rand() & 0x3F)) - 0x20);
            motion->y.w.i = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_06 + (rand() & 0x3F)) - 0x20);
            motion->z.w.i = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_0A + (rand() & 0x3F)) - 0x20);
            angle = rand();
            motion->velocity_x = (s32) (rcos(angle) << 5);
            motion->velocity_y = (s32) (rsin(angle) << 5);
            *((s16 *)&motion->velocity_z + 1) = (s16) ((0 - (rand() & 7)) - 8);
            render = particle->sprite;
            effect_state = ((void *)particle) + 0x20;
            render->scale_y = 0x1000;
            render->scale_x = 0x1000;
            /*
             * Original bug: D_800E03B0 supplies a 1x1 command at unit scale. The perspective renderer treats those
             * extents as world units, making these particles too small at the combat camera distance.
             * Found and documented by the Azure Dreams community
             * (adrando.com/guide/bugs.html).
             */
            render->source = &D_800E03B0;
            render->color.word = render_param;
            render->unk_06 = 8;
            effect_state->unk_B0 = effect_param;
            effect_state->unk_96 = (s16) ((rand() & 0xFF) | 0x80);
        }
        remaining -= 1;
    } while (remaining > 0);
}
