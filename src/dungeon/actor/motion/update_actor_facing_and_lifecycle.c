#include "common.h"
#include "slus.h"
#include "slus/imports.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "sdk/libgte.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

extern u8 actor_motion_resume_address;
extern Callback actor_facing_callbacks[];



/* Updates object callbacks, motion, sprite direction, and height. */
void update_actor_facing_and_lifecycle(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *part)
{
    u32 update_flags = g_dungeon_status.flags;
    ActorRecord *secondary = body;
    ActorActionHandler callback;
    s16 direction;
    s16 direction_index;
    s32 part_flags;
    s32 adjusted_flags;
    s16 target_height;
    u16 old_height;

    if (update_flags & 0x2000) {
        ActorActionHandler early_callback = body->unk_8C.handler;
        if (early_callback == (ActorActionHandler)&actor_motion_resume_address) {
            early_callback(body, motion, part, body);
            return;
        } else {
            body->movement_queue_state &= 0x7F;
        }
        return;
    }

    if (refresh_actor_facing_and_lifecycle(body, motion, part, body) != 0) {
        return;
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, motion, part, body);
    }
    actor_facing_callbacks[body->action_id](body, motion, part, body);

    if ((*(s16 *)((u8 *)body + (0xB8))) == 0) {
        part->color.c.r += 4;
        part->color.c.g += 4;
        part->color.c.b += 4;
        if (part->color.c.r >= 0x40) {
            (*(s16 *)((u8 *)body + (0xB8))) = 1;
        }
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    body->unk_90.value += motion->velocity_z;

    part_flags = part->flags;
    adjusted_flags = part_flags & 0x8000;
    if (!adjusted_flags) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + secondary->facing + 0x100) >> 9);
        direction &= 7;
        direction_index = direction;
        if (body->unk_94 != direction_index) {
            select_record_entry_and_value(part,
                ((void **)body->unk_A4.address)[direction_index],
                part->unk_04);
            body->unk_94 = direction;
        }

        if (dir_sprite_flag[direction_index] != 0) {
            adjusted_flags = part->flags | 1;
            part->flags = adjusted_flags;
            apply_monster_koyaw_data(secondary->flags1C, (u8 *)part + 0xC);
        } else {
            adjusted_flags = part->flags & 0xFFFE;
            part->flags = adjusted_flags;
            apply_monster_koyaw_data(secondary->flags1C, (u8 *)part + 0xC);
        }

        if (!(secondary->flags1C & 0x20)) {
            if (!(part->flags & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            part->flags |= 0x7000;
            secondary->flags1C &= 0xFFFBFFFF;
        }

        if (secondary->flags1C & 0x40000) {
            if (!(part->flags & 0x40)) {
                u16 phase = body->unk_9E;
                body->unk_9E = phase + 1;
                body->unk_A0.value += rsin((s16)phase * 0xAA) << 5;
            }

            if (!(body->action_state_flags & 8)) {
                s32 min_height = -0x20;
                s16 height;
                sample_terrain_surface_height(((u16) motion->x.w.i), ((u16) motion->y.w.i),
                    (s16)(((u16)secondary->ground_height) - 0x20));
                height = body->unk_90.parts.high.s;
                if (min_height < height) {
                    body->unk_90.parts.high.u -= 8;
                }
                else if (height < -0x28) {
                    body->unk_90.parts.high.u += 8;
                }
            }
        } else {
            s32 height_adjustment = body->unk_A0.value;
            body->unk_9E = 0;
            body->unk_A0.value = 0;
            body->unk_90.value -= height_adjustment;
            if (!(body->action_state_flags & 8)) {
                target_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                    ((u16) motion->y.w.i),
                    (s16)(((u16)secondary->ground_height) - 0x20)) -
                    ((u16)secondary->ground_height);
                old_height = body->unk_90.parts.high.u;
                if (body->unk_90.parts.high.s < target_height) {
                    body->unk_90.parts.high.u = old_height + 8;
                    if (target_height < body->unk_90.parts.high.s) {
                        body->unk_90.parts.high.s = target_height;
                    }
                } else {
                    body->unk_90.parts.high.s = target_height;
                }
            }
        }
    } else {
        adjusted_flags = part_flags & 0x800;
        if (adjusted_flags) {
            adjusted_flags = part_flags & 0x8FFF;
        } else {
            adjusted_flags = part_flags | 0x7000;
        }
        part->flags = adjusted_flags;
    }

    {
        s32 object_flags;
        object_flags = secondary->flags1C;
        if (object_flags & 0x40000000) {
            adjusted_flags = object_flags & 0xBFFFFFFF;
            secondary->flags1C = adjusted_flags;
            target_height = sample_terrain_surface_height(
                (part->tile_x << 6) | 0x20,
                (part->tile_y << 6) | 0x20,
                (s16)(((u16)secondary->ground_height) - 0x20));
            if (target_height < 0x200) {
                body->unk_90.parts.high.u += ((u16)secondary->ground_height) - target_height;
                secondary->ground_height = target_height;
            }
        }
    }

    motion->z.w.i = ((u16)secondary->ground_height) +
        body->unk_90.parts.high.u - body->unk_A0.parts.high;
    part->flags |= 0x40;
}
