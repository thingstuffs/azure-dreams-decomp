/* Relink of matched dungeon/func_80D3B9B0; every changed retail word is a paired relocation. */
#define update_actor_visual_motion func_8015F1B0
#define D_80171A80 D_8015FA80
#define D_80176374 D_80164374
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_800E23E0[];
extern u8 D_8015FA80[];
extern Callback D_80164374[];

extern void select_indirect_table_entry(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void apply_monster_koyaw_data(u32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);


typedef struct S_801711B0_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801711B0_0;   /* motion in func_8015F1B0 */

typedef struct S_801711B0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801711B0_1;   /* part in func_8015F1B0 */

typedef struct S_801711B0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801711B0_2;   /* base in func_8015F1B0 */

/* Update object callbacks, motion, facing, and ground-relative height. */
void func_8015F1B0(void *object_arg, void *motion_arg, void *part_arg)
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
        if (paused_callback == (Callback)D_8015FA80) {
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
    D_80164374[(*(u8 *)((u8 *)object_arg + (0x9A)))](object_arg, motion_arg, part_arg, object_arg);

    prior_state = (s32)state_or_dir << 16;
    new_state = (*(s8 *)((u8 *)object_arg + (0x6D)));
    prior_state >>= 16;
    if (prior_state != new_state) {
        try_move_actor_to_valid_position(object_arg, motion_arg, part_arg, object_arg);
    }

    ((S_801711B0_0 *)motion_arg)->unk_00.at00.v += ((S_801711B0_0 *)motion_arg)->unk_0C;
    ((S_801711B0_0 *)motion_arg)->unk_04.at00.v += ((S_801711B0_0 *)motion_arg)->unk_10;

    if (!((*(u32 *)((u8 *)object_arg + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        ((S_801711B0_0 *)motion_arg)->unk_14 += (*(s8 *)((u8 *)object_arg + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)object_arg + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)object_arg + (0x90))) += ((S_801711B0_0 *)motion_arg)->unk_14;
    part_flags = ((S_801711B0_1 *)part_arg)->unk_14;

    if (!(part_flags & 0x8000)) {
        u16 facing_flags;

        direction = ((g_game_work.view.viewAngle + ((S_801711B0_2 *)base)->unk_2A + 0x100) >> 9) & 7;
        state_or_dir = direction;
        if ((*(s16 *)((u8 *)object_arg + (0x94))) != state_or_dir) {
            select_indirect_table_entry(part_arg,
                (*(u8 *)((u8 *)(((S_801711B0_1 *)part_arg)->unk_2C) + (state_or_dir))),
                ((S_801711B0_1 *)part_arg)->unk_04);
            (*(s16 *)((u8 *)object_arg + (0x94))) = direction;
        }

        if (dir_sprite_flag[state_or_dir] != 0) {
            facing_flags = ((S_801711B0_1 *)part_arg)->unk_14;
            facing_flags |= 1;
        } else {
            facing_flags = ((S_801711B0_1 *)part_arg)->unk_14 & 0xFFFE;
        }
        ((S_801711B0_1 *)part_arg)->unk_14 = facing_flags;

        apply_monster_koyaw_data(((S_801711B0_2 *)base)->unk_1C, (u8 *)part_arg + 0xC);
        if (!(((S_801711B0_2 *)base)->unk_1C & 0x20)) {
            if (!(((S_801711B0_1 *)part_arg)->unk_14 & 0x40)) {
                func_800478B8(part_arg);
            }
        } else {
            ((S_801711B0_1 *)part_arg)->unk_14 |= 0x7000;
            ((S_801711B0_2 *)base)->unk_1C &= 0xFFFBFFFF;
        }

        normal_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(((S_801711B0_1 *)part_arg)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part_arg)->unk_2C == D_800E23E0) {
                s32 bob_signed;

                bob_step = (*(u16 *)((u8 *)object_arg + (0x9E)))++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                (*(s32 *)((u8 *)object_arg + (0xA0))) +=
                    func_800644B8(bob_phase) << 4;
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
                ground_height = sample_terrain_surface_height(((S_801711B0_0 *)motion_arg)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion_arg)->unk_04.at02.v,
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    ((S_801711B0_0 *)motion_arg)->unk_14 = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        new_part_flags = part_flags & 0x800;
        if (new_part_flags) {
            ((S_801711B0_1 *)part_arg)->unk_14 = part_flags & 0x8FFF;
        } else {
            ((S_801711B0_1 *)part_arg)->unk_14 = part_flags | 0x7000;
        }

        special_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = special_flags;
        if (!(special_flags & 0x40000)) {
            s32 bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((S_801711B0_0 *)motion_arg)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion_arg)->unk_04.at02.v,
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    ((S_801711B0_0 *)motion_arg)->unk_14 = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((S_801711B0_1 *)part_arg)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part_arg)->unk_2C == D_800E23E0) {
                s32 bob_signed;

                bob_step = (*(u16 *)((u8 *)object_arg + (0x9E)))++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                (*(s32 *)((u8 *)object_arg + (0xA0))) +=
                    func_800644B8(bob_phase) << 4;
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
            (((S_801711B0_1 *)part_arg)->unk_24 << 6) | 0x20,
            (((S_801711B0_1 *)part_arg)->unk_25 << 6) | 0x20,
            (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)object_arg + (0x92))) += ((S_801711B0_2 *)base)->unk_88 - ground_height;
            ((S_801711B0_2 *)base)->unk_88 = ground_height;
        }
    }

    ((S_801711B0_0 *)motion_arg)->unk_0A = ((S_801711B0_2 *)base)->unk_88 +
        (*(u16 *)((u8 *)object_arg + (0x92))) - (*(u16 *)((u8 *)object_arg + (0xA2)));
    ((S_801711B0_1 *)part_arg)->unk_14 |= 0x40;
}
