#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_particle_template.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x20];
    s32 field_20;
} EffectFieldView_8132ED0C;


typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
s32 func_80167088(s32 limit);                         /* extern */
extern void D_80165AB8(u8 *, u8 *, u8 *);


typedef struct S_80165D0C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165D0C_0;   /* arg0 in create_ballistic_landing_particle */

typedef struct S_80165D0C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
} S_80165D0C_1;

typedef struct S_80165D0C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80165D0C_2;

typedef struct S_80165D0C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165D0C_3;

   /* ((S_80165D0C_0 *)arg0)->unk_08 in create_ballistic_landing_particle */

/* Spawn an effect relative to the source with randomized motion and sprite size. */
void create_ballistic_landing_particle(S_80165D0C_0 *source, s16 duration, s32 scale, s16 offset_x, s16 offset_y, s16 offset_z,
    s32 velocity_z) {
    s32 sprite_scale;
    SpriteFrameState *sprite;
    S_80165D0C_1 *effect_state;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x12);
    if (effect != NULL) {
        (effect->update_callback) = &D_80165AB8;
        ((S_80165D0C_3 *)((effect->position)))->unk_02 =
            (s16) (((MovingPosition *)(source->unk_08))->x + offset_x);
        ((S_80165D0C_3 *)((effect->position)))->unk_06 =
            (s16) (((MovingPosition *)(source->unk_08))->y + offset_y);
        ((S_80165D0C_3 *)((effect->position)))->unk_0A =
            (s16) (((MovingPosition *)(source->unk_08))->z + offset_z);
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_42 = (u16) ((MovingPosition *)(source->unk_08))->x;
        effect_state->unk_44 = (u16) ((MovingPosition *)(source->unk_08))->y;
        effect_state->unk_46 = (u16) ((MovingPosition *)(source->unk_08))->z;
        ((S_80165D0C_3 *)((effect->position)))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((effect->position)))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((effect->position)))->unk_14 = (s32) (velocity_z + 0xFFFC0000);
        effect_state->unk_60 = 0x10000;
        effect_state->unk_14 = duration;
        effect_state->unk_32 = 0;
        effect_state->unk_34 = 0;
        register_node(effect, project_sprite_chain);
        sprite = effect->sprite;
        sprite->depth_bias = -4;
        sprite->flags = (u16) (sprite->flags & 0xFFF3);
        sprite_scale = 0x1000 / (s32) (func_80167088(5) + 8);
        sprite->color.word = scale;
        sprite->scale_y = (s16) sprite_scale;
        sprite->scale_x = (s16) sprite_scale;
        (((EffectFieldView_8132ED0C *)effect)->field_20) = scale;
        effect_state->unk_04 = scale;
        effect_state->unk_08 = scale;
        (*(Copy12 *)((u8 *)effect + 0x56)) =
            (*(Copy12 *)((u8 *)&particle_sprite_template + 0));
        sprite->source = (void *) (((void *)effect) + 0x56);
    }
}

/* MECHANISM: A packed Copy12 assignment emits the retail lwl/lwr and swl/swr copy sequence. */
