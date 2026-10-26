#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

typedef s32 M2C_UNK;

typedef struct S_80D65810_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x1C];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} S_80D65810_0;

   /* input in create_origin_motion_effect */

void select_record_entry_and_value(void *state, void *entries, short index);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern void update_effect_collision_and_lifetime(void);

/* Creates an effect relative to the origin and initializes its motion and appearance. */
void create_origin_motion_effect(s32 unused_0, void *origin_ptr_in, s32 unused_2, u16 offset_x, s16 offset_y, s16 offset_z) {
    void *origin_ptr;
    u16 render_flags;
    MovingPosition *origin;
    u16 x;
    s16 y;
    s16 z;
    s32 size;
    SpriteFrameState *render;
    SpriteFrameState *sprite;
    S_80D65810_0 *motion;
    ObjectPosition *position;
    ObjectNodeHeader *effect;
    origin_ptr = origin_ptr_in;

    origin = origin_ptr;
    x = offset_x;
    y = offset_y;
    z = offset_z;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = ((void *)effect) + 0x20;
        motion->unk_0C = 0x1E;
        motion->unk_0E = 0x1E;
        effect->update_callback = update_effect_collision_and_lifetime;
        register_node(effect, project_sprite_chain);
        render = effect->sprite;
        render->flags |= 0xC;
        size = 0x60;
        render->tpage_abr = size;
        render->depth_bias = 0;
        render_flags = render->flags;
        render->flags = (u16)(render_flags | 2);
        position = effect->position;
        position->x.w.i = x;
        position->y.w.i = (u16)y;
        position->z.w.i = (u16)z;
        motion->unk_34 = 0x40000;
        motion->unk_40 = 0x8000;
        motion->unk_2C = (s32)((s32)position->x.v >> 1);
        motion->unk_30 = (s32)((s32)position->y.v >> 1);
        if (motion->unk_2C == 0) {
            motion->unk_2C = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
            motion->unk_30 = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
        }
        motion->unk_38 = (s32)(0 - ((s32)motion->unk_2C >> 4));
        motion->unk_3C = (s32)(0 - ((s32)motion->unk_30 >> 4));
        position->x.w.i = (u16)(*(u16 *)&position->x.w.i + origin->x);
        position->y.w.i = (u16)(*(u16 *)&position->y.w.i + origin->y);
        position->z.w.i = (u16)(*(u16 *)&position->z.w.i + origin->z);
        sprite = effect->sprite;
        sprite->scale_x = 0xC00;
        sprite->scale_y = 0xC00;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->clut = 0x7DCF;
        sprite->flags = (u16)(sprite->flags | 0x100);
        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
    }
}

