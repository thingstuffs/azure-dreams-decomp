#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
extern int abs(int);
#ifndef NULL
#define NULL 0
#endif

/* ---- globals (declared array-style so every access stays %hi/%lo, never $gp) ---- */
typedef struct CFlags46 { u8 pad_00[0x46]; u16 f46; } CFlags46;
extern u8 D_800E3548[];

/* ---- ordinary callees ---- */
extern s32 func_80042900();
extern s32 func_80098B38();
extern s32 func_8009A350();
extern u8 *func_8009B25C();
extern s32 func_8009CD58();
extern s32 func_8009FD40();
extern s32 func_800A0134();
extern u8 *func_800A02AC();
extern u8 *func_800A03C4();
extern u8 *func_800A05A4();
extern s32 func_800A0818();
extern s32 func_800A0E6C();
extern s32 func_800A19E4();
extern s32 func_800A2C34();
extern s32 func_800A2CAC();
extern s32 func_800A2CB8();
extern s32 func_800A3518();
extern s32 func_800A3544();
extern s32 func_800A35A4();
extern s32 func_800A365C();
extern s32 func_800A36B4();
extern s32 func_800A384C();
extern u8 *func_800A3D18();
extern s32 func_800A404C();
extern u16 func_800A40AC();
extern s32 func_800A41F0();
extern s32 func_800A45D8();
extern s32 func_800A6E8C();
extern s32 func_800A70E4();
extern s32 func_800A9A0C();
extern s32 func_800AA53C();
extern s32 func_800ADD20();
extern s32 func_800BCB04();
extern s32 func_800C7F68();

#define STEPVEC(neighbor_result)                                                            \
    {                                                                                    \
        u16 facing = (*(u16 *)(creature + 0x2A) >> 9) & 7;                                  \
        direction = facing;                                                                 \
        neighbor_result = func_8009B25C(creature,                                           \
            (u16)(position[0x24] + *(u16 *)((facing * 2) + (u8 *)dirStepX)),              \
            (u16)(position[0x25] + *(u16 *)((facing * 2) + (u8 *)dirStepY)),              \
            *(s16 *)(creature + 0x88));                                                     \
    }

