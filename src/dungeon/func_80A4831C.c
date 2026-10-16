#include "modules/dungeon_resource06_slot0.h"

void func_80171B1C(void *move_data, void *context, void *position_data, void *actor_data)
{
    u16 dungeon_flags = dungeonStatus.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;

    if ((dungeon_flags & 0x4000) || ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)func_80172264(move_data, context, position_data, actor_data) == 0) {
            func_800A9A0C(actor_data);
            return;
        }
        if (dungeonStatus.unk_0C == actor_data) {
            ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    func_800A19E4(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)func_800A02AC(actor_data,(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v));
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)func_800A0818((s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R06_80171B1C_S_80171C34_7 *)(((R06_80171B1C_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R06_80171B1C_S_80171C34_7 *)(((R06_80171B1C_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (func_800A6D30() & 7) << 9;
            }
        } else {
            if (func_800A04F0(actor_data,(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &D_80082E80;
                    s32 target_facing = ((u16)D_800814A8->facing);
                    s32 offset_index =
                        ((((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tileX +
                        *(u16 *)((u8 *)((s8 *)dirStepX) + offset_index);
                    target_y = target_position->tileY +
                        *(u16 *)((u8 *)((s8 *)dirStepY) + offset_index);
                }

                if (((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v == (u16)target_x &&
                    ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v == (u16)target_y) {
                    ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)func_800A0818((s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)func_8009A8C0((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)func_800A0818((s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY), turn_data));
                }
                if (((s16)func_8009FD7C(
                        ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY)) != 0) {
                    limit_detour = 1;
                }
            } else {
                func_800A0E6C(position_data, ((R06_80171B1C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (((R06_80171B1C_S_80171C34_2 *)position_data)->unk_26.s >= 0 &&
               ((R06_80171B1C_DungeonRecord *)D_800E2970)[((R06_80171B1C_S_80171C34_2 *)position_data)->unk_26.s].flags & 2) {
        func_800A0E6C(position_data, ((R06_80171B1C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)func_800A04F0(actor_data,(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(u8)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R06_80171B1C_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)func_800A0134((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)func_8009A540(
                    ((s16)((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &D_80082E80;
            ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)func_800A0818((s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)(target_position->tileX),(s16)(target_position->tileY), (u8 *)move_data + 0x98));
            if (((s16)func_8009FD7C(
                    ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v,
                    target_position->tileX, target_position->tileY)) != 0) {
                if (((s16)func_800A0134(D_800814A8, actor_data)) < 0x81) {
                    if (((s16)func_8009A540(
                            ((s16)((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(s16)((s16)(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            func_800A0E6C(position_data, ((R06_80171B1C_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)D_8006CD00);

    do {
        turn_flags = ((R06_80171B1C_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)func_8009A8C0((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R06_80171B1C_S_80171C34_8 *)((u8 *)actor_data + (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v;
            ((R06_80171B1C_S_80171C34_8 *)((u8 *)actor_data + (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v;
            ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u++;

            func_8009A3D0(
                ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v, ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v,
                (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dirStepX);
                step_offset = (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v += *x_step;
                ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v += *((u8 *)((s8 *)dirStepY) + step_offset);
            }

            func_8009A21C((s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v),(s16)(((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v),(u16)((((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&D_80082E80.tileX) != ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00u.v) {
            if (((s16)func_8009A180(actor_data,
                    (u8 *)D_800814A8->unk_58 + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        func_800A9A0C(actor_data);
        return;
    }

    {
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R06_80171B1C_S_80171C34_5 *)move_data)->unk_9C.u = ((R06_80171B1C_S_80171C34_2 *)position_data)->unk_26.u;
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_6D.u--;
        dungeonStatus.unk_08++;
    }
    if (((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)func_800BCB04(
        (((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at00.v << 6) | 0x20,
        (((R06_80171B1C_S_80171C34_2 *)position_data)->unk_24.at01.v << 6) | 0x20,(s16)((s16)(((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R06_80171B1C_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}
