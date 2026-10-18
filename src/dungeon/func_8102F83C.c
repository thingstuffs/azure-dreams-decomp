#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2A];
    s16 field_2A;
    u8 pad_2C[0x41];
    union {
        s8 s8;
        u8 u8;
    } field_6D;
    u8 pad_6E[0x3];
    u8 field_71;
    u8 pad_72[0x1E];
    union {
        s32 s32;
        struct { u8 pad[0x2]; s16 value; } s16_at_2;
        struct { u8 pad[0x2]; u16 value; } u16_at_2;
    } field_90;
    s16 field_94;
    u8 pad_96[0x2];
    u16 field_98;
    u8 field_9A;
    u8 pad_9B[0x2];
    union {
        s8 s8;
        u8 u8;
    } field_9D;
} EntityArgFieldView_8102F83C;



typedef void (*Callback)(void *, void *, void *, void *);

extern s32 func_80042900();
extern void select_indirect_table_entry();
extern void func_800478B8();
extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern u8 D_801714B8;
extern Callback D_80176138[];


typedef struct S_8017103C_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8017103C_0;   /* monster in update_monster_appearance_motion */

typedef struct S_8017103C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_8017103C_1;   /* actor in update_monster_appearance_motion */

typedef struct S_8017103C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017103C_2;   /* motion in update_monster_appearance_motion */

/* Runs entity callbacks, updates monster appearance, and advances motion with floor collision. */
void update_monster_appearance_motion(void *entity_arg, void *motion_arg, void *monster_arg)
{
    S_8017103C_2 *motion = motion_arg;
    void *monster = monster_arg;
    S_8017103C_1 *actor = entity_arg;
    s32 direction;
    s16 direction_copy;
    s32 facing_angle;
    s16 old_direction;
    void *call_entity;
    void *call_motion;
    void *call_monster;
    void *call_context;
    s16 direction_index;
    u16 monster_flags;
    u16 new_flags;
    s16 floor_height;
    s16 actor_height;

    if (g_dungeon_status.flags & 0x2000) {
        Callback first_callback;

        first_callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
        if (first_callback == (Callback)&D_801714B8) {
            first_callback(entity_arg, motion_arg, monster_arg, entity_arg);
            return;
        } else {
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_71) &= 0x7F;
            return;
        }
    } else {
        call_entity = entity_arg;
        call_motion = motion;
        call_monster = monster;
        old_direction = (s8)(((EntityArgFieldView_8102F83C *)entity_arg)->field_6D.u8);
        call_context = entity_arg;
    }


    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_monster, call_context) != 0) {
        return;
    }

    {
        Callback callback;

        callback = (*(Callback *)((u8 *)entity_arg + 0x8C));
        if (callback != 0) {
            callback(entity_arg, motion, monster, entity_arg);
        }
    }
    D_80176138[(((EntityArgFieldView_8102F83C *)entity_arg)->field_9A)](entity_arg, motion, monster, entity_arg);

    if ((s16)old_direction != (((EntityArgFieldView_8102F83C *)entity_arg)->field_6D.s8)) {
        try_move_actor_to_valid_position(entity_arg, motion, monster, entity_arg);
    }

    monster_flags = ((S_8017103C_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        facing_angle = g_game_work.view.viewAngle + (((EntityArgFieldView_8102F83C *)entity_arg)->field_2A) + 0x100;
        direction = (facing_angle >> 9) & 7;
        direction_copy = direction;
        direction_index = direction;

        if ((((EntityArgFieldView_8102F83C *)entity_arg)->field_94) != direction_index) {
            u8 *tile_map = ((S_8017103C_0 *)monster)->unk_2C;

            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index],
                              ((S_8017103C_0 *)monster)->unk_04);
            }
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_94) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            ((S_8017103C_0 *)monster)->unk_14 |= 1;
        } else {
            ((S_8017103C_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(actor->unk_1C & 0x20)) {
            if (!(((S_8017103C_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((S_8017103C_0 *)monster)->unk_14 |= 0x7000;
        }

        if (!(actor->unk_1C & 0x10000000)) {
            if ((func_80042900(actor, 1) << 16) != 0) {
                s32 monster_state = ((S_8017103C_0 *)monster)->unk_04;
                s32 shade;
                if (monster_state == 0) {
                    ((S_8017103C_0 *)monster)->unk_0E = 0x80;
                    ((S_8017103C_0 *)monster)->unk_0D = 0x80;
                    ((S_8017103C_0 *)monster)->unk_0C = 0x80;
                } else {
                    if (monster_state == 1) {
                        shade = 0x64;
                    } else if (monster_state == 2) {
                        shade = 0x50;
                    } else if (monster_state == 3) {
                        shade = 0x64;
                    } else {
                        goto flags_done;
                    }
                    ((S_8017103C_0 *)monster)->unk_0E = shade;
                    ((S_8017103C_0 *)monster)->unk_0D = shade;
                    ((S_8017103C_0 *)monster)->unk_0C = shade;
                }
            } else {
                apply_monster_koyaw_data(actor->unk_1C,
                              (u8 *)monster + 0xC);
            }
        }
    } else {
        new_flags = (monster_flags & 0x0800) ? (monster_flags & 0x8FFF) : (monster_flags | 0x7000);
        ((S_8017103C_0 *)monster)->unk_14 = new_flags;
    }

flags_done:
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((((EntityArgFieldView_8102F83C *)entity_arg)->field_98) & 8) {
        (((EntityArgFieldView_8102F83C *)entity_arg)->field_9D.u8) = 0;
    } else {
        motion->unk_14 += (((EntityArgFieldView_8102F83C *)entity_arg)->field_9D.s8) * 0x14000;
        (((EntityArgFieldView_8102F83C *)entity_arg)->field_9D.u8)++;
    }

    (((EntityArgFieldView_8102F83C *)entity_arg)->field_90.s32) += motion->unk_14;

    if (!((((EntityArgFieldView_8102F83C *)entity_arg)->field_98) & 4) && (floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(actor->unk_88.u - 0x20))) < 0x200) {
        actor_height = actor->unk_88.s;
        if ((((EntityArgFieldView_8102F83C *)entity_arg)->field_90.s16_at_2.value) + actor_height < floor_height) {
            actor->unk_1C &= 0xF7FFFFFF;
        } else if (floor_height >= actor_height) {
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_90.s32) = 0;
            motion->unk_14 = 0;
            actor->unk_1C |= 0x08000000;
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_9D.u8) = 0;
        } else {
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_90.s16_at_2.value) = floor_height - actor->unk_88.u;
            motion->unk_14 = 0;
            actor->unk_1C |= 0x08000000;
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_9D.u8) = 0;
        }
        if (actor->unk_1C & 0x40000000) {
            actor->unk_1C &= 0xBFFFFFFF;
            floor_height = sample_terrain_surface_height(
                (((S_8017103C_0 *)monster)->unk_24 << 6) | 0x20,
                (((S_8017103C_0 *)monster)->unk_25 << 6) | 0x20,
                (s16)(actor->unk_88.u - 0x20));
            (((EntityArgFieldView_8102F83C *)entity_arg)->field_90.s16_at_2.value) +=
                actor->unk_88.u - floor_height;
            actor->unk_88.u = floor_height;
        }
    } else {
        actor->unk_1C &= 0xF7FFFFFF;
    }
    motion->unk_0A =
        actor->unk_88.u + (((EntityArgFieldView_8102F83C *)entity_arg)->field_90.u16_at_2.value);
    ((S_8017103C_0 *)monster)->unk_14 |= 0x40;

}
