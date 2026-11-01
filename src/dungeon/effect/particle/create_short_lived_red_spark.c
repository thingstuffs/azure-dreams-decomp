#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"
#include "slus.h"

typedef struct S_80166204_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80166204_4;   /* arg0 in create_short_lived_red_spark */

typedef struct S_80166204_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80166204_5;

   /* ((S_80166204_4 *)arg0)->unk_08 in create_short_lived_red_spark */


extern void D_80165A0C();

/* Creates an offset effect with randomized motion and initializes its display properties. */
void create_short_lived_red_spark(S_80166204_4 *source, s16 effect_value, s32 unused, s16 offset_x, s16 offset_y, s16 offset_z,
    s32 velocity_z) {
    s32 color_component;
    s32 sprite_flags;
    SpriteFrameState *sprite;
    ShortLivedRedSparkBody *effect_state;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect->update_callback = &D_80165A0C;
        effect->position->x.w.i =
            (s16) (((MovingPosition *)(source->unk_08))->x + offset_x);
        effect->position->y.w.i =
            (s16) (((MovingPosition *)(source->unk_08))->y + offset_y);
        effect->position->z.w.i =
            (s16) (((MovingPosition *)(source->unk_08))->z + offset_z);
        effect_state = NODE_BODY(effect);
        effect_state->unk_42 = (u16) ((MovingPosition *)(source->unk_08))->x;
        effect_state->unk_44 = (u16) ((MovingPosition *)(source->unk_08))->y;
        effect_state->unk_46 = (u16) ((MovingPosition *)(source->unk_08))->z;
        effect->position->velocity_x = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        effect->position->velocity_y = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        effect->position->velocity_z = velocity_z;
        effect_state->unk_14 = effect_value;
        effect_state->unk_32 = 8;
        effect_state->unk_34 = 8;
        register_node(effect, project_sprite_chain);
        sprite = effect->sprite;
        sprite->scale_y = 0x2AA;
        color_component = 0x20;
        sprite->color.c.b = color_component;
        sprite->scale_x = 0x2AA;
        sprite->color.c.r = 0xFF;
        sprite->color.c.g = color_component;
        sprite_flags = sprite->flags & 0xFFF3;
        sprite_flags |= 2;
        sprite->flags = sprite_flags;
        sprite->clut = 0x7DCF;
        sprite_flags |= 0x100;
        sprite->flags = sprite_flags;
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
    }
}

/* MECHANISM: Seven ABI arguments preserve the unused a2 slot; offset_x/y/z are s16
   parameters, so assign_parms converts them instead of marking the stack slots REG_EQUIV,
   and they stay in s0/s3/s4 across the first call. */
