#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry(void *, u8, s8);
extern void advance_sprite_animation_and_textures(void *);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);
extern void start_direction_based_action(void *, void *, void *, void *);

extern u8 D_801716F4[];
extern Callback barong_callbacks[];

typedef struct S_801712A8_0 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_801712A8_0;   /* actor in update_actor_facing_and_floor_contact */

   /* monster in update_actor_facing_and_floor_contact */

typedef struct S_801712A8_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801712A8_2;   /* motion in update_actor_facing_and_floor_contact */

/* Updates actor behavior, facing, movement, and floor contact. */
void update_actor_facing_and_floor_contact(void *entity, S_801712A8_2 *motion, SpriteFrameState *monster)
{
    void *actor = entity;
    u16 direction;
    u32 direction_copy;
    Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        Callback first_callback;

        first_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (first_callback == (Callback)D_801716F4) {
            first_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    direction = *(s8 *)((u8 *)entity + 0x6D);
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    if ((*(u32 *)((u8 *)entity + 0x14)) & 0x00800000) {
        if ((*(u8 *)((u8 *)entity + 0x9A)) != 0x17) {
            (*(u32 *)((u8 *)entity + 0x14)) &= 0xFF7FFFFF;
            start_direction_based_action(entity, motion, monster, entity);
        }
    }

    callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    barong_callbacks[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);

    if ((s16)direction != ((S_801712A8_0 *)actor)->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, monster, actor);
    }

    monster_flags = monster->flags;
    if (!(monster_flags & 0x8000)) {
        s32 angle_sector;

        angle_sector =
            (g_game_work.view.camera_rotation.parts.viewAngle + ((S_801712A8_0 *)actor)->unk_2A + 0x100) >> 9;
        direction = angle_sector & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = *(unsigned char **)&monster->frameTable;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index],
                              monster->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            monster->flags |= 1;
        } else {
            monster->flags &= 0xFFFE;
        }

        if (!(((S_801712A8_0 *)actor)->unk_1C.u & 0x20)) {
            if (!(monster->flags & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            monster->flags |= 0x7000;
        }

        apply_monster_koyaw_data(((S_801712A8_0 *)actor)->unk_1C.s, (u8 *)monster + 0xC);
    } else {
        monster->flags =
            (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
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

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4) && (floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((S_801712A8_0 *)actor)->unk_88.u - 0x20))) < 0x200) {
        actor_height = ((S_801712A8_0 *)actor)->unk_88.s;
        if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
            ((S_801712A8_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
        } else if (floor_height >= actor_height) {
            (*(s32 *)((u8 *)entity + 0x90)) = 0;
            motion->unk_14 = 0;
            ((S_801712A8_0 *)actor)->unk_1C.u |= 0x08000000;
            (*(u8 *)((u8 *)entity + 0x9D)) = 0;
        } else {
            (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((S_801712A8_0 *)actor)->unk_88.u;
            motion->unk_14 = 0;
            ((S_801712A8_0 *)actor)->unk_1C.u |= 0x08000000;
            (*(u8 *)((u8 *)entity + 0x9D)) = 0;
        }
        if (((S_801712A8_0 *)actor)->unk_1C.u & 0x40000000) {
            ((S_801712A8_0 *)actor)->unk_1C.u &= 0xBFFFFFFF;
            floor_height = sample_terrain_surface_height(
                (monster->unk_24 << 6) | 0x20,
                (monster->unk_25 << 6) | 0x20,
                (s16)(((S_801712A8_0 *)actor)->unk_88.u - 0x20));
            (*(s16 *)((u8 *)entity + 0x92)) +=
                ((S_801712A8_0 *)actor)->unk_88.u - floor_height;
            ((S_801712A8_0 *)actor)->unk_88.u = floor_height;
        }
    } else {
        ((S_801712A8_0 *)actor)->unk_1C.u &= 0xF7FFFFFF;
    }
    motion->unk_0A =
        ((S_801712A8_0 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    monster->flags |= 0x40;

}
