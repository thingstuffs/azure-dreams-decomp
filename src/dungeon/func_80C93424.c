#include "modules/dungeon_ovl_cb3000.h"

void dungeonSetBossEffectFlag(void *entity, CB_80170C24_S_80170C24_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s32 direction_value;
    s16 old_direction;
    CB_80170C24_Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (dungeonStatus.flags & 0x2000) {
        CB_80170C24_Callback early_callback;

        early_callback = (*(CB_80170C24_Callback *)((u8 *)entity + 0x8C));
        if (early_callback == func_8017102C) {
            early_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }


    old_direction = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (dungeonRefreshActorFacingAndLifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    callback = (*(CB_80170C24_Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    D_8017533C[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)old_direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, monster, entity);
    }

    monster_flags = ((CB_80170C24_S_80170C24_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        direction_value = gameWork.view.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((CB_80170C24_S_80170C24_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                selectIndirectTableEntry(monster, tile_map[direction_index], ((CB_80170C24_S_80170C24_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dirSpriteFlag[direction_copy] != 0) {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 1;
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((CB_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x20)) {
            if (!(((CB_80170C24_S_80170C24_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x7000;
        }

        dungeonApplyMonsterKoyawData(((CB_80170C24_S_80170C24_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags | 0x7000;
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
        floor_height = func_800BCB04(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((CB_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x40000000) {
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = func_800BCB04((((CB_80170C24_S_80170C24_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((CB_80170C24_S_80170C24_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - floor_height;
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x40;

}

