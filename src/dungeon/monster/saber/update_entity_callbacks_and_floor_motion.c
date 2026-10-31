#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "engine/texture.h"
#include "dungeon/item.h"

typedef ActorActionHandler Callback;

extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

#include "dungeon/monster/saber.h"
#include "slus.h"
extern Callback saber_callbacks[];

   /* monster in update_entity_callbacks_and_floor_motion */

typedef struct S_80171320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80171320_1;   /* actor in update_entity_callbacks_and_floor_motion */

typedef struct S_80171320_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171320_2;   /* motion in update_entity_callbacks_and_floor_motion */

/* Runs entity callbacks, updates monster facing, and applies motion and floor collision. */
void update_entity_callbacks_and_floor_motion(ActorRecord *body, S_80171320_2 *motion, SpriteFrameState *sprite)
{
    S_80171320_1 *actor = (S_80171320_1 *)body;
    s32 direction;
    s16 direction_copy;
    s32 direction_value;
    s16 old_direction;
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        Callback early_callback;

        early_callback = body->unk_8C.handler;
        if (early_callback == (Callback)&saber_behavior_entry) {
            early_callback(body, motion, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    old_direction = (s8)(*(u8 *)((u8 *)body + 0x6D));
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, motion, sprite, body);
    }

    saber_callbacks[body->action_id.u](body, motion, sprite, body);

    if ((s16)old_direction != body->pending_turn_updates) {
        try_move_actor_to_valid_position(body, motion, sprite, body);
    }

    monster_flags = sprite->flags;
    if (!(monster_flags & 0x8000)) {
        direction_value = g_game_work.view.camera_rotation.parts.viewAngle + body->facing + 0x100;
        direction = (direction_value >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if (body->unk_94 != direction_index) {
            u8 *tile_map = *(unsigned char **)&sprite->frameTable;
            if (tile_map != 0) {
                select_indirect_table_entry(sprite, tile_map[direction_index], sprite->unk_04);
            }
            body->unk_94 = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }

        if (!(actor->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
        }

        apply_monster_koyaw_data(actor->unk_1C, (u8 *)sprite + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            sprite->flags = monster_flags & 0x8FFF;
        } else {
            sprite->flags = monster_flags | 0x7000;
        }
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->unk_14 += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    }

    body->unk_90.value += motion->unk_14;

    if (!(body->action_state_flags & 4)) {
        floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(actor->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = actor->unk_88.s;
            if (body->unk_90.parts.high.s + actor_height < floor_height) {
                actor->unk_1C &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    body->unk_90.value = 0;
                } else {
                    body->unk_90.parts.high.s = floor_height - actor->unk_88.u;
                }

                motion->unk_14 = 0;
                actor->unk_1C |= 0x08000000;
                body->unk_9D.u = 0;
            }
            if (actor->unk_1C & 0x40000000) {
                actor->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                                      (sprite->tile_y << 6) | 0x20,
                                      (s16)(actor->unk_88.u - 0x20));
                body->unk_90.parts.high.s += actor->unk_88.u - floor_height;
                actor->unk_88.u = floor_height;
            }
        } else {
            actor->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        actor->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        actor->unk_88.u + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

}

