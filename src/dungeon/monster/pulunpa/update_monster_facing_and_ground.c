#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry();
extern void advance_sprite_animation_and_textures();
extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern u8 D_80170F20;
extern u8 D_80173B98;
extern Callback D_80176380[];
extern Callback D_801763E0[];

   /* monster in update_monster_facing_and_ground */

typedef struct S_80170AE0_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170AE0_1;   /* actor in update_monster_facing_and_ground */

typedef struct S_80170AE0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170AE0_2;   /* motion in update_monster_facing_and_ground */

/* Updates monster facing, runs actor callbacks, and applies movement and floor height corrections. */
void update_monster_facing_and_ground(void *entity, S_80170AE0_2 *motion, SpriteFrameState *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s16 old_direction;
    u32 old_direction_raw;
    s32 facing_angle;
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        Callback special_callback;

        special_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (special_callback == (Callback)&D_80170F20 ||
            special_callback == (Callback)&D_80173B98) {
            special_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    old_direction = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    monster_flags = monster->flags;
    if (!(monster_flags & 0x8000)) {
        facing_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (facing_angle >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = *(unsigned char **)&monster->frameTable;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index], monster->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        old_direction_raw = (s32)dir_sprite_flag + direction_copy;
        if (*(u8 *)old_direction_raw != 0) {
            monster->flags |= 1;
        } else {
            monster->flags &= 0xFFFE;
        }

        if (!(((S_80170AE0_1 *)actor)->unk_1C & 0x20)) {
            if (!(monster->flags & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            monster->flags |= 0x7000;
        }

        apply_monster_koyaw_data(((S_80170AE0_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            monster->flags = monster_flags & 0x8FFF;
        } else {
            monster->flags = monster_flags | 0x7000;
        }
    }

    callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    if ((*(u8 *)((u8 *)entity + 0xA7))) {
        D_801763E0[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);
    } else {
        D_80176380[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);
    }

    if (old_direction != ((S_80170AE0_1 *)actor)->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, monster, actor);
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((S_80170AE0_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80170AE0_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                (*(u16 *)((u8 *)entity + 0x98)) &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((S_80170AE0_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((S_80170AE0_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((S_80170AE0_1 *)actor)->unk_1C & 0x40000000) {
                ((S_80170AE0_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((monster->unk_24 << 6) | 0x20,
                                      (monster->unk_25 << 6) | 0x20,
                                      (s16)(((S_80170AE0_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((S_80170AE0_1 *)actor)->unk_88.u - floor_height;
                ((S_80170AE0_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((S_80170AE0_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((S_80170AE0_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    actor = (u8 *)actor + 0x88;
    motion->unk_0A =
        *(u16 *)actor + (*(u16 *)((u8 *)entity + 0x92));
    monster->flags |= 0x40;

}
