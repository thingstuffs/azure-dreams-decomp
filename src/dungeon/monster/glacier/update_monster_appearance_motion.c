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

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2A];
    s16 field_2A;
    u8 pad_2C[0x41];
    union {
        s8 s8;
        u8 u8;
    } field_6D;
    u8 pad_6E[0x3];
    u8 field_71;
    u8 pad_72[0x1E];
    union {
        s32 s32;
        struct { u8 pad[0x2]; s16 value; } s16_at_2;
        struct { u8 pad[0x2]; u16 value; } u16_at_2;
    } field_90;
    s16 field_94;
    u8 pad_96[0x2];
    u16 field_98;
    u8 field_9A;
    u8 pad_9B[0x2];
    union {
        s8 s8;
        u8 u8;
    } field_9D;
} EntityArgFieldView_8102F83C;

typedef ActorActionHandler Callback;

extern s32 get_entity_effect_value();
extern s32 refresh_actor_facing_and_lifecycle();
extern s16 sample_terrain_surface_height();

extern u8 glacier_action_resume_address;
extern Callback glacier_callbacks[];

typedef struct S_8017103C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8017103C_1;   /* actor in update_monster_appearance_motion */

typedef struct S_8017103C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017103C_2;   /* motion in update_monster_appearance_motion */

/* Runs entity callbacks, updates monster appearance, and advances motion with floor collision. */
void update_monster_appearance_motion(ActorRecord *body, void *motion_arg, SpriteFrameState *sprite)
{
    S_8017103C_2 *motion = motion_arg;
    SpriteFrameState *monster= sprite;
    S_8017103C_1 *actor = (S_8017103C_1 *)body;
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
    glacier_callbacks[(body->action_id.u)](body, motion, monster, body);

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

        if (!(actor->unk_1C & ACTOR_PARALYZED)) {
            if (!(monster->flags & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            monster->flags |= 0x7000;
        }

        if (!(actor->unk_1C & 0x10000000)) {
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
                apply_monster_koyaw_data(actor->unk_1C,
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        new_flags = (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
        monster->flags = new_flags;
    }

flags_done:
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((body->action_state_flags) & 8) {
        (body->unk_9D.u) = 0;
    } else {
        motion->unk_14 += (body->unk_9D.s) * 0x14000;
        (body->unk_9D.u)++;
    }

    (body->unk_90.value) += motion->unk_14;

    if (!((body->action_state_flags) & 4) && (floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(actor->unk_88.u - 0x20))) < 0x200) {
        actor_height = actor->unk_88.s;
        if ((body->unk_90.parts.high.s) + actor_height < floor_height) {
            actor->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
        } else if (floor_height >= actor_height) {
            (body->unk_90.value) = 0;
            motion->unk_14 = 0;
            actor->unk_1C |= ACTOR_GROUNDED;
            (body->unk_9D.u) = 0;
        } else {
            (body->unk_90.parts.high.s) = floor_height - actor->unk_88.u;
            motion->unk_14 = 0;
            actor->unk_1C |= ACTOR_GROUNDED;
            (body->unk_9D.u) = 0;
        }
        if (actor->unk_1C & ACTOR_REFRESH_GROUND) {
            actor->unk_1C &= ACTOR_REFRESH_GROUND_CLEAR_MASK;
            floor_height = sample_terrain_surface_height(
                (monster->tile_x << 6) | 0x20,
                (monster->tile_y << 6) | 0x20,
                (s16)(actor->unk_88.u - 0x20));
            (body->unk_90.parts.high.s) +=
                actor->unk_88.u - floor_height;
            actor->unk_88.u = floor_height;
        }
    } else {
        actor->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
    }
    motion->unk_0A =
        actor->unk_88.u + (body->unk_90.parts.high.u);
    monster->flags |= 0x40;

}
