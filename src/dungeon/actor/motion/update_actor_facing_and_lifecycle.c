#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/item.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

extern u8 actor_motion_resume_address;
extern Callback actor_facing_callbacks[];


typedef struct S_800C9AAC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_800C9AAC_2;   /* secondary in update_actor_facing_and_lifecycle */

/* Updates object callbacks, motion, sprite direction, and height. */
void update_actor_facing_and_lifecycle(void *state, ObjectPosition *motion, SpriteFrameState *part)
{
    u32 update_flags = g_dungeon_status.flags;
    S_800C9AAC_2 *secondary = state;
    Callback callback;
    s16 direction;
    s16 direction_index;
    s32 part_flags;
    s32 adjusted_flags;
    s16 target_height;
    u16 old_height;

    if (update_flags & 0x2000) {
        Callback early_callback = (*(Callback *)((u8 *)state + (0x8C)));
        if (early_callback == (Callback)&actor_motion_resume_address) {
            early_callback(state, motion, part, state);
            return;
        } else {
            (*(u8 *)((u8 *)state + (0x71))) &= 0x7F;
        }
        return;
    }

    if (refresh_actor_facing_and_lifecycle(state, motion, part, state) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)state + (0x8C)));
    if (callback != 0) {
        callback(state, motion, part, state);
    }
    actor_facing_callbacks[(*(u8 *)((u8 *)state + (0x9A)))](state, motion, part, state);

    if ((*(s16 *)((u8 *)state + (0xB8))) == 0) {
        part->color.c.r += 4;
        part->color.c.g += 4;
        part->color.c.b += 4;
        if (part->color.c.r >= 0x40) {
            (*(s16 *)((u8 *)state + (0xB8))) = 1;
        }
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    (*(s32 *)((u8 *)state + (0x90))) += motion->velocity_z;

    part_flags = part->flags;
    adjusted_flags = part_flags & 0x8000;
    if (!adjusted_flags) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + secondary->unk_2A + 0x100) >> 9);
        direction &= 7;
        direction_index = direction;
        if ((*(s16 *)((u8 *)state + (0x94))) != direction_index) {
            select_record_entry_and_value(part,
                ((void **)(*(void **)((u8 *)state + (0xA4))))[direction_index],
                part->unk_04);
            (*(s16 *)((u8 *)state + (0x94))) = direction;
        }

        if (dir_sprite_flag[direction_index] != 0) {
            adjusted_flags = part->flags | 1;
            part->flags = adjusted_flags;
            apply_monster_koyaw_data(secondary->unk_1C, (u8 *)part + 0xC);
        } else {
            adjusted_flags = part->flags & 0xFFFE;
            part->flags = adjusted_flags;
            apply_monster_koyaw_data(secondary->unk_1C, (u8 *)part + 0xC);
        }

        if (!(secondary->unk_1C & 0x20)) {
            if (!(part->flags & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            part->flags |= 0x7000;
            secondary->unk_1C &= 0xFFFBFFFF;
        }

        if (secondary->unk_1C & 0x40000) {
            if (!(part->flags & 0x40)) {
                u16 phase = (*(u16 *)((u8 *)state + (0x9E)));
                (*(u16 *)((u8 *)state + (0x9E))) = phase + 1;
                (*(s32 *)((u8 *)state + (0xA0))) += rsin((s16)phase * 0xAA) << 5;
            }

            if (!((*(u16 *)((u8 *)state + (0x98))) & 8)) {
                s32 min_height = -0x20;
                s16 height;
                sample_terrain_surface_height(((u16) motion->x.w.i), ((u16) motion->y.w.i),
                    (s16)(secondary->unk_88 - 0x20));
                height = (*(s16 *)((u8 *)state + (0x92)));
                if (min_height < height) {
                    (*(u16 *)((u8 *)state + (0x92))) -= 8;
                }
                else if (height < -0x28) {
                    (*(u16 *)((u8 *)state + (0x92))) += 8;
                }
            }
        } else {
            s32 height_adjustment = (*(s32 *)((u8 *)state + (0xA0)));
            (*(u16 *)((u8 *)state + (0x9E))) = 0;
            (*(s32 *)((u8 *)state + (0xA0))) = 0;
            (*(s32 *)((u8 *)state + (0x90))) -= height_adjustment;
            if (!((*(u16 *)((u8 *)state + (0x98))) & 8)) {
                target_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                    ((u16) motion->y.w.i),
                    (s16)(secondary->unk_88 - 0x20)) -
                    secondary->unk_88;
                old_height = (*(u16 *)((u8 *)state + (0x92)));
                if ((*(s16 *)((u8 *)state + (0x92))) < target_height) {
                    (*(u16 *)((u8 *)state + (0x92))) = old_height + 8;
                    if (target_height < (*(s16 *)((u8 *)state + (0x92)))) {
                        (*(s16 *)((u8 *)state + (0x92))) = target_height;
                    }
                } else {
                    (*(s16 *)((u8 *)state + (0x92))) = target_height;
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
        object_flags = secondary->unk_1C;
        if (object_flags & 0x40000000) {
            adjusted_flags = object_flags & 0xBFFFFFFF;
            secondary->unk_1C = adjusted_flags;
            target_height = sample_terrain_surface_height(
                (part->tile_x << 6) | 0x20,
                (part->tile_y << 6) | 0x20,
                (s16)(secondary->unk_88 - 0x20));
            if (target_height < 0x200) {
                (*(u16 *)((u8 *)state + (0x92))) += secondary->unk_88 - target_height;
                secondary->unk_88 = target_height;
            }
        }
    }

    motion->z.w.i = secondary->unk_88 +
        (*(u16 *)((u8 *)state + (0x92))) - (*(u16 *)((u8 *)state + (0xA2)));
    part->flags |= 0x40;
}
