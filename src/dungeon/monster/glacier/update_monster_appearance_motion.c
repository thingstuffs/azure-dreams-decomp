#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "engine/texture.h"
#include "dungeon/item.h"
#include "dungeon/monster/glacier.h"

typedef ActorActionHandler Callback;

extern s32 get_entity_effect_value();
extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

extern u8 glacier_action_resume_address;
extern Callback glacier_callbacks[];



/* Runs entity callbacks, updates monster appearance, and advances motion with floor collision. */
void update_monster_appearance_motion(ActorRecord *body, ObjectPosition *motion_arg, SpriteFrameState *sprite)
{
    ObjectPosition *motion = motion_arg;
    SpriteFrameState *monster= sprite;
    ActorRecord *actor = body;
    s32 direction;
    s16 direction_copy;
    s32 facing_angle;
    s16 old_direction;
    void *call_entity;
    void *call_motion;
    void *call_monster;
    void *call_context;
    s16 direction_index;
    u16 monster_flags;
    u16 new_flags;
    s16 floor_height;
    s16 actor_height;

    if (g_dungeon_status.flags & 0x2000) {
        Callback first_callback;

        first_callback = body->unk_8C.handler;
        if (first_callback == (Callback)&glacier_action_resume_address) {
            first_callback(body, motion_arg, sprite, body);
            return;
        } else {
            (body->movement_queue_state) &= 0x7F;
            return;
        }
    } else {
        call_entity = body;
        call_motion = motion;
        call_monster = monster;
        old_direction = (s8)(body->pending_turn_updates);
        call_context = body;
    }

    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_monster, call_context) != 0) {
        return;
    }

    {
        Callback callback;

        callback = body->unk_8C.handler;
        if (callback != 0) {
            callback(body, motion, monster, body);
        }
    }
    glacier_callbacks[(body->action_id)](body, motion, monster, body);

    if ((s16)old_direction != (body->pending_turn_updates)) {
        try_move_actor_to_valid_position(body, motion, monster, body);
    }

    monster_flags = monster->flags;
    if (!(monster_flags & 0x8000)) {
        facing_angle = g_game_work.view.camera_rotation.parts.viewAngle + (body->facing) + 0x100;
        direction = (facing_angle >> 9) & 7;
        direction_copy = direction;
        direction_index = direction;

        if ((body->unk_94) != direction_index) {
            u8 *tile_map = *(u8 **)&monster->frameTable;

            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index],
                              monster->unk_04);
            }
            (body->unk_94) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            monster->flags |= 1;
        } else {
            monster->flags &= 0xFFFE;
        }

        if (!(((u32)actor->flags1C) & ACTOR_PARALYZED)) {
            if (!(monster->flags & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            monster->flags |= 0x7000;
        }

        if (!(((u32)actor->flags1C) & 0x10000000)) {
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                s32 monster_state = monster->unk_04;
                s32 shade;
                if (monster_state == 0) {
                    monster->color.c.b = 0x80;
                    monster->color.c.g = 0x80;
                    monster->color.c.r = 0x80;
                } else {
                    if (monster_state == 1) {
                        shade = 0x64;
                    } else if (monster_state == 2) {
                        shade = 0x50;
                    } else if (monster_state == 3) {
                        shade = 0x64;
                    } else {
                        goto flags_done;
                    }
                    monster->color.c.b = shade;
                    monster->color.c.g = shade;
                    monster->color.c.r = shade;
                }
            } else {
                apply_monster_koyaw_data(((u32)actor->flags1C),
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        new_flags = (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
        monster->flags = new_flags;
    }

flags_done:
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if ((body->action_state_flags) & 8) {
        (body->unk_9D) = 0;
    } else {
        motion->velocity_z += ((body->unk_9D)) * 0x14000;
        (body->unk_9D)++;
    }

    (body->unk_90.value) += motion->velocity_z;

    if (!((body->action_state_flags) & 4) && (floor_height = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                              motion->y.unsigned_parts.integer,
                              (s16)(actor->ground_height - 0x20))) < 0x200) {
        actor_height = actor->ground_height;
        if ((body->unk_90.parts.high) + actor_height < floor_height) {
            actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        } else if (floor_height >= actor_height) {
            (body->unk_90.value) = 0;
            motion->velocity_z = 0;
            actor->flags1C |= ACTOR_GROUNDED;
            (body->unk_9D) = 0;
        } else {
            (body->unk_90.parts.high) = floor_height - actor->ground_height;
            motion->velocity_z = 0;
            actor->flags1C |= ACTOR_GROUNDED;
            (body->unk_9D) = 0;
        }
        if (((u32)actor->flags1C) & ACTOR_REFRESH_GROUND) {
            actor->flags1C &= ACTOR_REFRESH_GROUND_CLEAR_MASK;
            floor_height = sample_terrain_surface_height(
                (monster->tile_x << 6) | 0x20,
                (monster->tile_y << 6) | 0x20,
                (s16)(actor->ground_height - 0x20));
            (body->unk_90.parts.high) +=
                actor->ground_height - floor_height;
            actor->ground_height = floor_height;
        }
    } else {
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
    }
    motion->z.unsigned_parts.integer =
        actor->ground_height + (body->unk_90.parts.high);
    monster->flags |= 0x40;

}
