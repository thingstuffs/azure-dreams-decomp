#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry(void *, u8, s8);
extern void advance_sprite_animation_and_textures(void *);
extern s32 func_800644B8(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern u8 baloon_default_frames[];
extern void D_80171F1C(void *, void *, void *, void *);
extern Callback baloon_callbacks[];


typedef struct S_80171964_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171964_0;   /* motion in update_actor_object_motion */

typedef struct S_80171964_1 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171964_1;   /* part in update_actor_object_motion */

typedef struct S_80171964_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171964_2;   /* base in update_actor_object_motion */

/* Updates object callbacks, motion, sprite direction, and ground-relative height. */
void update_actor_object_motion(void *object_arg, void *motion_arg, void *part_arg)
{
    void *base = object_arg;
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
        if (first_callback == (Callback)D_80171F1C) {
            {
                void *entry_obj = object_arg;

                first_callback(entry_obj, motion_arg, part_arg, entry_obj);
            }
            return;
        }
        (*(u8 *)((u8 *)object_arg + (0x71))) &= 0x7F;
        return;
    }


    {
        s16 old_state = (s8)(*(u8 *)((u8 *)object_arg + (0x6D)));

        if (refresh_actor_facing_and_lifecycle(object_arg, motion_arg, part_arg, object_arg) != 0) {
            return;
        }
        dispatch_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (dispatch_callback != 0) {
            dispatch_callback(object_arg, motion_arg, part_arg, object_arg);
        }
        baloon_callbacks[(*(u8 *)((u8 *)object_arg + (0x9A)))](object_arg, motion_arg, part_arg, object_arg);
        if ((s16)old_state != (s8)(*(u8 *)((u8 *)object_arg + (0x6D)))) {
            try_move_actor_to_valid_position(object_arg, motion_arg, part_arg, object_arg);
        }
    }

    ((S_80171964_0 *)motion_arg)->unk_00.at00.v += ((S_80171964_0 *)motion_arg)->unk_0C;
    ((S_80171964_0 *)motion_arg)->unk_04.at00.v += ((S_80171964_0 *)motion_arg)->unk_10;

    if (!((*(u32 *)((u8 *)object_arg + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        ((S_80171964_0 *)motion_arg)->unk_14 += (*(s8 *)((u8 *)object_arg + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)object_arg + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
    }

    (*(s32 *)((u8 *)object_arg + (0x90))) += ((S_80171964_0 *)motion_arg)->unk_14;
    part_flags = ((S_80171964_1 *)part_arg)->unk_14;

    if (!(part_flags & 0x8000)) {
        s32 view_direction;
        s32 direction_index;
        s16 page_index;
        u8 *page_table;

        view_direction = (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80171964_2 *)base)->unk_2A + 0x100) >> 9;
        direction_index = view_direction & 7;
        page_index = direction_index;
        if ((*(s16 *)((u8 *)object_arg + (0x94))) != (s16)page_index) {
            select_indirect_table_entry(part_arg,
                (*(u8 *)((u8 *)(((S_80171964_1 *)part_arg)->unk_2C) + (page_index))),
                ((S_80171964_1 *)part_arg)->unk_04.s8);
            (*(s16 *)((u8 *)object_arg + (0x94))) = direction_index;
        }
        page_table = dir_sprite_flag;
        if (page_table[page_index] != 0) {
            ((S_80171964_1 *)part_arg)->unk_14 |= 1;
        } else {
            ((S_80171964_1 *)part_arg)->unk_14 &= 0xFFFE;
        }
        apply_monster_koyaw_data(((S_80171964_2 *)base)->unk_1C.s, (u8 *)part_arg + 0xC);

        if (!(((S_80171964_2 *)base)->unk_1C.u & 0x20)) {
            if (!(((S_80171964_1 *)part_arg)->unk_14 & 0x40)) {
                advance_sprite_animation_and_textures(part_arg);
            }
        } else {
            ((S_80171964_1 *)part_arg)->unk_14 |= 0x7000;
            ((S_80171964_2 *)base)->unk_1C.u &= 0xFFFBFFFF;
        }

        flags = ((S_80171964_2 *)base)->unk_1C.u;
        flags &= 0xF7FFFFFF;
        ((S_80171964_2 *)base)->unk_1C.u = flags;
        flags &= 0x40000;
        if (!flags) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= landing_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                landing_delta = sample_terrain_surface_height(((S_80171964_0 *)motion_arg)->unk_00.at02.v,
                                      ((S_80171964_0 *)motion_arg)->unk_04.at02.v,
                                      (s16)(((S_80171964_2 *)base)->unk_88 - 0x20)) -
                        ((S_80171964_2 *)base)->unk_88;
                if (landing_delta < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = landing_delta;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    ((S_80171964_0 *)motion_arg)->unk_14 = 0;
                    ((S_80171964_2 *)base)->unk_1C.u |= 0x08000000;
                }
            }
        } else {

            if (!(((S_80171964_1 *)part_arg)->unk_14 & 0x40) &&
                ((S_80171964_1 *)part_arg)->unk_2C == baloon_default_frames) {
                if (((S_80171964_1 *)part_arg)->unk_04.u16 == 0x400) {
                    (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
                }
                {
                    u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

                    (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
                    (*(s32 *)((u8 *)object_arg + (0xA0))) = -func_800644B8((s16)bob_frame * 0xC3) << 7;
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
            ((S_80171964_1 *)part_arg)->unk_14 = part_flags & 0x8FFF;
        } else {
            ((S_80171964_1 *)part_arg)->unk_14 = part_flags | 0x7000;
        }
        flags = ((S_80171964_2 *)base)->unk_1C.u;
        flags &= 0xF7FFFFFF;
        ((S_80171964_2 *)base)->unk_1C.u = flags;
        flags &= 0x40000;
        if (!flags) {
            bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
            (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((S_80171964_0 *)motion_arg)->unk_00.at02.v,
                                      ((S_80171964_0 *)motion_arg)->unk_04.at02.v,
                                      (s16)(((S_80171964_2 *)base)->unk_88 - 0x20)) -
                        ((S_80171964_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                    (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                    ((S_80171964_0 *)motion_arg)->unk_14 = 0;
                    ((S_80171964_2 *)base)->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(((S_80171964_1 *)part_arg)->unk_14 & 0x40) &&
                ((S_80171964_1 *)part_arg)->unk_2C == baloon_default_frames) {
                if (((S_80171964_1 *)part_arg)->unk_04.u16 == 0x400) {
                    (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
                }
                {
                    u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

                    (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
                    (*(s32 *)((u8 *)object_arg + (0xA0))) = -func_800644B8((s16)bob_frame * 0xC3) << 7;
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

    flags = ((S_80171964_2 *)base)->unk_1C.u;
    if (flags & 0x40000000) {
        ((S_80171964_2 *)base)->unk_1C.u = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (((S_80171964_1 *)part_arg)->unk_24 << 6) | 0x20,
            (((S_80171964_1 *)part_arg)->unk_25 << 6) | 0x20,
            (s16)(((S_80171964_2 *)base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)object_arg + (0x92))) += ((S_80171964_2 *)base)->unk_88 - ground_height;
            ((S_80171964_2 *)base)->unk_88 = ground_height;
        }
    }
    if ((*(u8 *)((u8 *)object_arg + (0x9A))) != 0x18) {
        ((S_80171964_0 *)motion_arg)->unk_0A =
            ((S_80171964_2 *)base)->unk_88 + (*(u16 *)((u8 *)object_arg + (0x92))) -
            (*(u16 *)((u8 *)object_arg + (0xA2)));
    } else {
        ((S_80171964_0 *)motion_arg)->unk_0A = (*(u16 *)((u8 *)object_arg + (0x92))) - (*(u16 *)((u8 *)object_arg
            + (0xA2)));
    }
    ((S_80171964_1 *)part_arg)->unk_14 |= 0x40;
}
