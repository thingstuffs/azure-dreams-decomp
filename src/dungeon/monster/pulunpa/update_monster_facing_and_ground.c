#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "engine/texture.h"
#include "dungeon/item.h"
#include "dungeon/monster/pulunpa.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_variant_action_address;
extern Callback D_80176380[];
extern Callback D_801763E0[];

   /* monster in update_monster_facing_and_ground */



/* Updates monster facing, runs actor callbacks, and applies movement and floor height corrections. */
void update_monster_facing_and_ground(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *actor = body;
    s32 direction;
    s16 direction_copy;
    s16 old_direction;
    u8 * direction_flag;
    s32 facing_angle;
    ActorActionHandler callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        ActorActionHandler special_callback;

        special_callback = body->unk_8C.handler;
        if (special_callback == (ActorActionHandler)&pulunpa_action_resume_address ||
            special_callback == (ActorActionHandler)&pulunpa_variant_action_address) {
            special_callback(body, motion, sprite, body);
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    old_direction = (s8)(*((u8 *)body + 0x6D));
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

        direction_flag = dir_sprite_flag + direction_copy;
        if (*direction_flag != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }

        if (!(actor->flags1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
        }

        apply_monster_koyaw_data(actor->flags1C, (u8 *)sprite + 0xC);
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

    if (body->unk_A4.bytes[3]) {
        D_801763E0[body->action_id.u](body, motion, sprite, actor);
    } else {
        D_80176380[body->action_id.u](body, motion, sprite, actor);
    }

    if (old_direction != actor->pending_turn_updates) {
        try_move_actor_to_valid_position(body, motion, sprite, actor);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (body->action_state_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
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
                body->unk_9D.u = 0;
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

    actor = (ActorRecord *)((u8 *)actor + 0x88);
    motion->z.unsigned_parts.integer =
        *(u16 *)actor + body->unk_90.parts.high.u;
    sprite->flags |= 0x40;

}
