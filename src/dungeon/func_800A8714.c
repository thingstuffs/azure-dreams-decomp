#include "common.h"
extern int abs(int);
#ifndef NULL
#define NULL 0
#endif

/* ---- globals (declared array-style so every access stays %hi/%lo, never $gp) ---- */
extern u16 D_80013714[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80082E80[];
extern u16 D_8008347E[];
extern void *D_800814A8[];
extern s32 D_800E296C[];
typedef struct D_800E2970Entry {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} D_800E2970Entry;
extern D_800E2970Entry D_800E2970[];
typedef struct CFlags46 { u8 pad_00[0x46]; u16 f46; } CFlags46;
extern u8 D_800E3548[];
extern u8 *D_800E3D7C[];
extern void *D_80089088[];

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
extern s32 func_800A40AC();
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
    do {                                                                                    \
        u16 facing = (*(u16 *)(creature + 0x2A) >> 9) & 7;                                  \
        direction = facing;                                                                 \
        neighbor_result = func_8009B25C(creature,                                           \
            (u16)(position[0x24] + *(u16 *)((facing * 2) + (u8 *)D_8006CCD8)),              \
            (u16)(position[0x25] + *(u16 *)((facing * 2) + (u8 *)D_8006CCE8)),              \
            *(s16 *)(creature + 0x88));                                                     \
    } while (0)

/* Selects a creature's next action and target from its behavior, species, and nearby tiles. */
s32 func_800ADE74(s32 unused, u8 *position_arg, u8 *creature_arg, s32 lower_limit, u16 upper_limit, volatile s32 status_out_addr)
{
    register u8 *position ASM_REG("$23");
    register u8 *creature ASM_REG("$21");
    register s32 neighbor_check;
    s32 saved_lower_limit;
    s16 tile_x;
    s16 tile_y;
    s16 slot_or_distance;
    u16 direction;
    s16 action_or_flags;
    s32 default_action;
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
    s32 delta_or_result;
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
    u8 *idle_player_pos;
    u8 *follow_player_pos;
    u8 *assist_player_pos;
    u8 *near_player_pos;
    u8 *ranged_player_pos;
    u8 *flee_player_pos;
    u8 *neighbor;
    u8 *target;
    u8 *target_pos;
    u8 *ally_slot_base;
    u16 slot_index;
    u8 *move_target;
    u8 *ally;

    position = position_arg;
    ASM_USE_NV(position);
    creature = creature_arg;
    default_action = 2;
    saved_lower_limit = lower_limit;
    ((CFlags46 *)creature)->f46 |= 0x4000;
    if (D_80013714[0] & 8) {
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
    if ((*(s32 *)(creature + 0x1C) & 0x2410) != 0x2000) {
        goto check_species_action;
    }
    {
        u8 *player = D_800E3D7C[0];
        behavior_byte = creature[0x12];
        if ((*(s32 *)(player + 0x1C) & 0x220) || (func_80042900(player, 0xA) << 16) != 0) {
            if (*(s32 *)(creature + 0x1C) & 0x20000) {
                if (behavior_byte != 0) {
                    behavior_byte = 1;
                }
            }
        }
        behavior = behavior_byte;
    }
    if (behavior == 1) {
        goto Lcase1;
    }
    if (behavior < 2) {
        if (behavior == 0) {
            goto Lcase0;
        }
        goto check_default_action;
    }
    if (behavior == 2) {
        goto Lcase2;
    }
    if (behavior == 4) {
        goto Lcase4;
    }
    goto check_default_action;

Lcase0:
    if ((func_800A2C34(creature) << 16) != 0) {
        return -1;
    }
    if ((func_80042900(creature, 6) << 16) == 0) {
        s32 found_slot = func_800A3544(creature, 0x1E);
        slot_or_distance = found_slot;
        if ((found_slot << 16) >= 0) {
            if (*(s32 *)(creature + 0x1C) & 0x20000) {
                idle_player_pos = D_80082E80;
                idle_player_dist = func_8009FD40(position, idle_player_pos);
                idle_player_range = func_800A35A4(creature, slot_or_distance);
                if ((idle_player_dist << 16) < (idle_player_range << 16)) {
                    if ((func_800A3518(D_800E3D7C[0]) << 16) != 0) {
                        s32 result;
                        register void *player_target;
                        *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                        *(u16 *)(creature + 0x2A) = func_800A0818(
                            position[0x24], position[0x25],
                            idle_player_pos[0x24], idle_player_pos[0x25], &slot_or_distance);
                        player_target = D_800814A8[0];
                        result = 4;
                        *(void **)(creature + 0x60) = player_target;
                        return result;
                    }
                }
            }
            scan_index = 0;
idle_ally_scan:
            ally_index = D_8008347E[0] & 1;
            do {
                ally_offset = ally_index * 4;
                ally = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
                if (ally != NULL) {
                    target_pos = *(void **)(ally - 0x14);
                    idle_ally_dist = func_8009FD40(position, target_pos);
                    idle_ally_range = func_800A35A4(creature, slot_or_distance);
                    if ((idle_ally_dist << 16) < (idle_ally_range << 16)) {
                        if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                            {
                                {
                                    s32 player_base, slot_action;
                                    slot_index = *(u16 *)&slot_or_distance;
                                    player_base = (s32)D_800814A8[0];
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
                                *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
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
        goto check_default_action;
    }
    {
        s32 action_code;
        s32 result;
        action_code = func_800A384C(creature, move_target, &direction, 0);
        action_or_flags = action_code;
        *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
        ASM_SCHED_BARRIER();
        lower_limit = action_code;
        if ((lower_limit << 16) < 0) {
            goto return_wait;
        }
        pending_action = lower_limit | 0x8000;
        goto store_move_action;
    }

Lcase1:
    if ((func_800A2C34(creature) << 16) != 0) {
        return -1;
    }
    if ((func_80042900(creature, 6) << 16) == 0) {
        s32 found_slot = func_800A3544(creature, 0x1E);
        slot_or_distance = found_slot;
        if ((found_slot << 16) >= 0) {
            if (*(s32 *)(creature + 0x1C) & 0x20000) {
                follow_player_pos = D_80082E80;
                follow_player_dist = func_8009FD40(position, follow_player_pos);
                follow_player_range = func_800A35A4(creature, slot_or_distance);
                if ((follow_player_dist << 16) < (follow_player_range << 16)) {
                    if ((func_800A3518(D_800814A8[0]) << 16) != 0) {
                        void *player_target;
                        register s32 target_direction;
                        *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                        target_direction = func_800A0818(
                            position[0x24], position[0x25],
                            follow_player_pos[0x24], follow_player_pos[0x25], &slot_or_distance);
                        player_target = D_800814A8[0];
                        *(u16 *)(creature + 0x2A) = target_direction;
                        *(void **)(creature + 0x60) = player_target;
                        return 4;
                    }
                }
            }
            scan_index = 0;
follow_ally_scan:
            ally_index = D_8008347E[0] & 1;
            do {
                ally_offset = ally_index * 4;
                ally = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
                if (ally != NULL) {
                    target_pos = *(void **)(ally - 0x14);
                    follow_ally_dist = func_8009FD40(position, target_pos);
                    follow_ally_range = func_800A35A4(creature, slot_or_distance);
                    if ((follow_ally_dist << 16) < (follow_ally_range << 16)) {
                        if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                            {
                                {
                                    s32 player_base, slot_action;
                                    slot_index = *(u16 *)&slot_or_distance;
                                    player_base = (s32)D_800814A8[0];
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
                                *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
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
        goto check_default_action;
    }
    {
        s32 action_code;
        s32 result;
        action_code = func_800A384C(creature, move_target, &direction, 0);
        action_or_flags = action_code;
        *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
        ASM_SCHED_BARRIER();
        lower_limit = action_code;
        if ((s16)lower_limit < 4) {
            goto return_wait;
        }
        pending_action = lower_limit | 0x8000;
        goto store_move_action;
    }

Lcase2:
    if ((func_80042900(creature, 6) << 16) == 0) {
        s32 found_slot = func_800A3544(creature, 0x1E);
        slot_or_distance = found_slot;
        if ((found_slot << 16) < 0) {
            goto check_player_action;
        }
        if (*(s32 *)(creature + 0x1C) & 0x20000) {
            assist_player_pos = D_80082E80;
            assist_player_dist = func_8009FD40(position, assist_player_pos);
            assist_player_range = func_800A35A4(creature, slot_or_distance);
            if ((assist_player_dist << 16) < (assist_player_range << 16)) {
                if ((func_800A3518(D_800814A8[0]) << 16) != 0) {
                    if ((func_800A2C34(creature) << 16) != 0) {
                        return -1;
                    }
                    {
                        void *player_target;
                        register s32 target_direction;
                        *(u16 *)(creature + 0x46) = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                        target_direction = func_800A0818(
                            position[0x24], position[0x25],
                            assist_player_pos[0x24], assist_player_pos[0x25], &slot_or_distance);
                        player_target = D_800814A8[0];
                        *(u16 *)(creature + 0x2A) = target_direction;
                        *(void **)(creature + 0x60) = player_target;
                        return 4;
                    }
                }
            }
        }
        scan_index = 0;
assist_ally_scan:
        ally_index = D_8008347E[0] & 1;
        do {
            ally_offset = ally_index * 4;
            ally = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
            if (ally != NULL) {
                target_pos = *(void **)(ally - 0x14);
                assist_ally_dist = func_8009FD40(position, target_pos);
                assist_ally_range = func_800A35A4(creature, slot_or_distance);
                if ((assist_ally_dist << 16) < (assist_ally_range << 16)) {
                    if ((func_800A3518(*(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                        if ((func_800A2C34(creature) << 16) != 0) {
                            return -1;
                        }
select_ally:
                        {
                            s32 player_base, slot_action;
                            slot_index = *(u16 *)&slot_or_distance;
                            player_base = (s32)D_800814A8[0];
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
                        *(void **)(creature + 0x60) = *(void **)((ally_offset + (s32)D_800814A8[0]) + 0xAC);
                        return 4;
                    }
                }
            }
            scan_index++;
            ally_index ^= 1;
        } while (scan_index < 2);
        goto check_player_action;
    }
    goto check_assist_action;

check_player_action:
    if (*(s32 *)(creature + 0x1C) & 0x20000) {
        if ((func_800A404C() << 16) == 0) {
            u8 *player = D_800814A8[0];
            if (player[0x9A] == 0x11) {
                u8 *player_target = *(u8 **)(player + 0x60);
                if (player_target != NULL) {
                    if (!(*(s32 *)(player_target + 0x14) & 0x2000)) {
                        {
                            s32 action_code;
                            register s32 checked_action ASM_REG("$3");
                            action_code = func_800A40AC(creature, (u16)func_8009CD58(player_target, 7, 0));
                            action_or_flags = action_code;
                            checked_action = action_code;
                            if ((checked_action << 16) < 0) {
                                goto check_assist_action;
                            }
                            action_code = checked_action | 0x8000;
                            *(u16 *)(creature + 0x46) = action_code;
                            *(u16 *)(creature + 0x2A) = func_800A0818(
                                position[0x24], position[0x25],
                                D_80082E80[0x24], D_80082E80[0x25], &action_or_flags);
                            return 3;
                        }
                    }
                }
            }
        }
    }
check_assist_action:
    if ((func_800A2C34(creature) << 16) == 0) {
        goto check_default_action;
    }
    return -1;

Lcase4:
    if ((func_800A2C34(creature) << 16) != 0) {
        return -1;
    }
    move_target = func_800A03C4(creature, position[0x24], position[0x25]);
    default_action = 0;
    *(void **)(creature + 0x60) = move_target;
    if (move_target == NULL) {
        goto check_default_action;
    }
    ASM_KEEP(default_action);
    {
        s32 action_code;
        u16 move_direction;
        action_code = func_800A384C(creature, move_target, &direction, 0);
        action_or_flags = action_code;
        if ((action_code << 16) < 0) {
            goto check_default_action;
        }
        move_direction = direction;
        *(u16 *)(creature + 0x46) = action_code | 0x8000;
        *(u16 *)(creature + 0x2A) = move_direction;
        return 1;
    }

check_default_action:
    if ((func_800A2C34(creature) << 16) == 0) {
        goto return_default;
    }
    return -1;

check_species_action:
    if ((func_800A2C34(creature) << 16) != 0) {
        return -1;
    }
    if (*(s32 *)(creature + 0x1C) & 0x10) {
        goto return_default;
    }
    {
        s8 room_index = *(s8 *)(position + 0x26);
        if (room_index >= 0) {
            if (D_800E2970[room_index].flags & 2) {
                goto return_default;
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

    {
        u32 kind_index = (u32)(creature[0x13] - 9);
        static void *const kind_labels[] = {
            &&Lcase9, &&Lcase10, &&wander, &&wander, &&wander, &&wander,
            &&wander, &&wander, &&wander, &&wander, &&wander, &&wander,
            &&Lcase21, &&Lcase22, &&Lcase23, &&Lcase24, &&Lcase25,
            &&Lcase26, &&Lcase27, &&Lcase28, &&Lcase29, &&wander, &&wander,
            &&Lcase32, &&wander, &&Lcase34, &&Lcase35, &&Lcase36,
            &&Lcase37, &&Lcase38, &&Lcase39, &&Lcase40, &&Lcase41,
            &&Lcase42, &&Lcase43, &&Lcase44
        };
        (void)kind_labels;
        if (kind_index >= 36) {
            goto wander;
        }
        goto *D_80089088[kind_index];
    }

Lcase25:
    func_800ADD20(creature, 0x10);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    STEPVEC(neighbor);
    if (neighbor[0x13] != 0) {
        goto wander;
    }
    if ((func_800A3518(creature) << 16) == 0) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x800A;
    return 6;

Lcase22:
    if (creature[0x48] != 0xF) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    near_player_pos = D_80082E80;
    if ((s16)func_8009FD40(near_player_pos, position) >= 0xB) {
        goto wander;
    }
    if (func_800A365C(position, near_player_pos) == 0) {
        goto wander;
    }
    if (func_800A36B4(creature, D_800E3D7C[0]) == 0) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8008;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        near_player_pos[0x24], near_player_pos[0x25], &action_or_flags);
    return 1;

Lcase44:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    ranged_player_pos = D_80082E80;
    ranged_distance = func_8009FD40(ranged_player_pos, position);
    if ((u32)((ranged_distance - 2) & 0xFFFF) >= 7) {
        goto wander;
    }
    if (func_800A365C(position, ranged_player_pos) == 0) {
        goto wander;
    }
    {
        s32 height_delta = (s16)func_800A0134(creature, D_800E3D7C[0]);
        height_delta = abs(height_delta);
        if (height_delta >= 0x21) {
            goto wander;
        }
    }
    target = func_800A05A4(creature, position[0x24], position[0x25], *(s16 *)(creature + 0x2A), (s16)ranged_distance);
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        goto wander;
    }
    if (func_800A36B4(creature, target) == 0) {
        goto wander;
    }
    if (creature[0xAE] != 0) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        ranged_player_pos[0x24], ranged_player_pos[0x25], &action_or_flags);
    return 5;

Lcase43:
    func_800ADD20(creature, 0x20);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        if (!(ability_flags & 0x100)) {
            goto wander;
        }
        if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
            goto wander;
        }
        if (ability_flags & 0x8000) {
            goto wander;
        }
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80[0x24], D_80082E80[0x25], &action_or_flags);
    return 5;

Lcase34:
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    if ((s8)position[0x26] < 0) {
        goto wander;
    }
    scan_index = 0;
    do {
        ally = *(void **)(((u8 *)D_800E3D7C[0] + scan_index * 4) + 0xAC);
        if (ally != NULL) {
            if ((func_800A2CAC(ally) << 16) != 0) {
                goto aim_at_player;
            }
        }
        scan_index++;
    } while (scan_index < 2);
    goto wander;

Lcase41:
    func_800ADD20(creature, 0x10);
    scan_index = 0;
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    do {
        target = *(u8 **)(((u8 *)D_800E3D7C[0] + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)func_800A0134(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((func_800A41F0(target) << 16) != 0) {
                    target_pos = *(void **)(target - 0x14);
                    if ((s16)func_8009FD40(target_pos, position) == 1) {
                        if (func_800C7F68(target) == 0) {
                            goto save_ability_target;
                        }
                    }
                }
            }
        }
        scan_index++;
    } while (scan_index < 2);
    goto wander;

Lcase40:
    func_800ADD20(creature, 0x40);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        if (ability_flags & 0x100) {
            *(u16 *)(creature + 0x98) = ability_flags | 0x8000;
            goto wander;
        }
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        goto wander;
    }

Lcase26:
    func_800ADD20(creature, 2);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            goto wander;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        goto wander;
    }
    if ((func_80042900(target, 1) << 16) != 0) {
        goto wander;
    }
    *(u16 *)(creature + 0x98) |= 0x8000;
    goto wander;

Lcase35:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    if (*(s16 *)(creature + 0xA6) != 0) {
        goto wander;
    }
    if (D_800E296C[0] & 4) {
        goto wander;
    }
    goto return_ability;

Lcase38:
    func_800ADD20(creature, 2);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    neighbor_check = func_800A2CB8(creature, target) << 16;
check_neighbor:
    if (neighbor_check == 0) {
        goto wander;
    }
    if ((func_80042900(target, 4) << 16) != 0) {
        goto wander;
    }
    goto return_ability;

Lcase39:
    func_800ADD20(creature, 0x10);
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            goto wander;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    if ((func_800A2CB8(creature, target) << 16) == 0) {
        goto wander;
    }
    if ((func_80042900(target, 2) << 16) != 0) {
        goto wander;
    }
    {
        *(u16 *)(creature + 0x46) = 0x8009;
        *(u16 *)(creature + 0x98) |= 0x8000;
        return 5;
    }

Lcase32:
    if (creature[0x49] == 0) {
        func_800ADD20(creature, 2);
        if (!(*(u16 *)(creature + 0x98) & 0x100)) {
            goto wander;
        }
        STEPVEC(neighbor);
        if (neighbor != D_800E3D7C[0]) {
            goto wander;
        }
        goto return_ability;
    }
    if (*(s32 *)(creature + 0x1C) & 0x410) {
        goto wander;
    }
    func_800AA53C(creature);
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        return 2;
    }
    if ((s8)position[0x26] >= 0) {
        func_800A0E6C(position, *(s8 *)(creature + 0x9C), creature, creature + 0x98);
        goto return_wait;
    }
    flee_player_pos = D_80082E80;
    if ((s16)func_8009FD40(position, flee_player_pos) != 1) {
        goto return_wait;
    }
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        flee_player_pos[0x24], flee_player_pos[0x25], creature + 0x98) + 0x800;
    goto return_wait;

Lcase36:
    {
        u16 ability_flags = *(u16 *)(creature + 0x98);
        *(u16 *)(creature + 0x98) = ability_flags & 0x7FFF;
    }
    if (creature[0x49] != 0) {
        goto wander;
    }
    if ((func_800A6E8C(position, 0x12, &tile_x, &tile_y) << 16) == 0) {
        goto wander;
    }
    action_result = func_800A0818(position[0x24], position[0x25], tile_x, tile_y, creature + 0x98);
    {
        s32 target_x = *(u16 *)&tile_x;
        s32 target_y = *(u16 *)&tile_y;
        s32 ability_flags = *(u16 *)(creature + 0x98);
        s32 x_delta, y_distance, shifted_x_delta;
        *(u16 *)(creature + 0x2A) = action_result;
        ability_flags |= 0x8000;
        ASM_KEEP_NV(ability_flags);
        *(u16 *)(creature + 0xA8) = target_x;
        target_x <<= 16;
        target_x >>= 16;
        *(u16 *)(creature + 0xAA) = target_y;
        target_y <<= 16;
        target_y >>= 16;
        *(u16 *)(creature + 0x98) = ability_flags;
        x_delta = position[0x24];
        x_delta -= target_x;
        ASM_KEEP_NV(x_delta);
        if (x_delta < 0) {
            x_delta = -x_delta;
        }
        ASM_KEEP_NV(x_delta);
        tile_x = x_delta;
        distance = x_delta;
        ASM_KEEP_NV(distance);
        shifted_x_delta = x_delta << 16;
        delta_or_result = position[0x25] - target_y;
        y_distance = delta_or_result;
        y_distance = abs(y_distance);
        tile_y = y_distance;
        x_delta = shifted_x_delta < (y_distance << 16);
        if (x_delta) {
            distance = y_distance;
        }
        if ((s16)distance == 1) {
            goto return_ability;
        }
        goto return_wait;
    }

Lcase37:
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

Lcase24:
    if ((s16)func_8009FD40(position, D_80082E80) < 2) {
        goto check_active_ability;
    }
    if (creature[0xB5] != 0) {
        goto check_occupied_tile;
    }
    func_800ADD20(creature, 8);
    if (*(u16 *)(creature + 0x98) & 0x100) {
        *(u16 *)(creature + 0x46) = 0x800A;
        return 6;
    }
check_active_ability:
    if (creature[0xB5] == 0) {
        goto wander;
    }
check_occupied_tile:
    neighbor = func_8009B25C(creature, position[0x24], position[0x25], *(s16 *)(creature + 0x88));
    if (neighbor == NULL) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto return_wait;
    }
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80[0x24], D_80082E80[0x25], creature + 0x98);
    goto return_wait;

Lcase42:
    func_800ADD20(creature, 4);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    {
        u8 *player_pos = D_80082E80;
        u16 height;
        if (func_800A365C(position, player_pos) == 0) {
            goto wander;
        }
        distance = func_8009FD40(player_pos, position);
        ASM_KEEP_NV(distance);
        if ((u32)((distance - 2) & 0xFFFF) >= 7) {
            goto wander;
        }
        height = *(u16 *)(creature + 0x88);
        scan_index = 0;
        direction = ((u32)func_800A0818(position[0x24], position[0x25], player_pos[0x24], player_pos[0x25], &action_or_flags) >> 9) & 7;
        tile_x = position[0x24];
        tile_y = position[0x25];
        if ((distance << 16) > 0) {
            u16 *x_steps = D_8006CCD8;
            u16 *y_steps = D_8006CCE8;
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
            goto wander;
        }
        goto return_directed_ability;
    }

Lcase27:
    func_800ADD20(creature, 4);
    scan_index = 0;
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    do {
        target = *(u8 **)(((u8 *)D_800E3D7C[0] + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)func_800A0134(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((func_800A41F0(target) << 16) != 0) {
                    if ((func_80042900(target, 0xC) << 16) == 0) {
                        target_pos = *(void **)(target - 0x14);
                        if ((s16)func_8009FD40(target_pos, position) == 1) {
                            goto aim_at_target;
                        }
                    }
                }
            }
        }
        scan_index++;
    } while (scan_index < 2);
    goto wander;

Lcase9:
Lcase10:
    target = func_800A02AC(creature, position[0x24], position[0x25]);
    if (target == NULL) {
        goto wander;
    }
    if ((u32)(target[0x13] - 0x33) >= 4) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    target_pos = *(void **)(target - 0x14);
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        target_pos[0x24], target_pos[0x25], &action_or_flags);
    return 5;

Lcase23:
    func_800ADD20(creature, 0x10);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    if (!(*(s32 *)(target + 0x14) & 0x4000)) {
        goto wander;
    }
    if (target == D_800E3D7C[0]) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x46) = 0x8009;
    return 5;

Lcase28:
    if (!(*(s32 *)(creature + 0x1C) & 0x20000)) {
        goto wander;
    }
    func_800ADD20(creature, 0x20);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    {
        s16 *tile_flags_out = &action_or_flags;
        u8 *player_pos = D_80082E80;
        u16 player_direction;
        player_direction = ((u32)func_800A0818(position[0x24], position[0x25], player_pos[0x24], player_pos[0x25], tile_flags_out) >> 9) & 7;
        direction = player_direction;
        if ((func_8009A350(position[0x24], position[0x25], player_direction, tile_flags_out) << 16) == 0) {
            goto wander;
        }
        if (action_or_flags & 0xB712) {
            goto wander;
        }
        if ((s16)func_8009FD40(player_pos, position) != 2) {
            goto wander;
        }
    }
return_directed_ability:
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

Lcase29:
    func_800ADD20(creature, 8);
    if (!(*(u16 *)(creature + 0x98) & 0x100)) {
        goto wander;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    if (!(*(s32 *)(target + 0x14) & 0x4000)) {
        goto wander;
    }
    {
        neighbor_check = target[0x13];
        goto check_neighbor;
    }

Lcase21:
    if (creature[0xA7] == 0) {
        goto wander;
    }
    if (creature[0xA8] != 0) {
        goto wander;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        goto wander;
    }
    if (target != D_800E3D7C[0]) {
        goto wander;
    }
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80[0x24], D_80082E80[0x25], &action_or_flags);
    return 5;

wander:
    move_target = func_800A3D18(position, creature, 2);
    *(void **)(creature + 0x60) = move_target;
    if (move_target != NULL) {
        action_result = func_800A384C(creature, move_target, &direction, 1);
        action_or_flags = action_result;
        *(u16 *)(creature + 0x2A) = *(u16 *)&direction;
        if ((action_result << 16) < 0) {
            goto return_wait;
        }
        pending_action = action_result | 0x8000;
store_move_action:
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
            tile_x = position[0x24] + *(u16 *)((facing * 2) + (u8 *)D_8006CCD8);
            tile_y = position[0x25] + *(u16 *)((facing * 2) + (u8 *)D_8006CCE8);
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
                goto return_ability;
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
    if ((s8)position[0x26] < 0) {
        goto return_default;
    }
    return 2;

aim_at_player:
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        D_80082E80[0x24], D_80082E80[0x25], &action_or_flags);
    return 5;

save_ability_target:
    *(u16 *)(creature + 0x46) = 0x8009;
    *(void **)(creature + 0xA8) = target;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        target_pos[0x24], target_pos[0x25], &action_or_flags);
    return 5;

aim_at_target:
    *(u16 *)(creature + 0x46) = 0x8009;
    *(u16 *)(creature + 0x2A) = func_800A0818(
        position[0x24], position[0x25],
        target_pos[0x24], target_pos[0x25], &action_or_flags);
    return 5;

return_default:
    delta_or_result = default_action << 16;
    ASM_KEEP(delta_or_result);
    return (u32)delta_or_result >> 16;
}
