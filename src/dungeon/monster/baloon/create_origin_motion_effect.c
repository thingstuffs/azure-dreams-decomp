#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/dungeon_moving_views.h"

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

typedef struct S_80D65810_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65810_1;

typedef struct S_80D65810_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65810_3;

   /* input in create_origin_motion_effect */

M2C_UNK select_record_entry_and_value();
s32 register_node();
s32 rand();
extern void project_sprite_chain(void);
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
    S_80D65810_3 *position;
    void *effect;
    origin_ptr = origin_ptr_in;

    origin = origin_ptr;
    x = offset_x;
    y = offset_y;
    z = offset_z;
    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        motion = effect + 0x20;
        motion->unk_0C = 0x1E;
        motion->unk_0E = 0x1E;
        ((S_80D65810_1 *)effect)->unk_10 = update_effect_collision_and_lifetime;
        register_node(effect, project_sprite_chain);
        render = ((S_80D65810_1 *)effect)->unk_0C;
        render->flags |= 0xC;
        size = 0x60;
        render->tpage_abr = size;
        render->unk_06 = 0;
        render_flags = render->flags;
        render->flags = (u16)(render_flags | 2);
        position = ((S_80D65810_1 *)effect)->unk_08;
        position->unk_00.at02.v = x;
        position->unk_04.at02.v = (u16)y;
        position->unk_0A = (u16)z;
        motion->unk_34 = 0x40000;
        motion->unk_40 = 0x8000;
        motion->unk_2C = (s32)((s32)position->unk_00.at00.v >> 1);
        motion->unk_30 = (s32)((s32)position->unk_04.at00.v >> 1);
        if (motion->unk_2C == 0) {
            motion->unk_2C = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
            motion->unk_30 = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
        }
        motion->unk_38 = (s32)(0 - ((s32)motion->unk_2C >> 4));
        motion->unk_3C = (s32)(0 - ((s32)motion->unk_30 >> 4));
        position->unk_00.at02.v = (u16)(position->unk_00.at02.v + origin->unk_02);
        position->unk_04.at02.v = (u16)(position->unk_04.at02.v + origin->unk_06);
        position->unk_0A = (u16)(position->unk_0A + origin->unk_0A);
        sprite = ((S_80D65810_1 *)effect)->unk_0C;
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

