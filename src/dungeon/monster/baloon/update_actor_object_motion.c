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

extern void advance_sprite_animation_and_textures(void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

extern u8 baloon_default_frames[];
extern void baloon_action_resume_address(void *, void *, void *, void *);
extern Callback baloon_callbacks[];


typedef struct S_80171964_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171964_2;   /* base in update_actor_object_motion */

/* Updates object callbacks, motion, sprite direction, and ground-relative height. */
/* Runs Baloon's callbacks, facing, and motion, adds its idle bob, and uses a separate height rule for
 * action state 24. */
void update_actor_object_motion(void *object_arg, void *motion_arg, SpriteFrameState *part_arg)
{
    S_80171964_2 *base = object_arg;
    Callback first_callback;
    Callback dispatch_callback;
    s32 flags;
    s32 bob_offset;
    s16 ground_height;
    s32 height_adjust;
    s32 height;
    u16 part_flags;

    if (g_dungeon_status.flags & 0x2000) {
        first_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (first_callback == (Callback)baloon_action_resume_address) {
            {
                void *entry_obj = object_arg;

                first_callback(entry_obj, motion_arg, part_arg, entry_obj);
            }
            return;
        }
        (*((u8 *)object_arg + (0x71))) &= 0x7F;
        return;
    }

    {
        s16 old_state = (s8)(*((u8 *)object_arg + (0x6D)));

        if (refresh_actor_facing_and_lifecycle(object_arg, motion_arg, part_arg, object_arg) != 0) {
            return;
        }
        dispatch_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (dispatch_callback != 0) {
            dispatch_callback(object_arg, motion_arg, part_arg, object_arg);
        }
        baloon_callbacks[(*((u8 *)object_arg + (0x9A)))](object_arg, motion_arg, part_arg, object_arg);
        if ((s16)old_state != (s8)(*((u8 *)object_arg + (0x6D)))) {
            try_move_actor_to_valid_position(object_arg, motion_arg, part_arg, object_arg);
        }
    }

    ((ObjectPosition *)motion_arg)->x.v += ((ObjectPosition *)motion_arg)->velocity_x;
    ((ObjectPosition *)motion_arg)->y.v += ((ObjectPosition *)motion_arg)->velocity_y;

    if (!((*(u32 *)((u8 *)object_arg + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        ((ObjectPosition *)motion_arg)->velocity_z += (*(s8 *)((u8 *)object_arg + (0x9D))) * 0x14000;
        (*((u8 *)object_arg + (0x9D)))++;
    } else {
        (*((u8 *)object_arg + (0x9D))) = 0;
    }

    (*(s32 *)((u8 *)object_arg + (0x90))) += ((ObjectPosition *)motion_arg)->velocity_z;
    part_flags = part_arg->flags;

    if (!(part_flags & 0x8000)) {
        s32 view_direction;
        s32 direction_index;
        s16 page_index;
        u8 *page_table;

        view_direction = (g_game_work.view.camera_rotation.parts.viewAngle + base->unk_2A + 0x100) >> 9;
        direction_index = view_direction & 7;
        page_index = direction_index;
        if ((*(s16 *)((u8 *)object_arg + (0x94))) != (s16)page_index) {
            select_indirect_table_entry(part_arg,
                (*((*(u8 **)&part_arg->frameTable) + (page_index))),
                part_arg->unk_04);
            (*(s16 *)((u8 *)object_arg + (0x94))) = direction_index;
        }
        page_table = dir_sprite_flag;
        if (page_table[page_index] != 0) {
            part_arg->flags |= 1;
        } else {
            part_arg->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(((s32)base->unk_1C), (u8 *)part_arg + 0xC);

        if (!(base->unk_1C & 0x20)) {
            if (!(part_arg->flags & 0x40)) {
                advance_sprite_animation_and_textures(part_arg);
            }
        } else {
            part_arg->flags |= 0x7000;
            base->unk_1C &= 0xFFFBFFFF;
        }

        flags = base->unk_1C;
        flags &= 0xF7FFFFFF;
        base->unk_1C = flags;
        flags &= 0x40000;
        if (!flags) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= landing_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                landing_delta = sample_terrain_surface_height(((ObjectPosition *)motion_arg)->x.unsigned_parts.integer,
                                      ((ObjectPosition *)motion_arg)->y.unsigned_parts.integer,
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (landing_delta < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = landing_delta;
                    (*((u8 *)object_arg + (0x9D))) = 0;
                    ((ObjectPosition *)motion_arg)->velocity_z = 0;
                    base->unk_1C |= 0x08000000;
                }
            }
        } else {

            if (!(part_arg->flags & 0x40) &&
                *(u8 **)&part_arg->frameTable == baloon_default_frames) {
                if (*(u16 *)&part_arg->unk_04 == 0x400) {
                    (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
                }
                {
                    u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

                    (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
                    (*(s32 *)((u8 *)object_arg + (0xA0))) = -rsin((s16)bob_frame * 0xC3) << 7;
                }
            }
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                height_adjust = -0x20;
                height = *(s16 *)((u8 *)object_arg + 0x92);
                part_flags = *(u16 *)((u8 *)object_arg + 0x92);
                if (height_adjust < height) {
                    height_adjust = part_flags - 8;
                    *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
                } else {
                    height_adjust = height < -0x28;
                    if (height_adjust) {
                        height_adjust = part_flags + 8;
                        *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
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
        flags = base->unk_1C;
        flags &= 0xF7FFFFFF;
        base->unk_1C = flags;
        flags &= 0x40000;
        if (!flags) {
            bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((ObjectPosition *)motion_arg)->x.unsigned_parts.integer,
                                      ((ObjectPosition *)motion_arg)->y.unsigned_parts.integer,
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*((u8 *)object_arg + (0x9D))) = 0;
                    ((ObjectPosition *)motion_arg)->velocity_z = 0;
                    base->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(part_arg->flags & 0x40) &&
                *(u8 **)&part_arg->frameTable == baloon_default_frames) {
                if (*(u16 *)&part_arg->unk_04 == 0x400) {
                    (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
                }
                {
                    u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

                    (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
                    (*(s32 *)((u8 *)object_arg + (0xA0))) = -rsin((s16)bob_frame * 0xC3) << 7;
                }
            }
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                height_adjust = -0x20;
                height = *(s16 *)((u8 *)object_arg + 0x92);
                part_flags = *(u16 *)((u8 *)object_arg + 0x92);
                if (height_adjust < height) {
                    height_adjust = part_flags - 8;
                    *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
                } else {
                    height_adjust = height < -0x28;
                    if (height_adjust) {
                        height_adjust = part_flags + 8;
                        *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
                    }
                }
            }
        }
    }

    flags = base->unk_1C;
    if (flags & 0x40000000) {
        base->unk_1C = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (part_arg->tile_x << 6) | 0x20,
            (part_arg->tile_y << 6) | 0x20,
            (s16)(base->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)object_arg + (0x92))) += base->unk_88 - ground_height;
            base->unk_88 = ground_height;
        }
    }
    if ((*((u8 *)object_arg + (0x9A))) != 0x18) {
        ((ObjectPosition *)motion_arg)->z.unsigned_parts.integer =
            base->unk_88 + (*(u16 *)((u8 *)object_arg + (0x92))) -
            (*(u16 *)((u8 *)object_arg + (0xA2)));
    } else {
        ((ObjectPosition *)motion_arg)->z.unsigned_parts.integer = (*(u16 *)((u8 *)object_arg + (0x92))) - (*(u16 *)((u8 *)object_arg
            + (0xA2)));
    }
    part_arg->flags |= 0x40;
}
