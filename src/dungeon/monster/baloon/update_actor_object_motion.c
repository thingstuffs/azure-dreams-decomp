#include "slus.h"
#include "dungeon/monster/baloon_frames.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "dungeon/actor.h"
#include "sdk/libgte.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);


extern void baloon_action_resume_address(void *, void *, void *, void *);
extern Callback baloon_callbacks[];


/* Updates object callbacks, motion, sprite direction, and ground-relative height. */
/* Runs Baloon's callbacks, facing, and motion, adds its idle bob, and uses a separate height rule for
 * action state 24. */
void update_actor_object_motion(ActorRecord *object_arg, void *motion_arg, SpriteFrameState *part_arg)
{
    ActorRecord *base = object_arg;
    ActorActionHandler first_callback;
    ActorActionHandler dispatch_callback;
    s32 flags;
    s32 bob_offset;
    s16 ground_height;
    s32 height_adjust;
    s32 height;
    u16 part_flags;

    if (g_dungeon_status.flags & 0x2000) {
        first_callback = object_arg->unk_8C.handler;
        if (first_callback == (ActorActionHandler)baloon_action_resume_address) {
            {
                void *entry_obj = object_arg;

                first_callback(entry_obj, motion_arg, part_arg, entry_obj);
            }
            return;
        }
        object_arg->movement_queue_state &= 0x7F;
        return;
    }

    {
        s16 old_state = object_arg->pending_turn_updates;

        if (refresh_actor_facing_and_lifecycle(object_arg, motion_arg, part_arg, object_arg) != 0) {
            return;
        }
        dispatch_callback = object_arg->unk_8C.handler;
        if (dispatch_callback != 0) {
            dispatch_callback(object_arg, motion_arg, part_arg, object_arg);
        }
        baloon_callbacks[object_arg->action_id](object_arg, motion_arg, part_arg, object_arg);
        if (old_state != object_arg->pending_turn_updates) {
            try_move_actor_to_valid_position(object_arg, motion_arg, part_arg, object_arg);
        }
    }

    ((ObjectPosition *)motion_arg)->x.v += ((ObjectPosition *)motion_arg)->velocity_x;
    ((ObjectPosition *)motion_arg)->y.v += ((ObjectPosition *)motion_arg)->velocity_y;

    if (!(object_arg->flags1C & 0x40000) &&
        !(object_arg->action_state_flags & 8)) {
        ((ObjectPosition *)motion_arg)->velocity_z += object_arg->unk_9D * 0x14000;
        object_arg->unk_9D++;
    } else {
        object_arg->unk_9D = 0;
    }

    object_arg->unk_90.value += ((ObjectPosition *)motion_arg)->velocity_z;
    part_flags = part_arg->flags;

    if (!(part_flags & 0x8000)) {
        s32 view_direction;
        s32 direction_index;
        s16 page_index;
        u8 *page_table;

        view_direction = (g_game_work.view.camera_rotation.parts.viewAngle + base->facing + 0x100) >> 9;
        direction_index = view_direction & 7;
        page_index = direction_index;
        if (object_arg->unk_94 != (s16)page_index) {
            select_indirect_table_entry(part_arg,
                (*((*(u8 **)&part_arg->frameTable) + (page_index))),
                part_arg->unk_04);
            object_arg->unk_94 = direction_index;
        }
        page_table = dir_sprite_flag;
        if (page_table[page_index] != 0) {
            part_arg->flags |= 1;
        } else {
            part_arg->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(base->flags1C, (u8 *)part_arg + 0xC);

        if (!(base->flags1C & 0x20)) {
            if (!(part_arg->flags & 0x40)) {
                advance_sprite_animation_and_textures(part_arg);
            }
        } else {
            part_arg->flags |= 0x7000;
            base->flags1C &= 0xFFFBFFFF;
        }

        flags = base->flags1C;
        flags &= 0xF7FFFFFF;
        base->flags1C = flags;
        flags &= 0x40000;
        if (!flags) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = object_arg->unk_A0.value;
            object_arg->unk_9E = 0;
            object_arg->unk_A0.value = 0;
            object_arg->unk_90.value -= landing_offset;
            if (!(object_arg->action_state_flags & 8)) {
                landing_delta = sample_terrain_surface_height(((ObjectPosition *)motion_arg)->x.unsigned_parts.integer,
                                      ((ObjectPosition *)motion_arg)->y.unsigned_parts.integer,
                                      (s16)(base->ground_height - 0x20)) -
                        base->ground_height;
                if (landing_delta < object_arg->unk_90.parts.high) {
                    object_arg->unk_90.parts.high = landing_delta;
                    object_arg->unk_9D = 0;
                    ((ObjectPosition *)motion_arg)->velocity_z = 0;
                    base->flags1C |= 0x08000000;
                }
            }
        } else {

            if (!(part_arg->flags & 0x40) &&
                *(u8 **)&part_arg->frameTable == baloon_default_frames) {
                if (*(u16 *)&part_arg->unk_04 == 0x400) {
                    object_arg->unk_9E = 0;
                }
                {
                    u16 bob_frame = object_arg->unk_9E;

                    object_arg->unk_9E = bob_frame + 1;
                    object_arg->unk_A0.value = -rsin((s16)bob_frame * 0xC3) << 7;
                }
            }
            if (!(object_arg->action_state_flags & 8)) {
                height_adjust = -0x20;
                height = object_arg->unk_90.parts.high;
                part_flags = object_arg->unk_90.parts.high;
                if (height_adjust < height) {
                    height_adjust = part_flags - 8;
                    object_arg->unk_90.parts.high = height_adjust;
                } else {
                    height_adjust = height < -0x28;
                    if (height_adjust) {
                        height_adjust = part_flags + 8;
                        object_arg->unk_90.parts.high = height_adjust;
                    }
                }
            }
        }
    } else {
        if (part_flags & 0x800) {
            part_arg->flags = part_flags & 0x8FFF;
        } else {
            part_arg->flags = part_flags | 0x7000;
        }
        flags = base->flags1C;
        flags &= 0xF7FFFFFF;
        base->flags1C = flags;
        flags &= 0x40000;
        if (!flags) {
            bob_offset = object_arg->unk_A0.value;
            object_arg->unk_9E = 0;
            object_arg->unk_A0.value = 0;
            object_arg->unk_90.value -= bob_offset;
            if (!(object_arg->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(((ObjectPosition *)motion_arg)->x.unsigned_parts.integer,
                                      ((ObjectPosition *)motion_arg)->y.unsigned_parts.integer,
                                      (s16)(base->ground_height - 0x20)) -
                        base->ground_height;
                if (ground_height < object_arg->unk_90.parts.high) {
                    object_arg->unk_90.parts.high = ground_height;
                    object_arg->unk_9D = 0;
                    ((ObjectPosition *)motion_arg)->velocity_z = 0;
                    base->flags1C |= 0x08000000;
                }
            }
        } else {
            if (!(part_arg->flags & 0x40) &&
                *(u8 **)&part_arg->frameTable == baloon_default_frames) {
                if (*(u16 *)&part_arg->unk_04 == 0x400) {
                    object_arg->unk_9E = 0;
                }
                {
                    u16 bob_frame = object_arg->unk_9E;

                    object_arg->unk_9E = bob_frame + 1;
                    object_arg->unk_A0.value = -rsin((s16)bob_frame * 0xC3) << 7;
                }
            }
            if (!(object_arg->action_state_flags & 8)) {
                height_adjust = -0x20;
                height = object_arg->unk_90.parts.high;
                part_flags = object_arg->unk_90.parts.high;
                if (height_adjust < height) {
                    height_adjust = part_flags - 8;
                    object_arg->unk_90.parts.high = height_adjust;
                } else {
                    height_adjust = height < -0x28;
                    if (height_adjust) {
                        height_adjust = part_flags + 8;
                        object_arg->unk_90.parts.high = height_adjust;
                    }
                }
            }
        }
    }

    flags = base->flags1C;
    if (flags & 0x40000000) {
        base->flags1C = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (part_arg->tile_x << 6) | 0x20,
            (part_arg->tile_y << 6) | 0x20,
            (s16)(base->ground_height - 0x20));
        if (ground_height < 0x200) {
            object_arg->unk_90.parts.high += base->ground_height - ground_height;
            base->ground_height = ground_height;
        }
    }
    if (object_arg->action_id != 0x18) {
        ((ObjectPosition *)motion_arg)->z.unsigned_parts.integer =
            base->ground_height + object_arg->unk_90.parts.high -
            object_arg->unk_A0.parts.high;
    } else {
        ((ObjectPosition *)motion_arg)->z.unsigned_parts.integer = object_arg->unk_90.parts.high - object_arg->unk_A0.parts.high;
    }
    part_arg->flags |= 0x40;
}
