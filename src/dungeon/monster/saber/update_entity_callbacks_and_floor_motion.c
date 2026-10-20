#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *, void *, void *, void *);


extern void select_indirect_table_entry();
extern void func_800478B8();
extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern s32 D_80171728;
extern Callback D_80174E5C[];


   /* monster in update_entity_callbacks_and_floor_motion */

typedef struct S_80171320_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80171320_1;   /* actor in update_entity_callbacks_and_floor_motion */

typedef struct S_80171320_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171320_2;   /* motion in update_entity_callbacks_and_floor_motion */

/* Runs entity callbacks, updates monster facing, and applies motion and floor collision. */
void update_entity_callbacks_and_floor_motion(void *entity, S_80171320_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s32 direction_value;
    s16 old_direction;
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        Callback early_callback;

        early_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (early_callback == (Callback)&D_80171728) {
            early_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }


    old_direction = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    D_80174E5C[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)old_direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, monster, entity);
    }

    monster_flags = ((SpriteAnimationTableView *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        direction_value = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((SpriteAnimationTableView *)monster)->unk_2C;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index], ((SpriteAnimationTableView *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            ((SpriteAnimationTableView *)monster)->unk_14 |= 1;
        } else {
            ((SpriteAnimationTableView *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((S_80171320_1 *)actor)->unk_1C & 0x20)) {
            if (!(((SpriteAnimationTableView *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((SpriteAnimationTableView *)monster)->unk_14 |= 0x7000;
        }

        apply_monster_koyaw_data(((S_80171320_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            ((SpriteAnimationTableView *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((SpriteAnimationTableView *)monster)->unk_14 = monster_flags | 0x7000;
        }
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
                              (s16)(((S_80171320_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((S_80171320_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                ((S_80171320_1 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((S_80171320_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((S_80171320_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((S_80171320_1 *)actor)->unk_1C & 0x40000000) {
                ((S_80171320_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((((SpriteAnimationTableView *)monster)->unk_24 << 6) | 0x20,
                                      (((SpriteAnimationTableView *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((S_80171320_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((S_80171320_1 *)actor)->unk_88.u - floor_height;
                ((S_80171320_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((S_80171320_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((S_80171320_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((S_80171320_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((SpriteAnimationTableView *)monster)->unk_14 |= 0x40;

}

