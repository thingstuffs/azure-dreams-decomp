#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 uboat_default_frames[];
#include "dungeon/monster/u_boat.h"
extern Callback uboat_callbacks[];

extern void select_indirect_table_entry(void *, u8, s8);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern void apply_monster_koyaw_data(u32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);


   /* part in update_actor_visual_motion */

typedef struct S_801711B0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801711B0_2;   /* base in update_actor_visual_motion */

/* Update object callbacks, motion, facing, and ground-relative height. */
/* Runs U-Boat's callbacks, facing, and motion, adds idle bobbing, and resolves falling and
 * terrain-relative height. */
void update_actor_visual_motion(void *object_arg, ObjectPosition *motion_arg, SpriteFrameState *part_arg)
{
    void *base = object_arg;
    s16 state_or_dir;
    s32 direction;
    s32 prior_state;
    s32 update_value_2;
    void *check_obj;
    void *check_motion;
    void *check_part;
    void *check_context;
    u16 part_flags;
    Callback paused_callback;
    Callback callback;
    s32 new_state;
    s16 ground_height;
    s32 flags;
    s32 normal_flags;
    s32 special_flags;
    u16 new_part_flags;
    u16 bob_step;
    s32 bob_phase;

    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (paused_callback == (Callback)uboat_behavior_entry) {
            void *callback_obj = object_arg;

            paused_callback(callback_obj, motion_arg, part_arg, callback_obj);
            return;
        }
        ((u8 *)object_arg)[113] &= 0x7F;
        return;
    }

    check_obj = object_arg;
    check_motion = motion_arg;
    check_part = part_arg;
    update_value_2 = (*(u8 *)((u8 *)object_arg + (0x6D)));
    check_context = object_arg;
    state_or_dir = (s8)update_value_2;
    if (refresh_actor_facing_and_lifecycle(check_obj, check_motion, check_part, check_context) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
    if (callback != 0) {
        callback(object_arg, motion_arg, part_arg, object_arg);
    }
    uboat_callbacks[(*(u8 *)((u8 *)object_arg + (0x9A)))](object_arg, motion_arg, part_arg, object_arg);

    prior_state = (s32)state_or_dir << 16;
    new_state = (*(s8 *)((u8 *)object_arg + (0x6D)));
    prior_state >>= 16;
    if (prior_state != new_state) {
        try_move_actor_to_valid_position(object_arg, motion_arg, part_arg, object_arg);
    }

    motion_arg->x.v += motion_arg->velocity_x;
    motion_arg->y.v += motion_arg->velocity_y;

    if (!((*(u32 *)((u8 *)object_arg + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        motion_arg->velocity_z += (*(s8 *)((u8 *)object_arg + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)object_arg + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)object_arg + (0x90))) += motion_arg->velocity_z;
    part_flags = part_arg->flags;

    if (!(part_flags & 0x8000)) {
        u16 facing_flags;

        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801711B0_2 *)base)->unk_2A + 0x100) >> 9) & 7;
        state_or_dir = direction;
        if ((*(s16 *)((u8 *)object_arg + (0x94))) != state_or_dir) {
            select_indirect_table_entry(part_arg,
                (*(u8 *)((u8 *)(*(unsigned char **)&part_arg->frameTable) + (state_or_dir))),
                part_arg->unk_04);
            (*(s16 *)((u8 *)object_arg + (0x94))) = direction;
        }

        if (dir_sprite_flag[state_or_dir] != 0) {
            facing_flags = part_arg->flags;
            facing_flags |= 1;
        } else {
            facing_flags = part_arg->flags & 0xFFFE;
        }
        part_arg->flags = facing_flags;

        apply_monster_koyaw_data(((S_801711B0_2 *)base)->unk_1C, (u8 *)part_arg + 0xC);
        if (!(((S_801711B0_2 *)base)->unk_1C & 0x20)) {
            if (!(part_arg->flags & 0x40)) {
                advance_sprite_animation_and_textures(part_arg);
            }
        } else {
            part_arg->flags |= 0x7000;
            ((S_801711B0_2 *)base)->unk_1C &= 0xFFFBFFFF;
        }

        normal_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(part_arg->flags & 0x40) &&
                *(unsigned char **)&part_arg->frameTable == uboat_default_frames) {
                s32 bob_signed;

                bob_step = (*(u16 *)((u8 *)object_arg + (0x9E)))++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                (*(s32 *)((u8 *)object_arg + (0xA0))) +=
                    rsin(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(u16 *)((u8 *)object_arg + (0x92))) = (*(u16 *)((u8 *)object_arg + (0x92))) - 8;
                } else {
                    if ((*(s16 *)((u8 *)object_arg + (0x92))) < -0x28) {
                        (*(u16 *)((u8 *)object_arg + (0x92))) = (*(u16 *)((u8 *)object_arg + (0x92))) + 8;
                    }
                }
            }
        } else {
            s32 bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion_arg->x.w.i),
                                      ((u16) motion_arg->y.w.i),
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    motion_arg->velocity_z = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        new_part_flags = part_flags & 0x800;
        if (new_part_flags) {
            part_arg->flags = part_flags & 0x8FFF;
        } else {
            part_arg->flags = part_flags | 0x7000;
        }

        special_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = special_flags;
        if (!(special_flags & 0x40000)) {
            s32 bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion_arg->x.w.i),
                                      ((u16) motion_arg->y.w.i),
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    motion_arg->velocity_z = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(part_arg->flags & 0x40) &&
                *(unsigned char **)&part_arg->frameTable == uboat_default_frames) {
                s32 bob_signed;

                bob_step = (*(u16 *)((u8 *)object_arg + (0x9E)))++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                (*(s32 *)((u8 *)object_arg + (0xA0))) +=
                    rsin(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(u16 *)((u8 *)object_arg + (0x92))) = (*(u16 *)((u8 *)object_arg + (0x92))) - 8;
                } else if ((*(s16 *)((u8 *)object_arg + (0x92))) < -0x28) {
                    (*(u16 *)((u8 *)object_arg + (0x92))) = (*(u16 *)((u8 *)object_arg + (0x92))) + 8;
                }
            }
        }

        if ((*(u8 *)((u8 *)object_arg + (0xB5))) != 0) {
            (*(u16 *)((u8 *)object_arg + (0x92))) = 0;
        }
    }

    flags = ((S_801711B0_2 *)base)->unk_1C;
    if (flags & 0x40000000) {
        ((S_801711B0_2 *)base)->unk_1C = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (part_arg->unk_24 << 6) | 0x20,
            (part_arg->unk_25 << 6) | 0x20,
            (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)object_arg + (0x92))) += ((S_801711B0_2 *)base)->unk_88 - ground_height;
            ((S_801711B0_2 *)base)->unk_88 = ground_height;
        }
    }

    motion_arg->z.w.i = ((S_801711B0_2 *)base)->unk_88 +
        (*(u16 *)((u8 *)object_arg + (0x92))) - (*(u16 *)((u8 *)object_arg + (0xA2)));
    part_arg->flags |= 0x40;
}
