#include "modules/dungeon_ovl_cd7000.h"

void func_8014CC24(void *entity, CL_CD7000_80170C24_S_80170C24_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s32 direction_value;
    s16 old_direction;
    CL_CD7000_80170C24_Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        CL_CD7000_80170C24_Callback early_callback;

        early_callback = (*(CL_CD7000_80170C24_Callback *)((u8 *)entity + 0x8C));
        if (early_callback == func_8014D02C) {
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

    callback = (*(CL_CD7000_80170C24_Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    D_8015133C[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)old_direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, monster, entity);
    }

    monster_flags = ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        direction_value = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index], ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 |= 1;
        } else {
            ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x20)) {
            if (!(((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x7000;
        }

        apply_monster_koyaw_data(((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags | 0x7000;
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
                              (s16)(((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x40000000) {
                ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u - floor_height;
                ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((CL_CD7000_80170C24_S_80170C24_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((CL_CD7000_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x40;

}