/* Selects a creature's next action and target from its behavior, species, and nearby tiles. */
s32 func_800ADE74(s32 unused, u8 *position, u8 *creature, s32 lower_limit, u16 upper_limit, s32 status_out_addr)
{
    register s32 neighbor_check;
    s32 saved_lower_limit;
    s32 case_code0 = 0;
    s32 case_code1 = 0;
    s16 tile_x;
    s16 tile_y;
    s16 slot_or_distance;
    u16 direction;
    s16 action_or_flags;
    u16 default_action;
    s32 action_result;
    s32 step_limit;
    s32 pending_action;
    s32 idle_player_dist;
    s32 idle_ally_dist;
    s32 follow_player_dist;
    s32 follow_ally_dist;
    s32 assist_player_dist;
    s32 assist_ally_dist;
    s32 ranged_distance;
    s32 distance;
    s32 distance_scaled;
    u32 delta_or_result;
    s32 idle_player_range;
    s32 idle_ally_range;
    s32 follow_player_range;
    s32 follow_ally_range;
    s32 assist_player_range;
    s32 assist_ally_range;
    s32 scan_index;
    s32 ally_index;
    s32 ally_offset;
    s32 behavior;
    u8 behavior_byte;
    TileObject *idle_player_pos;
    TileObject *follow_player_pos;
    TileObject *assist_player_pos;
    TileObject *near_player_pos;
    TileObject *ranged_player_pos;
    TileObject *flee_player_pos;
    u8 *neighbor;
    u8 *target;
    u8 *target_pos;
    u8 *ally_slot_base;
    u16 slot_index;
    u8 *move_target;
    u8 *ally;

    default_action = 2;
    saved_lower_limit = lower_limit;
    ((CFlags46 *)creature)->f46 |= 0x4000;
    if (D_80013714 & 8) {
        func_800A9A0C(creature);
        return -1;
    }
    if (creature[0x25] == 0) {
        default_action = 0;
        goto return_default;
    }
    if ((func_800A2CAC(creature) << 16) != 0) {
        if ((func_800A6E8C(position, 0x60C, &tile_x, &tile_y) << 16) != 0) {
            if (creature[0x13] != 0x22) {
                if ((func_800A2C34(creature) << 16) != 0) {
                    return -1;
                }
                if (tile_x == position[0x24] && tile_y == position[0x25]) {
                    s16 entry_index = func_800A70E4(tile_x, tile_y, *(s16 *)(creature + 0x88));
                    if (entry_index >= 0) {
                        s32 hp = *(u16 *)(creature + 0x24);
                        if (0x10000 < (s32)hp) {
                            hp = 0xFFFF;
                        }
                        *(u16 *)(creature + 0x24) = hp;
                        if (creature[0x25] != 0) {
                            *(s32 *)(creature + 0x1C) &= ~8;
                        }
                        {
                            u8 max_hp = creature[0x66];
                            if (max_hp < creature[0x25]) {
                                creature[0x25] = max_hp;
                                creature[0x24] = 0xFF;
                            }
                        }
                        func_80098B38((entry_index * 4) + (u8 *)D_800E3548);
                    }
                    return 0;
                }
                *(u16 *)(creature + 0x2A) = func_800A0818(
                    position[0x24], position[0x25],
                    tile_x, tile_y, &slot_or_distance);
                *(u16 *)(creature + 0x46) = 0x800B;
                return 2;
            }
        }
    }

    func_800A19E4(position, creature, (s16)saved_lower_limit, (s16)upper_limit, status_out_addr);
    if ((*(s32 *)(creature + 0x1C) & 0x2410) == 0x2000) {
        {
            EntityRec *player = D_800E3D7C;
            behavior_byte = creature[0x12];
            if ((player->flags1C & 0x220) || (func_80042900(player, 0xA) << 16) != 0) {
                if (*(s32 *)(creature + 0x1C) & 0x20000) {
                    if (behavior_byte != 0) {
                        behavior_byte = 1;
                    }
                }
            }
            behavior = behavior_byte;
        }
        switch (behavior) {
        case 0:
            if ((func_800A2C34(creature) << 16) != 0) {
                return -1;
            }
            if ((func_80042900(creature, 6) << 16) == 0) {
                s32 found_slot = func_800A3544(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (*(s32 *)(creature + 0x1C) & 0x20000) {
                        idle_player_pos = &D_80082E80;
                        idle_player_dist = func_8009FD40(position, idle_player_pos);
                        idle_player_range = func_800A35A4(creature, slot_or_distance);
                        if ((idle_player_dist << 16) < (idle_player_range << 16)) {
                            if ((func_800A3518(((u8 *)D_800E3D7C)) << 16) != 0) {
                                s32 result;
                                register EntityRec *player_target;
                                *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                *(u16 *)(creature + 0x2A) = func_800A0818(
                                    position[0x24], position[0x25],
                                    idle_player_pos->tileX, idle_player_pos->tileY, &slot_or_distance);
                                player_target = D_800814A8;
                                result = 4;
                                *(void **)(creature + 0x60) = player_target;
                                return result;
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = dungeonStatus.unk_1E & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            idle_ally_dist = func_8009FD40(position, target_pos);
                            idle_ally_range = func_800A35A4(creature, slot_or_distance);
                            distance_scaled = idle_ally_dist << 16;
                            distance = (s32)distance_scaled < (idle_ally_range << 16);
                            if (distance) {
                                if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8) + 0xAC)) << 16) != 0) {
                                    {
                                        {
                                            s32 player_base, slot_action;
                                            slot_index = *(u16 *)&slot_or_distance;
                                            player_base = (s32)D_800814A8;
                                            slot_action = slot_index + 1;
                                            slot_action |= 0x8000;
                                            ally_slot_base = (u8 *)(ally_offset + player_base);
                                            *(u16 *)(creature + 0x46) = slot_action;
                                        }
                                        if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                            *(u16 *)(creature + 0x2A) = func_800A0818(
                                                position[0x24], position[0x25],
                                                target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                        }
                                        *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                                        return 4;
                                    }
                                }
                            }
                        }
                        scan_index++;
                        ally_index ^= 1;
                    } while (scan_index < 2);
                }
            }

            move_target = func_800A3D18(position, creature, 4);
            *(void **)(creature + 0x60) = move_target;
            if (move_target == NULL) {
                break;
            }
            {
                s32 action_code;
                s32 result;
                action_code = func_800A384C(creature, move_target, &direction, 0);
                action_or_flags = action_code;
                *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
                case_code0 = action_code;
                if ((case_code0 << 16) < 0) {
                    *(u16 *)(creature + 0x46) = 0x800B;
                    return 2;
                }
                pending_action = case_code0 | 0x8000;
                *(u16 *)(creature + 0x46) = pending_action;
                return 1;
            }

        case 1:
            if ((func_800A2C34(creature) << 16) != 0) {
                return -1;
            }
            if ((func_80042900(creature, 6) << 16) == 0) {
                s32 found_slot = func_800A3544(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (*(s32 *)(creature + 0x1C) & 0x20000) {
                        follow_player_pos = &D_80082E80;
                        follow_player_dist = func_8009FD40(position, follow_player_pos);
                        follow_player_range = func_800A35A4(creature, slot_or_distance);
                        if ((follow_player_dist << 16) < (follow_player_range << 16)) {
                            if ((func_800A3518(D_800814A8) << 16) != 0) {
                                EntityRec *player_target;
                                register s32 target_direction;
                                *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                target_direction = func_800A0818(
                                    position[0x24], position[0x25],
                                    follow_player_pos->tileX, follow_player_pos->tileY, &slot_or_distance);
                                player_target = D_800814A8;
                                *(u16 *)(creature + 0x2A) = target_direction;
                                *(void **)(creature + 0x60) = player_target;
                                return 4;
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = dungeonStatus.unk_1E & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            follow_ally_dist = func_8009FD40(position, target_pos);
                            follow_ally_range = func_800A35A4(creature, slot_or_distance);
                            if ((follow_ally_dist << 16) < (follow_ally_range << 16)) {
                                if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8) + 0xAC)) << 16) != 0) {
                                    {
                                        {
                                            s32 player_base, slot_action;
                                            slot_index = *(u16 *)&slot_or_distance;
                                            player_base = (s32)D_800814A8;
                                            slot_action = slot_index + 1;
                                            slot_action |= 0x8000;
                                            ally_slot_base = (u8 *)(ally_offset + player_base);
                                            *(u16 *)(creature + 0x46) = slot_action;
                                        }
                                        if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                            *(u16 *)(creature + 0x2A) = func_800A0818(
                                                position[0x24], position[0x25],
                                                target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                        }
                                        *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                                        return 4;
                                    }
                                }
                            }
                        }
                        scan_index++;
                        ally_index ^= 1;
                    } while (scan_index < 2);
                }
            }

            move_target = func_800A3D18(position, creature, -3);
            *(void **)(creature + 0x60) = move_target;
            if (move_target == NULL) {
                break;
            }
            {
                s32 action_code;
                s32 result;
                action_code = func_800A384C(creature, move_target, &direction, 0);
                action_or_flags = action_code;
                *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
                case_code1 = action_code;
                if ((s16)case_code1 < 4) {
                    *(u16 *)(creature + 0x46) = 0x800B;
                    return 2;
                }
                pending_action = case_code1 | 0x8000;
                *(u16 *)(creature + 0x46) = pending_action;
                return 1;
            }

        case 2:
            if ((func_80042900(creature, 6) << 16) == 0) {
                s32 found_slot = func_800A3544(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (*(s32 *)(creature + 0x1C) & 0x20000) {
                        assist_player_pos = &D_80082E80;
                        assist_player_dist = func_8009FD40(position, assist_player_pos);
                        assist_player_range = func_800A35A4(creature, slot_or_distance);
                        if ((assist_player_dist << 16) < (assist_player_range << 16)) {
                            if ((func_800A3518(D_800814A8) << 16) != 0) {
                                if ((func_800A2C34(creature) << 16) != 0) {
                                    return -1;
                                }
                                {
                                    EntityRec *player_target;
                                    register s32 target_direction;
                                    *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                    target_direction = func_800A0818(
                                        position[0x24], position[0x25],
                                        assist_player_pos->tileX, assist_player_pos->tileY, &slot_or_distance);
                                    player_target = D_800814A8;
                                    *(u16 *)(creature + 0x2A) = target_direction;
                                    *(void **)(creature + 0x60) = player_target;
                                    return 4;
                                }
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = dungeonStatus.unk_1E & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            assist_ally_dist = func_8009FD40(position, target_pos);
                            assist_ally_range = func_800A35A4(creature, slot_or_distance);
                            if ((assist_ally_dist << 16) < (assist_ally_range << 16)) {
                                if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8) + 0xAC)) << 16) != 0) {
                                    if ((func_800A2C34(creature) << 16) != 0) {
                                        return -1;
                                    }
                                    {
                                        s32 player_base, slot_action;
                                        slot_index = *(u16 *)&slot_or_distance;
                                        player_base = (s32)D_800814A8;
                                        slot_action = slot_index + 1;
                                        slot_action |= 0x8000;
                                        ally_slot_base = (u8 *)(ally_offset + player_base);
                                        *(u16 *)(creature + 0x46) = slot_action;
                                    }
                                    if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                        *(u16 *)(creature + 0x2A) = func_800A0818(
                                            position[0x24], position[0x25],
                                            target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                    }
                                    *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8) + 0xAC);
                                    return 4;
                                }
                            }
                        }
                        scan_index++;
                        ally_index ^= 1;
                    } while (scan_index < 2);
                }
                if (*(s32 *)(creature + 0x1C) & 0x20000) {
                    if ((func_800A404C() << 16) == 0) {
                        EntityRec *player = D_800814A8;
                        if (player->unk_9A == 0x11) {
                            EntityRec *player_target = player->target;
                            if (player_target != NULL) {
                                if (!(player_target->flags14 & 0x2000)) {
                                    {
                                        s32 action_code;
                                        u16 checked_action;
                                        action_or_flags = func_800A40AC(creature, (u16)func_8009CD58(player_target, 7, 0));
                                        checked_action = action_or_flags;
                                        if ((checked_action << 16) >= 0) {
                                            action_code = checked_action | 0x8000;
                                            *(u16 *)(creature + 0x46) = action_code;
                                            *(u16 *)(creature + 0x2A) = func_800A0818(
                                                position[0x24], position[0x25],
                                                D_80082E80.tileX, D_80082E80.tileY, &action_or_flags);
                                            return 3;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((func_800A2C34(creature) << 16) == 0) {
                break;
            }
            return -1;

        case 4:
            if ((func_800A2C34(creature) << 16) != 0) {
                return -1;
            }
            move_target = func_800A03C4(creature, position[0x24], position[0x25]);
            default_action = 0;
            *(void **)(creature + 0x60) = move_target;
            if (move_target != NULL) {
                {
                    s32 action_code;
                    u16 move_direction;
                    action_code = func_800A384C(creature, move_target, &direction, 0);
                    action_or_flags = action_code;
                    if ((action_code << 16) < 0) {
                        break;
                    }
                    move_direction = direction;
                    *(u16 *)(creature + 0x46) = action_code | 0x8000;
                    *(u16 *)(creature + 0x2A) = move_direction;
                    return 1;
                }
            }
        }
        if ((func_800A2C34(creature) << 16) == 0) {
            delta_or_result = default_action << 16;
            return (u32)delta_or_result >> 16;
        }
        return -1;
    }
    if ((func_800A2C34(creature) << 16) != 0) {
        return -1;
    }
    if (*(s32 *)(creature + 0x1C) & 0x10) {
        delta_or_result = default_action << 16;
        return (u32)delta_or_result >> 16;
    }
    {
        s8 room_index = *(s8 *)(position + 0x26);
        if (room_index >= 0) {
            if (D_800E2970[room_index].flags & 2) {
                delta_or_result = default_action << 16;
                return (u32)delta_or_result >> 16;
            }
        }
    }

    if ((func_80042900(creature, 6) << 16) == 0) {
        s32 found_slot = func_800A3544(creature, 0x1E);
        slot_or_distance = found_slot;
        if ((found_slot << 16) >= 0) {
            if ((func_800A3518(creature) << 16) != 0) {
                slot_index = *(u16 *)&slot_or_distance;
                *(void **)(creature + 0x60) = creature;
                *(u16 *)(creature + 0x46) = (slot_index + 1) | 0x8000;
                return 4;
            }
        }
    }

    switch (creature[0x13]) {

    case 25:
    func_800ADD20(creature, 0x10);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    if (neighbor[0x13] != 0) {
        break;
    }
    if ((func_800A3518(creature) << 16) == 0) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x800A;
    return 6;

    case 22:
    if (creature[0x48] != 0xF) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    near_player_pos = &D_80082E80;
    if ((s16)func_8009FD40(near_player_pos, position) >= 0xB) {
        break;
    }
    if (func_800A365C(position, near_player_pos) == 0) {
        break;
    }
    if (func_800A36B4(creature, ((u8 *)D_800E3D7C)) == 0) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8008;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        near_player_pos->tileX, near_player_pos->tileY, &action_or_flags);
    return 1;

    case 44:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    ranged_player_pos = &D_80082E80;
    ranged_distance = func_8009FD40(ranged_player_pos, position);
    if ((u32)((ranged_distance - 2) & 0xFFFF) >= 7) {
        break;
    }
    if (func_800A365C(position, ranged_player_pos) == 0) {
        break;
    }
    {
        s32 height_delta = (s16)func_800A0134(creature, ((u8 *)D_800E3D7C));
        height_delta = abs(height_delta);
        if (height_delta >= 0x21) {
            break;
        }
    }
    target = func_800A05A4(creature, position[0x24], position[0x25], *(s16 *)(creature + 0x2A), (s16)ranged_distance);
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        break;
    }
    if (func_800A36B4(creature, target) == 0) {
        break;
    }
    if (creature[0xAE] != 0) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        ranged_player_pos->tileX, ranged_player_pos->tileY, &action_or_flags);
    return 5;

    case 43:
    func_800ADD20(creature, 0x20);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        if (!(ability_flags & 0x100)) {
            break;
        }
        if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
            break;
        }
        if (ability_flags & 0x8000) {
            break;
        }
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80.tileX, D_80082E80.tileY, &action_or_flags);
    return 5;

    case 34:
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    if ((s8)position[0x26] < 0) {
        break;
    }
    scan_index = 0;
    do {
        ally = *(void **)(((u8 *)((u8 *)D_800E3D7C) + scan_index * 4) + 0xAC);
        if (ally != NULL) {
            if ((func_800A2CAC(ally) << 16) != 0) {
                *(u16 *)(creature + 0x46) = 0x8009;
                *(u16 *)(creature + 0x2A) = func_800A0818(
                    position[0x24], position[0x25],
                    D_80082E80.tileX, D_80082E80.tileY, &action_or_flags);
                return 5;
            }
        }
        scan_index++;
    } while (scan_index < 2);
    break;

    case 41:
    func_800ADD20(creature, 0x10);
    scan_index = 0;
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    do {
        target = *(u8 **)(((u8 *)((u8 *)D_800E3D7C) + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)func_800A0134(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((func_800A41F0(target) << 16) != 0) {
                    target_pos = *(void **)(target - 0x14);
                    if ((s16)func_8009FD40(target_pos, position) == 1) {
                        if (func_800C7F68(target) == 0) {
                            *(u16 *)(creature + 0x46) = 0x8009;
                            *(void **)(creature + 0xA8) = target;
                            *(u16 *)(creature + 0x2A) = func_800A0818(
                                position[0x24], position[0x25],
                                target_pos[0x24], target_pos[0x25], &action_or_flags);
                            return 5;
                        }
                    }
                }
            }
        }
        scan_index++;
    } while (scan_index < 2);
    break;

    case 40:
    func_800ADD20(creature, 0x40);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        if (ability_flags & 0x100) {
            *(u16 *)(creature + 0x98) = ability_flags | 0x8000;
            break;
        }
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        break;
    }

    case 26:
    func_800ADD20(creature, 2);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            break;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        break;
    }
    if ((func_80042900(target, 1) << 16) != 0) {
        break;
    }
    *(u16 *)(creature + 0x98) |= 0x8000;
    break;

    case 35:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    if (*(s16 *)(creature + 0xA6) != 0) {
        break;
    }
    if (D_800E296C & 4) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

    case 38:
    func_800ADD20(creature, 2);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    neighbor_check = func_800A2CB8(creature, target) << 16;
    if (neighbor_check == 0) {
        break;
    }
    if ((func_80042900(target, 4) << 16) != 0) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

    case 39:
    func_800ADD20(creature, 0x10);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            break;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        break;
    }
    if ((func_80042900(target, 2) << 16) != 0) {
        break;
    }
    {
        *(u16 *)(creature + 0x46) = 0x8009;
        *(u16 *)(creature + 0x98) |= 0x8000;
        return 5;
    }

    case 32:
    if (creature[0x49] == 0) {
        func_800ADD20(creature, 2);
        if (!(*(u16 *)(creature + 0x98) & 0x100)) {
            break;
        }
        STEPVEC(neighbor);
        if (neighbor != ((u8 *)D_800E3D7C)) {
            break;
        }
        *(u16 *)(creature + 0x46) = 0x8009;
        return 5;
    }
    if (*(s32 *)(creature + 0x1C) & 0x410) {
        break;
    }
    func_800AA53C(creature);
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        return 2;
    }
    if ((s8)position[0x26] >= 0) {
        func_800A0E6C(position, *(s8 *)(creature + 0x9C), creature, creature + 0x98);
    } else {
        flee_player_pos = &D_80082E80;
        if ((s16)func_8009FD40(position, flee_player_pos) == 1) {
            *(u16 *)(creature + 0x2A) = func_800A0818(
                position[0x24], position[0x25],
                flee_player_pos->tileX, flee_player_pos->tileY, creature + 0x98) + 0x800;
        }
    }
    *(u16 *)(creature + 0x46) = 0x800B;
    return 2;

    case 36:
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
    }
    if (creature[0x49] != 0) {
        break;
    }
    if ((func_800A6E8C(position, 0x12, &tile_x, &tile_y) << 16) == 0) {
        break;
    }
    action_result = func_800A0818(position[0x24], position[0x25], tile_x, tile_y, creature + 0x98);
    {
        s32 target_x = *(u16 *)&tile_x;
        s32 target_y = *(u16 *)&tile_y;
        s32 ability_flags = *(u16 *)(creature + 0x98);
        s32 x_delta, y_distance, shifted_x_delta, y_delta;
        *(u16 *)(creature + 0x2A) = action_result;
        ability_flags |= 0x8000;
        *(u16 *)(creature + 0xA8) = target_x;
        target_x <<= 16;
        target_x >>= 16;
        *(u16 *)(creature + 0xAA) = target_y;
        target_y <<= 16;
        target_y >>= 16;
        *(u16 *)(creature + 0x98) = ability_flags;
        x_delta = position[0x24];
        x_delta -= target_x;
        x_delta = abs(x_delta);
        tile_x = x_delta;
        distance = x_delta;
        ASM_KEEP_NV(distance);
        shifted_x_delta = x_delta << 16;
        y_delta = position[0x25] - target_y;
        y_distance = y_delta;
        y_distance = abs(y_distance);
        tile_y = y_distance;
        x_delta = shifted_x_delta < (y_distance << 16);
        if (x_delta) {
            distance = y_distance;
        }
        if ((s16)distance == 1) {
            goto return_ability;
        }
        *(u16 *)(creature + 0x46) = 0x800B;
        return 2;
    }

    case 37:
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

    case 24:
    if ((s16)func_8009FD40(position, ((u8 *)(&D_80082E80))) >= 2) {
        if (creature[0xB5] == 0) {
            func_800ADD20(creature, 8);
            if (*(u16 *)(creature + 0x98) & 0x100) {
                *(u16 *)(creature + 0x46) = 0x800A;
                return 6;
            }
        }
    }
    if (creature[0xB5] == 0) {
        break;
    }
    neighbor = func_8009B25C(creature, position[0x24], position[0x25], *(s16 *)(creature + 0x88));
    if (neighbor == NULL) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        *(u16 *)(creature + 0x46) = 0x800B;
        return 2;
    }
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80.tileX, D_80082E80.tileY, creature + 0x98);
    goto return_wait;

    case 42:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    {
        TileObject *player_pos = &D_80082E80;
        u16 height;
        if (func_800A365C(position, player_pos) == 0) {
            break;
        }
        distance = func_8009FD40(player_pos, position);
        if ((u32)((distance - 2) & 0xFFFF) >= 7) {
            break;
        }
        height = *(u16 *)(creature + 0x88);
        scan_index = 0;
        direction = ((u32)func_800A0818(position[0x24], position[0x25], player_pos->tileX, player_pos->tileY, &action_or_flags) >> 9) & 7;
        tile_x = position[0x24];
        tile_y = position[0x25];
        if ((distance << 16) > 0) {
            u16 *x_steps = dirStepX;
            u16 *y_steps = dirStepY;
            do {
                s32 next_x, next_y;
                s32 step_direction = *(s16 *)&direction;
                s32 x_step = x_steps[step_direction];
                s32 y_step = y_steps[step_direction];
                next_x = *(u16 *)&tile_x + x_step;
                next_y = *(u16 *)&tile_y + y_step;
                tile_x = next_x;
                tile_y = next_y;
                if ((func_800A45D8((next_x << 6) & 0xFFC0, (next_y << 6) & 0xFFC0, (s16)(height + 0x20), next_x) << 16) != 0) {
                    step_limit = (s16)distance;
                    break;
                }
                {
                    s16 next_height = func_800BCB04(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_y << 6) + 0x20) & 0xFFE0, (s16)(height - 0x20));
                    if (next_height < (s16)height) {
                        break;
                    }
                    if (next_height - (s16)height >= 0x21) {
                        break;
                    }
                    scan_index++;
                    height = next_height;
                }
                step_limit = (s16)distance;
            } while (scan_index < step_limit);
        }
        if (scan_index != (s16)distance) {
            break;
        }
        {
            s32 result;
            s32 action_word;
            s32 facing;
            result = 5;
            facing = direction;
            action_word = 0x8009;
            *(u16 *)(creature + 0x46) = action_word;
            *(u16 *)(creature + 0x2A) = facing << 9;
            return result;
        }
    }

    case 27:
    func_800ADD20(creature, 4);
    scan_index = 0;
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    do {
        target = *(u8 **)(((u8 *)((u8 *)D_800E3D7C) + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)func_800A0134(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((func_800A41F0(target) << 16) != 0) {
                    if ((func_80042900(target, 0xC) << 16) == 0) {
                        target_pos = *(void **)(target - 0x14);
                        if ((s16)func_8009FD40(target_pos, position) == 1) {
                            *(u16 *)(creature + 0x46) = 0x8009;
                            *(u16 *)(creature + 0x2A) = func_800A0818( position[0x24], position[0x25], target_pos[0x24], target_pos[0x25], &action_or_flags);
                            return 5;
                        }
                    }
                }
            }
        }
        scan_index++;
    } while (scan_index < 2);
    break;

    case 9:
    case 10:
    target = func_800A02AC(creature, position[0x24], position[0x25]);
    if (target == NULL) {
        break;
    }
    if ((u32)(target[0x13] - 0x33) >= 4) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    target_pos = *(void **)(target - 0x14);
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        target_pos[0x24], target_pos[0x25], &action_or_flags);
    return 5;

    case 23:
    func_800ADD20(creature, 0x10);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if (!(*(s32 *)(target + 0x14) & 0x4000)) {
        break;
    }
    if (target == ((u8 *)D_800E3D7C)) {
        break;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

    case 28:
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        break;
    }
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    {
        s16 *tile_flags_out = &action_or_flags;
        TileObject *player_pos = &D_80082E80;
        u16 player_direction;
        player_direction = ((u32)func_800A0818(position[0x24], position[0x25], player_pos->tileX, player_pos->tileY, tile_flags_out) >> 9) & 7;
        direction = player_direction;
        if ((func_8009A350(position[0x24], position[0x25], player_direction, tile_flags_out) << 16) == 0) {
            break;
        }
        if (action_or_flags & 0xB712) {
            break;
        }
        if ((s16)func_8009FD40(player_pos, position) != 2) {
            break;
        }
    }
    {
        s32 result;
        s32 action_word;
        s32 facing;
        result = 5;
        facing = direction;
        action_word = 0x8009;
        *(u16 *)(creature + 0x46) = action_word;
        *(u16 *)(creature + 0x2A) = facing << 9;
        return result;
    }

    case 29:
    func_800ADD20(creature, 8);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if (!(*(s32 *)(target + 0x14) & 0x4000)) {
        break;
    }
    {
        neighbor_check = target[0x13];
        if (neighbor_check == 0) {
            break;
        }
        if ((func_80042900(target, 4) << 16) != 0) {
            break;
        }
        *(u16 *)(creature + 0x46) = 0x8009;
        return 5;
    }

    case 21:
    if (creature[0xA7] != 0) {
        if (creature[0xA8] == 0) {
            STEPVEC(neighbor);
            target = neighbor;
            if (target != NULL) {
                if (target == ((u8 *)D_800E3D7C)) {
                    *(u16 *)(creature + 0x46) = 0x8009;
                    *(u16 *)(creature + 0x2A) = func_800A0818(
                        position[0x24], position[0x25],
                        D_80082E80.tileX, D_80082E80.tileY, &action_or_flags);
                    return 5;
                }
            }
        }
    }
    default:
        break;
    }
    move_target = func_800A3D18(position, creature, 2);
    *(void **)(creature + 0x60) = move_target;
    if (move_target != NULL) {
        action_result = func_800A384C(creature, move_target, &direction, 1);
        action_or_flags = action_result;
        *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
        if ((action_result << 16) < 0) {
            *(u16 *)(creature + 0x46) = 0x800B;
            return 2;
        }
        pending_action = action_result | 0x8000;
        *(u16 *)(creature + 0x46) = pending_action;
        return 1;
    }
    goto check_forward_target;

