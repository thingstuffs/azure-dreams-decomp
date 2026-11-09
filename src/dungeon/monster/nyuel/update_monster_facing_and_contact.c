#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "engine/texture.h"
#include "dungeon/item.h"
#include "dungeon/monster/nyuel.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

extern u8 nyuel_action_resume_address;
extern Callback nyuel_callbacks[];

   /* monster in update_monster_facing_and_contact */



/* Updates monster facing, runs actor callbacks, and applies motion and floor contact. */
void update_monster_facing_and_contact(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *actor = body;
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

        if (!(actor->flags1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
            apply_monster_koyaw_data(actor->flags1C, (u8 *)sprite + 0xC);
        } else {
            sprite->flags |= 0x7000;
            apply_monster_koyaw_data(actor->flags1C, (u8 *)sprite + 0xC);
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

    nyuel_callbacks[body->action_id](body, motion, sprite, actor);

    if (old_direction != actor->pending_turn_updates) {
        try_move_actor_to_valid_position(body, motion, sprite, actor);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (body->action_state_flags & 8) {
        body->unk_9D = 0;
    } else {
        motion->velocity_z += (body->unk_9D) * 0x14000;
        body->unk_9D++;
    }

    body->unk_90.value += motion->velocity_z;

    if (!(body->action_state_flags & 4)) {
        floor_height = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                              motion->y.unsigned_parts.integer,
                              (s16)(((u16)actor->ground_height) - 0x20));
        if (floor_height < 0x200) {
            actor_height = actor->ground_height;
            if (body->unk_90.parts.high.s + actor_height < floor_height) {
                body->action_state_flags &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    body->unk_90.value = 0;
                } else {
                    body->unk_90.parts.high.s = floor_height - ((u16)actor->ground_height);
                }

                motion->velocity_z = 0;
                actor->flags1C |= 0x08000000;
                body->unk_9D = 0;
            }
            if (actor->flags1C & 0x40000000) {
                actor->flags1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                                      (sprite->tile_y << 6) | 0x20,
                                      (s16)(((u16)actor->ground_height) - 0x20));
                body->unk_90.parts.high.s += ((u16)actor->ground_height) - floor_height;
                actor->ground_height = floor_height;
            }
        } else {
            actor->flags1C &= 0xF7FFFFFF;
        }
    } else {
        actor->flags1C &= 0xF7FFFFFF;
    }

    motion->z.unsigned_parts.integer =
        ((u16)actor->ground_height) + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

}
