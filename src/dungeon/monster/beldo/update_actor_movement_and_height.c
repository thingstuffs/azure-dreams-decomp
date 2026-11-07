#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "engine/object.h"
#include "engine/texture.h"
#include "dungeon/monster/beldo.h"
#include "sdk/libc.h"

typedef s32 M2C_UNK;

typedef void (*Callback)();

typedef union {
    long long value;
    struct { s32 high; u32 low; } word;
} DivProduct;

extern void advance_sprite_animation_and_textures();
extern s32 refresh_actor_facing_and_lifecycle();
extern s32 try_move_actor_to_valid_position();
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

extern Callback beldo_callbacks[];
extern M2C_UNK beldo_effect_pool_script[];



typedef struct S_8017112C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017112C_2_pre;   /* the 0x14 bytes before node in update_actor_movement_and_height, addressed as node[-1] */

typedef struct S_8017112C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8017112C_3;   /* record in update_actor_movement_and_height */

typedef struct S_8017112C_4 {
    s32 unk_00;
    u8 pad_04[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_8017112C_4;   /* motion in update_actor_movement_and_height */

/* Updates actor behavior, movement, facing, and height. */
void update_actor_movement_and_height(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite)
{
    ActorRecord *actor = body;
    u16 state_direction;
    void *call_entity;
    void *call_motion;
    void *call_monster;
    s32 saved_state;
    s32 current_state;
    s32 view_angle;
    Callback callback;
    Callback active_callback;
    s16 floor_height;
    s32 target_height;
    s32 height;
    s32 height_gap;
    u16 global_flags;
    u16 *flag_word;
    s32 height_delta;
    s32 height_fixed;
    s32 divisor_magic;
    s32 height_step;
    DivProduct product;
    u8 *slot;
    S_8017112C_2_pre *node;
    S_8017112C_3 *record;

    if (actor->unk_BB == 0 && g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
        actor->unk_BB = 1;
        enqueue_runtime_pool_script(beldo_effect_pool_script);
        actor->pending_turn_updates = 0;
        actor->action_phase = 0;
    }

    flag_word = &(*(u16 *)0x80013714);
    global_flags = *flag_word;
    if (global_flags & 8) {
        s32 slot_index = 1;
        slot = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            node = ((ActorRecord *)slot)->unk_AC.address;
            if (node != 0) {
                record = node[-1].unk_00;
                record->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot -= 4;
        } while (slot_index >= 0);
    }

    if (g_dungeon_status.flags & 0x2000) {
        callback = body->unk_8C.handler;
        if (callback == (Callback)&update_object_animation) {
            callback(body, position, sprite, actor);
            return;
        }
        actor->movement_queue_state &= 0x7F;
        return;
    }

    call_entity = body;
    call_motion = position;
    call_monster = sprite;
    state_direction = actor->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_monster, actor) != 0) {
        return;
    }

    active_callback = body->unk_8C.handler;
    if (active_callback != 0) {
        active_callback(body, position, sprite, actor);
    }
    beldo_callbacks[body->action_id](body, position, sprite, actor);

    saved_state = (s32)state_direction << 16;
    current_state = actor->pending_turn_updates;
    saved_state >>= 16;
    if (saved_state != current_state) {
        try_move_actor_to_valid_position(body, position, sprite, actor);
    }

    position->x.v += position->velocity_x;
    position->y.v += position->velocity_y;

    view_angle = g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100;
    state_direction = (view_angle >> 9) & 7;
    if (body->unk_94 != state_direction) {
        select_indirect_table_entry(sprite,
                      *((u8 *)sprite->frameTable + state_direction),
                      sprite->unk_04);
        body->unk_94 = state_direction;
    }

    sprite->flags &= 0xFFFE;
    apply_monster_koyaw_data(actor->flags1C, (u8 *)sprite + 0xC);

    if (!(actor->flags1C & 0x20)) {
        if (!(sprite->flags & 0x40)) {
            advance_sprite_animation_and_textures(sprite);
        }
    } else {
        sprite->flags |= 0x7000;
        actor->flags1C &= 0xFFFBFFFF;
    }

    if ((*(s16 *)((u8 *)body + (0xB8))) == 1) {
        target_height = ((S_8017112C_4 *)position)->unk_14.at02.v;
        height = position->z.w.i;
        height_fixed = position->z.unsigned_parts.integer;
        if (target_height > height) {
            height_gap = target_height - height;
            height_gap = abs(height_gap);
            divisor_magic = 0x66660000;
            if (height_gap >= 0x65) {
                height_gap = height_fixed + 8;
                position->z.w.i = height_gap;
            } else {
                height_delta = position->velocity_z;
                height_fixed = position->z.v;
                divisor_magic |= 0x6667;
                height_delta -= height_fixed;
                height_delta = abs(height_delta);
                product.value = (long long)height_delta * divisor_magic;
                height_step = (product.word.high >> 2) - (height_delta >> 31);
                height_fixed += height_step;
                position->z.v = height_fixed;
            }
        }
    }

    if ((*(s16 *)((u8 *)body + (0xB8))) == 2 && position->z.w.i >= -0x3EF) {
        position->z.w.i = position->z.unsigned_parts.integer - 4;
    }

    if (actor->flags1C & 0x40000000) {
        actor->flags1C &= 0xBFFFFFFF;
        floor_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                              (sprite->tile_y << 6) | 0x20,
                              (s16)(((u16)actor->ground_height) - 0x20));
        if (floor_height < 0x200) {
            body->unk_90.parts.high.u += ((u16)actor->ground_height) - floor_height;
            actor->ground_height = floor_height;
        }
    }

    sprite->flags |= 0x40;
}
