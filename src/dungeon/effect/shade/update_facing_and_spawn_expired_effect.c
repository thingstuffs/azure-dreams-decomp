#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/texture.h"
#include "slus.h"
#include "engine/node.h"

typedef struct S_800D58D8_0_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800D58D8_0_pre;   /* the 0x14 bytes before arg0 in update_facing_and_spawn_expired_effect, addressed as arg0[-1] */

typedef struct S_800D58D8_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x68];
    s16 unk_94;
    u16 unk_96;
} S_800D58D8_0;   /* arg0 in update_facing_and_spawn_expired_effect */

   /* arg1 in update_facing_and_spawn_expired_effect */

typedef struct S_800D58D8_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800D58D8_6;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
s32 resolve_record_orientation_or_fallback(void *, void *, Vec3u16 *, s32);     /* extern */
extern s32 D_800D586C[];

/* Update sprite facing and animation, then spawn an effect when the countdown expires. */
void update_facing_and_spawn_expired_effect(void *state, MovingPosition *position, SpriteFrameState *sprite) {
    Vec3u16 delta;
    s16 facing;
    void *direction_frames;
    u16 ticks_left;
    SpriteFrameState *effect_render;
    void *owner;
    ObjectPosition *effect_pos;
    ObjectNodeHeader *effect;

    facing = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_800D58D8_0 *)state)->unk_2A + 0x100) >> 9) & 7;
    if (((S_800D58D8_0 *)state)->unk_94 != facing) {
        direction_frames = sprite->frameTable;
        if (direction_frames != 0) {
            select_indirect_table_entry(sprite, *((u8 *)direction_frames + facing), sprite->unk_04);
        }
        ((S_800D58D8_0 *)state)->unk_94 = facing;
    }
    advance_sprite_animation_and_textures(sprite);
    ticks_left = ((S_800D58D8_0 *)state)->unk_96 - 1;
    ((S_800D58D8_0 *)state)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        effect = allocate_flagged_object_node(0x12);
        if (effect != NULL) {
            register_node(effect, project_sprite_chain);
            effect_render = effect->sprite;
            effect_render->tpage_abr = 0x20;
            effect_render->flags = (u16) (effect_render->flags | 0xC);
            effect_pos = effect->position;
            effect_pos->x.w.i = (u16) position->x;
            effect_pos->y.w.i = (u16) position->y;
            effect_pos->z.w.i = (u16) position->z;
            effect_render = effect->sprite;
            effect_render->scale_y = 0x1800;
            effect_render->scale_x = 0x1800;
            effect_render->color.c.b = 0x80;
            effect_render->color.c.g = 0x80;
            effect_render->color.c.r = 0x80;
            effect_render->depth_bias = (u16) *(u16 *)&sprite->depth_bias;
            effect->update_callback = &D_800D586C;
            owner = ((S_800D58D8_0_pre *)state)[-1].unk_00;
            if (resolve_record_orientation_or_fallback(((S_800D58D8_6 *)owner)->unk_08, owner, &delta, 0) != 0) {
                effect_pos->x.w.i = (u16) ((u16)effect_pos->x.w.i + delta.x);
                effect_pos->y.w.i = (u16) ((u16)effect_pos->y.w.i + delta.y);
                effect_pos->z.w.i = (u16) ((u16)effect_pos->z.w.i + delta.z);
            }
            select_record_entry_and_value(effect->sprite, effect_sprite_sources, 0);
        }
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800D58D8_0_pre *)state)[-1].unk_12 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* MECHANISM: A six-byte Vec3u16 output object forces the retail 0x30 frame and s0-s4 save set.
   Reusing effect_render across disjoint render-pointer live ranges colors both reloads as $a0.
   A scalar global RMW removes the displacement cascade; u8 stores materialize positive 0x80. */
