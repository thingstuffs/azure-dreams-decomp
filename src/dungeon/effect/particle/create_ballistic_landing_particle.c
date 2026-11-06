#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_particle_template.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x20];
    s32 field_20;
} EffectFieldView_8132ED0C;

typedef struct Copy12 {
    s32 word[3];
} __attribute__((packed)) Copy12;

s32 func_80167088(s32 limit);                         /* extern */
extern void D_80165AB8(u8 *, u8 *, u8 *);


   /* ((S_80165D0C_0 *)arg0)->unk_08 in create_ballistic_landing_particle */

/* Spawn an effect relative to the source with randomized motion and sprite size. */
void create_ballistic_landing_particle(ObjectNodeHeader *source, s16 duration, s32 scale, s16 offset_x, s16 offset_y, s16 offset_z,
    s32 velocity_z) {
    s32 sprite_scale;
    SpriteFrameState *sprite;
    ScatterLandingSparksOnGridBody *effect_state;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x12);
    if (effect != NULL) {
        (effect->update_callback) = &D_80165AB8;
        effect->position->x.w.i =
            (s16) (source->position->x.unsigned_parts.integer + offset_x);
        effect->position->y.w.i =
            (s16) (source->position->y.unsigned_parts.integer + offset_y);
        effect->position->z.w.i =
            (s16) (source->position->z.unsigned_parts.integer + offset_z);
        effect_state = NODE_BODY(effect);
        effect_state->unk_42 = (u16) source->position->x.unsigned_parts.integer;
        effect_state->unk_44 = (u16) source->position->y.unsigned_parts.integer;
        effect_state->unk_46 = (u16) source->position->z.unsigned_parts.integer;
        effect->position->velocity_x = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        effect->position->velocity_y = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        effect->position->velocity_z = (s32) (velocity_z + 0xFFFC0000);
        effect_state->gravity = 0x10000;
        effect_state->unk_14 = duration;
        effect_state->ticks = 0;
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
        sprite->source = (((void *)effect) + 0x56);
    }
}

/* MECHANISM: A packed Copy12 assignment emits the retail lwl/lwr and swl/swr copy sequence. */
