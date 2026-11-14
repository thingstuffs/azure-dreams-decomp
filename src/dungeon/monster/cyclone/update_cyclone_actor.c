#include "slus.h"
#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "engine/texture.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "sdk/libgte.h"
#include "dungeon/monster/cyclone_frames.h"

typedef struct Actor Actor;
typedef void (*ActorCallback)(Actor *, ObjectPosition *, SpriteFrameState *, Actor *);

struct Actor {
    u8 pad00[0x1C];
    s32 flags;
    u8 pad20[0x0A];
    s16 angle;
    u8 pad2C[0x41];
    u8 type;
    u8 pad6E[3];
    u8 status71;
    u8 pad72[0x16];
    u16 height88;
    u8 pad8A[2];
    ActorCallback callback;
    union { s32 value; ActorScratchHalves halves; } position90;
    s16 direction94;
    u8 pad96[2];
    u16 state98;
    u8 dispatch9A;
    u8 pad9B[2];
    u8 counter9D;
    u8 pad9E[6];
    union { s32 value; ActorScratchHalves halves; } correctionA4;
    u8 padA8[4];
    u16 correctionCountAC;
};

extern ActorCallback cyclone_callbacks[];

extern s32 refresh_actor_facing_and_lifecycle(Actor *, ObjectPosition *, SpriteFrameState *, Actor *);

/* Updates actor direction, callbacks, motion, and ground height. */
/* Runs Cyclone's callbacks, updates table-dependent sprite mirroring and idle bobbing, and resolves ground
 * contact. */
