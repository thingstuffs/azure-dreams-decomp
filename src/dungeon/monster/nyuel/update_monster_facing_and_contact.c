#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "engine/texture.h"
#include "dungeon/item.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

extern u8 nyuel_action_resume_address;
extern u8 pulunpa_variant_action_address;
extern Callback nyuel_callbacks[];
extern Callback D_80176380[];
extern Callback D_801763E0[];

   /* monster in update_monster_facing_and_contact */

typedef struct S_80170A98_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170A98_1;   /* actor in update_monster_facing_and_contact */

typedef struct S_80170A98_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A98_2;   /* motion in update_monster_facing_and_contact */

/* Updates monster facing, runs actor callbacks, and applies motion and floor contact. */
void update_monster_facing_and_contact(ActorRecord *body, S_80170A98_2 *motion, SpriteFrameState *sprite)
{
    S_80170A98_1 *actor = (S_80170A98_1 *)body;
    s32 direction;
    s16 direction_copy;
    s16 old_direction;
    s32 facing_angle;
    ActorActionHandler callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        ActorActionHandler early_callback;

        early_callback = body->unk_8C.handler;
        if (early_callback == (ActorActionHandler)&nyuel_action_resume_address) {
            early_callback(body, motion, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    old_direction = body->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    monster_flags = sprite->flags;
    if (!(monster_flags & 0x8000)) {
        facing_angle = g_game_work.view.camera_rotation.parts.viewAngle + body->facing + 0x100;
        direction = (facing_angle >> 9) & 7;
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
            apply_monster_koyaw_data(actor->unk_1C, (u8 *)sprite + 0xC);
        } else {
            sprite->flags |= 0x7000;
            apply_monster_koyaw_data(actor->unk_1C, (u8 *)sprite + 0xC);
        }
    } else {
        if (monster_flags & 0x0800) {
            sprite->flags = monster_flags & 0x8FFF;
        } else {
            sprite->flags = monster_flags | 0x7000;
        }
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, motion, sprite, actor);
    }

    nyuel_callbacks[body->action_id.u](body, motion, sprite, actor);

    if (old_direction != actor->unk_6D) {
        try_move_actor_to_valid_position(body, motion, sprite, actor);
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
                body->action_state_flags &= 0xF7FFFFFF;
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
