#include "modules/dungeon_ovl_e0365c.h"

void dungeonUpdateEntityFacingAndGround(void *entity, E_80170A58_S_80170A58_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s16 old_direction;
    s32 facing_angle;
    E_80170A58_Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (dungeonStatus.flags & 0x2000) {
        E_80170A58_Callback early_callback;

        early_callback = (*(E_80170A58_Callback *)((u8 *)entity + 0x8C));
        if (early_callback == (E_80170A58_Callback)&func_80170E5C) {
            early_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }


    old_direction = (*(s8 *)((u8 *)entity + 0x6D));
    if (dungeonRefreshActorFacingAndLifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    monster_flags = ((E_80170A58_S_80170A58_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        facing_angle = gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (facing_angle >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((E_80170A58_S_80170A58_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                selectIndirectTableEntry(monster, tile_map[direction_index], ((E_80170A58_S_80170A58_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dirSpriteFlag[direction_copy] != 0) {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 1;
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((E_80170A58_S_80170A58_1 *)actor)->unk_1C & 0x20)) {
            if (!(((E_80170A58_S_80170A58_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
            dungeonApplyMonsterKoyawData(((E_80170A58_S_80170A58_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 0x7000;
            dungeonApplyMonsterKoyawData(((E_80170A58_S_80170A58_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
        }
    } else {
        if (monster_flags & 0x0800) {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 = monster_flags | 0x7000;
        }
    }

    callback = (*(E_80170A58_Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    D_80174568[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);

    if (old_direction != ((E_80170A58_S_80170A58_1 *)actor)->unk_6D) {
        func_800AA36C(entity, motion, monster, actor);
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
        floor_height = func_800BCB04(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((E_80170A58_S_80170A58_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                (*(u16 *)((u8 *)entity + 0x98)) &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((E_80170A58_S_80170A58_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((E_80170A58_S_80170A58_1 *)actor)->unk_1C & 0x40000000) {
                ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04((((E_80170A58_S_80170A58_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((E_80170A58_S_80170A58_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - floor_height;
                ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 0x40;

}