void update_cyclone_actor(Actor *input_actor, ObjectPosition *input_motion, SpriteFrameState *input_entity)
{
    Actor *subject = input_actor;
    s16 direction;
    s16 direction_index;
    s16 old_type;
    s32 height_offset;
    s32 height_adjust;
    ActorCallback special_callback;
    ActorCallback dispatch_callback;
    u16 entity_flags;
    s32 actor_flags;
    s16 ground;
    s32 correction;

    if (g_dungeon_status.flags & 0x2000) {
        special_callback = input_actor->callback;
        if (special_callback == dispatch_cyclone_actions) {
            special_callback((input_actor), input_motion, input_entity, (input_actor));
            return;
        }
        input_actor->status71 &= 0x7F;
        return;
    }

    old_type = (s8)input_actor->type;
    if (refresh_actor_facing_and_lifecycle(input_actor, input_motion, input_entity, input_actor) != 0) {
        return;
    }

    entity_flags = input_entity->flags;
    if (!(entity_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + input_actor->angle + 0x100) >> 9) & 7;
        direction_index = direction;

        if (input_actor->direction94 != direction) {
            if (input_entity->frameTable != 0) {
                select_indirect_table_entry(input_entity, ((u8 *)input_entity->frameTable)[direction], input_entity->unk_04);
            }
            input_actor->direction94 = direction;
        }

        {
            u16 updated_flags;

            if (input_entity->frameTable == cyclone_fade_direction_frames && dir_sprite_flag[direction_index] != 0) {
                updated_flags = input_entity->flags | 1;
            } else {
                updated_flags = input_entity->flags & 0xFFFE;
            }
            input_entity->flags = updated_flags;
        }
        apply_monster_koyaw_data(subject->flags, (u8 *)&input_entity->color);
        if (!(subject->flags & 0x20)) {
            if (!(input_entity->flags & 0x40)) {
                advance_sprite_animation_and_textures(input_entity);
            }
        } else {
            input_entity->flags |= 0x7000;
            subject->flags &= 0xFFFBFFFF;
        }
    } else {
        if (entity_flags & 0x0800) {
            input_entity->flags = entity_flags & 0x8FFF;
        } else {
            input_entity->flags = entity_flags | 0x7000;
        }
    }

    dispatch_callback = input_actor->callback;
    if (dispatch_callback != 0) {
        dispatch_callback(input_actor, input_motion, input_entity, subject);
    }
    cyclone_callbacks[input_actor->dispatch9A](input_actor, input_motion, input_entity, subject);

    if (old_type != (s8)subject->type) {
        try_move_actor_to_valid_position(input_actor, input_motion, input_entity, subject);
    }

    input_motion->x.v += input_motion->velocity_x;
    input_motion->y.v += input_motion->velocity_y;

    if (!(subject->flags & 0x00040000) && !(input_actor->state98 & 8)) {
        input_motion->velocity_z += (s8)input_actor->counter9D * 0x14000;
        input_actor->counter9D++;
    } else {
        input_actor->counter9D = 0;
    }
    input_actor->position90.value += input_motion->velocity_z;

    if (!(input_entity->flags & 0x8000)) {
        actor_flags = subject->flags;
        actor_flags &= 0xF7FFFFFF;
        subject->flags = actor_flags;
        actor_flags &= 0x00040000;
        if (actor_flags) {
            if (!(input_entity->flags & 0x40) && input_entity->frameTable == cyclone_move_direction_frames) {
                u16 correction_count = input_actor->correctionCountAC;
                input_actor->correctionCountAC = correction_count + 1;
                input_actor->correctionA4.value += rsin((s16)correction_count * 0xAA) << 5;
            }
            if (!(input_actor->state98 & 8)) {
                height_adjust = -0x18;
                height_offset = input_actor->position90.halves.high.s;
                entity_flags = input_actor->position90.halves.high.u;
                if (height_adjust < height_offset) {
                    height_adjust = entity_flags - 8;
                    input_actor->position90.halves.high.s = height_adjust;
                } else {
                    height_adjust = height_offset < -0x20;
                    if (height_adjust) {
                        height_adjust = entity_flags + 8;
                        input_actor->position90.halves.high.s = height_adjust;
                    }
                }
            }
        } else {
            s32 reset_correction;

            reset_correction = input_actor->correctionA4.value;
            input_actor->correctionCountAC = 0;
            input_actor->correctionA4.value = 0;
            input_actor->position90.value -= reset_correction;
            if (!(input_actor->state98 & 8)) {
                ground = (s16)(sample_terrain_surface_height(
                    input_motion->x.unsigned_parts.integer,
                    input_motion->y.unsigned_parts.integer,
                    (s16)(subject->height88 - 0x20)) - subject->height88);
                if (ground < input_actor->position90.halves.high.s) {
                    input_actor->position90.halves.high.s = ground;
                    input_actor->counter9D = 0;
                    input_motion->velocity_z = 0;
                    subject->flags |= 0x08000000;
                }
            }
        }
    } else {
        actor_flags = subject->flags;
        actor_flags &= 0xF7FFFFFF;
        subject->flags = actor_flags;
        actor_flags &= 0x00040000;
        if (!actor_flags) {
            correction = input_actor->correctionA4.value;
            input_actor->correctionCountAC = 0;
            input_actor->correctionA4.value = 0;
            input_actor->position90.value -= correction;
            if (!(input_actor->state98 & 8)) {
                ground = (s16)(sample_terrain_surface_height(
                    input_motion->x.unsigned_parts.integer,
                    input_motion->y.unsigned_parts.integer,
                    (s16)(subject->height88 - 0x20)) - subject->height88);
                if (ground < input_actor->position90.halves.high.s) {
                    input_actor->position90.halves.high.s = ground;
                    input_actor->counter9D = 0;
                    input_motion->velocity_z = 0;
                    subject->flags |= 0x08000000;
                }
            }
        } else {
            if (!(input_entity->flags & 0x40) && input_entity->frameTable == cyclone_move_direction_frames) {
                u16 correction_count = input_actor->correctionCountAC;
                input_actor->correctionCountAC = correction_count + 1;
                input_actor->correctionA4.value += rsin((s16)correction_count * 0xAA) << 5;
            }
            if (!(input_actor->state98 & 8)) {
                height_adjust = -0x18;
                height_offset = input_actor->position90.halves.high.s;
                entity_flags = input_actor->position90.halves.high.u;
                if (height_adjust < height_offset) {
                    height_adjust = entity_flags - 8;
                    input_actor->position90.halves.high.s = height_adjust;
                } else {
                    height_adjust = height_offset < -0x20;
                    if (height_adjust) {
                        height_adjust = entity_flags + 8;
                        input_actor->position90.halves.high.s = height_adjust;
                    }
                }
            }
        }
    }

    actor_flags = subject->flags;
    if (actor_flags & 0x40000000) {
        subject->flags = actor_flags & 0xBFFFFFFF;
        ground = sample_terrain_surface_height((input_entity->tile_x << 6) | 0x20,
                               (input_entity->tile_y << 6) | 0x20,
                               (s16)(subject->height88 - 0x20));
        if (ground < 0x200) {
            input_actor->position90.halves.high.s += subject->height88 - ground;
            subject->height88 = ground;
        }
    }

    input_motion->z.w.i = subject->height88 +
                       input_actor->position90.halves.high.u -
                       input_actor->correctionA4.halves.high.u;
    input_entity->flags |= 0x40;

    return;
}
