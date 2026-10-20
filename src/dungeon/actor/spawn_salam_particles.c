#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in spawn_salam_particles */

void *allocate_list_node();               /* extern */
s32 register_node();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_800CAED0;
extern M2C_UNK D_800E03B0;

typedef struct S_800CAFDC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CAFDC_0;

typedef struct S_800CAFDC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800CAFDC_1;

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
    S_800CAFDC_1 *motion;
    void *particle;
    SpriteFrameState *render;

    remaining = 2;
    do {
        particle = allocate_list_node(0x212, source);
        if (particle != NULL) {
            ((S_800CAFDC_0 *)particle)->unk_10 = &D_800CAED0;
            register_node(particle, project_sprite_chain);
            motion = ((S_800CAFDC_0 *)particle)->unk_08;
            motion->unk_02 = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_02 + (rand() & 0x3F)) - 0x20);
            motion->unk_06 = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_06 + (rand() & 0x3F)) - 0x20);
            motion->unk_0A = (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_0A + (rand() & 0x3F)) - 0x20);
            angle = rand();
            motion->unk_0C = (s32) (func_80064584(angle) << 5);
            motion->unk_10 = (s32) (func_800644B8(angle) << 5);
            motion->unk_16 = (s16) ((0 - (rand() & 7)) - 8);
            render = ((S_800CAFDC_0 *)particle)->unk_0C;
            effect_state = particle + 0x20;
            render->scale_y = 0x1000;
            render->scale_x = 0x1000;
            render->source = &D_800E03B0;
            render->color.word = render_param;
            render->unk_06 = 8;
            effect_state->unk_B0 = effect_param;
            effect_state->unk_96 = (s16) ((rand() & 0xFF) | 0x80);
        }
        remaining -= 1;
    } while (remaining > 0);
}
