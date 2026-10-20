#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *, void *, void *, void *);


extern void select_indirect_table_entry(void *, u8, s8);
extern void func_800478B8(void *);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern u8 D_80170EE4[];
extern Callback D_80176680[];


typedef struct S_80170AD0_0 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170AD0_0;   /* actor in update_effect_visuals_and_lifetime */

   /* monster in update_effect_visuals_and_lifetime */

typedef struct S_80170AD0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170AD0_2;   /* motion in update_effect_visuals_and_lifetime */

/* Updates actor callbacks, facing, movement, and floor contact. */
void update_effect_visuals_and_lifetime(void *entity_arg, void *motion_arg, void *monster_arg)
{
    void *actor = entity_arg;
    s16 direction_index;
    register s32 direction;
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    u8 entity_kind;

    if (g_dungeon_status.flags & 0x2000) {
        Callback early_callback;

        early_callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
        if (early_callback == (Callback)D_80170EE4) {
            early_callback(entity_arg, motion_arg, monster_arg, entity_arg);
        } else {
            (*(u8 *)((u8 *)entity_arg + 0x71)) &= 0x7F;
        }
        return;
    }


    direction_index = *(s8 *)((u8 *)entity_arg + 0x6D);
    entity_kind = (*(u8 *)((u8 *)entity_arg + 0x9A));
    if (entity_kind != 0x17 && entity_kind != 0x19) {
        if (refresh_actor_facing_and_lifecycle(entity_arg, motion_arg, monster_arg, entity_arg) != 0) {
            return;
        }
    }

    callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
    if (callback != 0) {
        callback(entity_arg, motion_arg, monster_arg, actor);
    }

    D_80176680[(*(u8 *)((u8 *)entity_arg + 0x9A))](entity_arg, motion_arg, monster_arg, actor);

    if ((s16)direction_index != ((S_80170AD0_0 *)actor)->unk_6D) {
        try_move_actor_to_valid_position(entity_arg, motion_arg, monster_arg, actor);
    }

    monster_flags = ((SpriteAnimationTableView *)monster_arg)->unk_14;
    if (!(monster_flags & 0x8000)) {
        s32 direction_sector;

        direction_sector =
            (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170AD0_0 *)actor)->unk_2A + 0x100) >> 9;
        direction = direction_sector & 7;
        direction_index = direction;

        if ((*(s16 *)((u8 *)entity_arg + 0x94)) != direction_index) {
            u8 *direction_tiles = ((SpriteAnimationTableView *)monster_arg)->unk_2C;
            select_indirect_table_entry(monster_arg, direction_tiles[direction_index],
                          ((SpriteAnimationTableView *)monster_arg)->unk_04);
            (*(s16 *)((u8 *)entity_arg + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_index] != 0) {
            ((SpriteAnimationTableView *)monster_arg)->unk_14 |= 1;
        } else {
            ((SpriteAnimationTableView *)monster_arg)->unk_14 &= 0xFFFE;
        }

        if (!(((S_80170AD0_0 *)actor)->unk_1C.u & 0x20)) {
            if (!(((SpriteAnimationTableView *)monster_arg)->unk_14 & 0x40)) {
                func_800478B8(monster_arg);
            }
        } else {
            ((SpriteAnimationTableView *)monster_arg)->unk_14 |= 0x7000;
        }

        apply_monster_koyaw_data(((S_80170AD0_0 *)actor)->unk_1C.s, (u8 *)monster_arg + 0xC);
    } else {
        ((SpriteAnimationTableView *)monster_arg)->unk_14 =
            (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
    }

    ((S_80170AD0_2 *)motion_arg)->unk_00.at00.v += ((S_80170AD0_2 *)motion_arg)->unk_0C;
    ((S_80170AD0_2 *)motion_arg)->unk_04.at00.v += ((S_80170AD0_2 *)motion_arg)->unk_10;

    if ((*(u16 *)((u8 *)entity_arg + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity_arg + 0x9D)) = 0;
    } else {
        ((S_80170AD0_2 *)motion_arg)->unk_14 += (*(s8 *)((u8 *)entity_arg + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity_arg + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity_arg + 0x90)) += ((S_80170AD0_2 *)motion_arg)->unk_14;

    if (!((*(u16 *)((u8 *)entity_arg + 0x98)) & 4)) {
        floor_height = sample_terrain_surface_height(((S_80170AD0_2 *)motion_arg)->unk_00.at02.v,
                              ((S_80170AD0_2 *)motion_arg)->unk_04.at02.v,
                              (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80170AD0_0 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity_arg + 0x92)) + actor_height < floor_height) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity_arg + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity_arg + 0x92)) = floor_height - ((S_80170AD0_0 *)actor)->unk_88.u;
                }

                ((S_80170AD0_2 *)motion_arg)->unk_14 = 0;
                (*(u8 *)((u8 *)entity_arg + 0x9D)) = 0;
                ((S_80170AD0_0 *)actor)->unk_1C.u |= 0x08000000;
            }

            if (((S_80170AD0_0 *)actor)->unk_1C.u & 0x40000000) {
                ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height(
                    (((SpriteAnimationTableView *)monster_arg)->unk_24 << 6) | 0x20,
                    (((SpriteAnimationTableView *)monster_arg)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170AD0_0 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity_arg + 0x92)) +=
                    ((S_80170AD0_0 *)actor)->unk_88.u - floor_height;
                ((S_80170AD0_0 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
        }
    } else {
        ((S_80170AD0_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
    }

    ((S_80170AD0_2 *)motion_arg)->unk_0A =
        ((S_80170AD0_0 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity_arg + 0x92));
    ((SpriteAnimationTableView *)monster_arg)->unk_14 |= 0x40;

}