return_wait:
    *(u16 *)(creature + 0x46) = 0x800B;
    return 2;

check_forward_target:
    {
        u8 kind = creature[0x13];
        if (kind != 0x1E) {
            goto check_room;
        }
        if (*(s32 *)(creature + 0x14) & 0x20000000) {
            goto check_room;
        }
        {
            u16 facing = (*(u16 *)(creature + 0x2A) >> 9) & 7;
            direction = facing;
            tile_x = position[0x24] + *(u16 *)((facing * 2) + (u8 *)dirStepX);
            tile_y = position[0x25] + *(u16 *)((facing * 2) + (u8 *)dirStepY);
        }
        target = NULL;
        if (creature[0xAC] == 0) {
            target = func_8009B25C(creature, *(u16 *)&tile_x, *(u16 *)&tile_y, *(s16 *)(creature + 0x88));
            if (target != NULL) {
                u8 target_kind = target[0x13];
                if ((u32)(target_kind - 1) >= 0x2D || target_kind == kind) {
                    target = NULL;
                }
            }
        }
        if (creature[0xAC] < 2) {
            if (target == NULL) {
                target = (u8 *)((s16)func_800A70E4(tile_x, tile_y, *(s16 *)(creature + 0x88)) + 1);
            } else {
                *(u16 *)(creature + 0x46) = 0x8009;
                return 5;
            }
        }
        if (target == NULL) {
            goto check_room;
        }
    }
return_ability:
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

check_room:
    if ((s8)position[0x26] >= 0) {
        return 2;
    }
return_default:
    delta_or_result = default_action << 16;
    return (u32)delta_or_result >> 16;
}
