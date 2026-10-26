#include "dungeon/level/room_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/dungeon_item_entries.h"
#include "shared/monster_ids.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/level.h"
extern int abs(int);
#ifndef NULL
#define NULL 0
#endif

/* ---- globals (declared array-style so every access stays %hi/%lo, never $gp) ---- */

/* ---- ordinary callees ---- */
extern s32 get_entity_effect_value();
extern s32 clear_slot_and_update_linked_state();
extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern u8 *find_eligible_actor_at_tile_and_height();
extern s32 get_tile_chebyshev_distance();
extern s32 get_actor_height_difference();
extern void * find_adjacent_actor();
extern void * find_monster_neighbor_candidate();
extern u8 *scan_actor_along_heading();
extern s32 get_rounded_facing_and_rounding_flag();
extern s32 select_actor_route_target();
extern s32 update_actor_proximity_flag();
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/state.h"
extern s32 has_low_actor_mp();
extern s32 check_entity_interaction_compatibility();
extern s32 check_scaled_value_threshold();
extern s32 find_slot_by_definition_kind();
extern s32 get_definition_field_from_triple();
extern s32 choose_usable_ability_or_attack();
extern void * choose_best_eligible_entry(void *owner_arg, void *start, s32 score_limit);
extern u16 select_highest_value_item();
extern s32 check_left_tile_and_center_height();
extern s32 find_nearest_floor_item_in_room();
extern s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z);
extern s32 update_actor_status_and_mp();
extern void refresh_actor_proximity_state(u8 *context);
extern s32 check_global_or_linked_flag_20000();

#define STEPVEC(neighbor_result)                                                            \
    {                                                                                    \
        u16 facing = ((*(u16 *)&((EntityRec *)creature)->facing) >> 9) & 7;                                  \
        direction = facing;                                                                 \
        neighbor_result = find_eligible_actor_at_tile_and_height(creature,                                           \
            (u16)(((TileObject *)position)->tile_position.parts.tile_x + *(u16 *)((facing * 2) + (u8 *)dir_step_x)),              \
            (u16)(((TileObject *)position)->tile_position.parts.tile_y + *(u16 *)((facing * 2) + (u8 *)dir_step_y)),              \
            ((EntityRec *)creature)->unk_88);                                                     \
    }

/* Selects a creature's next action and target from its behavior, species, and nearby tiles. */
s32 select_creature_action_and_target(s32 unused, u8 *position, u8 *creature, s32 lower_limit, u16 upper_limit, s32 status_out_addr)
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
    ((ActorRecord *)creature)->action_flags |= 0x4000;
    if (system_update_flags & 8) {
        update_actor_status_and_mp(creature);
        return -1;
    }
    if (creature[0x25] == 0) {
        default_action = 0;
        goto return_default;
    }
    if ((has_low_actor_mp(creature) << 16) != 0) {
        if ((find_nearest_floor_item_in_room(position, 0x60C, &tile_x, &tile_y) << 16) != 0) {
            if (creature[0x13] != MONSTER_WEADOG) {
                if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                    return -1;
                }
                if (tile_x == ((TileObject *)position)->tile_position.parts.tile_x && tile_y == ((TileObject *)position)->tile_position.parts.tile_y) {
                    s16 entry_index = find_floor_item_at_world_position(tile_x, tile_y, ((ActorRecord *)creature)->ground_height);
                    if (entry_index >= 0) {
                        /*
                         * BUG: this low-MP food path consumes the floor item without adding MP. The u16
                         * read is written back unchanged (the > 0x10000 test cannot pass); a creature with 1 MP
                         * still has 1 MP after eating. feed_actor_restore_mp adds 0xA00 for the same
                         * category-12, subtype-6 food before clamping.
                         */
                        s32 hp = *(u16 *)(creature + 0x24);
                        if (0x10000 < (s32)hp) {
                            hp = 0xFFFF;
                        }
                        *(u16 *)(creature + 0x24) = hp;
                        if (creature[0x25] != 0) {
                            ((ActorRecord *)creature)->flags1C &= ~ACTOR_MP_EMPTY;
                        }
                        {
                            u8 max_hp = creature[0x66];
                            if (max_hp < creature[0x25]) {
                                creature[0x25] = max_hp;
                                creature[0x24] = 0xFF;
                            }
                        }
                        /*
                         * BUG: clearing an arbitrary floor slot here leaves its tile's 0x800 item flag
                         * set. The clear helper updates that flag only for the player's selected floor entry.
                         * Unless this food is selected, the now-empty tile still blocks item placement;
                         * remove_floor_items_at_tile clears the flag too.
                         */
                        clear_slot_and_update_linked_state((entry_index * 4) + (u8 *)((u8 *)dungeon_ground_items));
                    }
                    return 0;
                }
                (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                    ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                    tile_x, tile_y, &slot_or_distance);
                ((ActorRecord *)creature)->action_flags = 0x800B;
                return 2;
            }
        }
    }

    update_actor_proximity_flag(position, creature, (s16)saved_lower_limit, (s16)upper_limit, status_out_addr);
    if ((((ActorRecord *)creature)->flags1C & (ACTOR_BLIND | ACTOR_CONFUSED | ACTOR_PLAYER_SIDE)) == 0x2000) {
        {
            ActorRecord *player = dungeon_actor_ring_anchor;
            behavior_byte = creature[0x12];
            if ((player->flags1C & (ACTOR_PARALYZED | ACTOR_ASLEEP)) || (get_entity_effect_value(player, STATUS_FROG) << 16) != 0) {
                if (((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE) {
                    if (behavior_byte != 0) {
                        behavior_byte = 1;
                    }
                }
            }
            behavior = behavior_byte;
        }
        switch (behavior) {
        case 0:
            if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                return -1;
            }
            if ((get_entity_effect_value(creature, STATUS_MAGIC_BIND) << 16) == 0) {
                s32 found_slot = find_slot_by_definition_kind(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE) {
                        idle_player_pos = &reference_tile_object;
                        idle_player_dist = get_tile_chebyshev_distance(position, idle_player_pos);
                        idle_player_range = get_definition_field_from_triple(creature, slot_or_distance);
                        if ((idle_player_dist << 16) < (idle_player_range << 16)) {
                            if ((check_scaled_value_threshold(((u8 *)dungeon_actor_ring_anchor)) << 16) != 0) {
                                s32 result;
                                register ActorRecord *player_target;
                                ((ActorRecord *)creature)->action_flags = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                    ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                    idle_player_pos->tile_position.parts.tile_x, idle_player_pos->tile_position.parts.tile_y, &slot_or_distance);
                                player_target = primary_actor_record;
                                result = 4;
                                ((ActorRecord *)creature)->target = player_target;
                                return result;
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = g_dungeon_status.turn_counter & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            idle_ally_dist = get_tile_chebyshev_distance(position, target_pos);
                            idle_ally_range = get_definition_field_from_triple(creature, slot_or_distance);
                            distance_scaled = idle_ally_dist << 16;
                            distance = (s32)distance_scaled < (idle_ally_range << 16);
                            if (distance) {
                                if ((check_scaled_value_threshold(*(void **)((ally_offset + (s32)primary_actor_record) + 0xAC)) << 16) != 0) {
                                    {
                                        {
                                            s32 player_base, slot_action;
                                            slot_index = *(u16 *)&slot_or_distance;
                                            player_base = (s32)primary_actor_record;
                                            slot_action = slot_index + 1;
                                            slot_action |= 0x8000;
                                            ally_slot_base = (u8 *)(ally_offset + player_base);
                                            ((ActorRecord *)creature)->action_flags = slot_action;
                                        }
                                        if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                                ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                                target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                        }
                                        ((ActorRecord *)creature)->target = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
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

            move_target = choose_best_eligible_entry(position, creature, 4);
            ((ActorRecord *)creature)->target = move_target;
            if (move_target == NULL) {
                break;
            }
            {
                s32 action_code;
                s32 result;
                action_code = choose_usable_ability_or_attack(creature, move_target, &direction, 0);
                action_or_flags = action_code;
                (*(u16 *)&((ActorRecord *)creature)->facing) = *(u16 *)&direction;
                case_code0 = action_code;
                if ((case_code0 << 16) < 0) {
                    ((ActorRecord *)creature)->action_flags = 0x800B;
                    return 2;
                }
                pending_action = case_code0 | 0x8000;
                ((ActorRecord *)creature)->action_flags = pending_action;
                return 1;
            }

        case 1:
            if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                return -1;
            }
            if ((get_entity_effect_value(creature, STATUS_MAGIC_BIND) << 16) == 0) {
                s32 found_slot = find_slot_by_definition_kind(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE) {
                        follow_player_pos = &reference_tile_object;
                        follow_player_dist = get_tile_chebyshev_distance(position, follow_player_pos);
                        follow_player_range = get_definition_field_from_triple(creature, slot_or_distance);
                        if ((follow_player_dist << 16) < (follow_player_range << 16)) {
                            if ((check_scaled_value_threshold(primary_actor_record) << 16) != 0) {
                                ActorRecord *player_target;
                                register s32 target_direction;
                                ((ActorRecord *)creature)->action_flags = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                target_direction = get_rounded_facing_and_rounding_flag(
                                    ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                    follow_player_pos->tile_position.parts.tile_x, follow_player_pos->tile_position.parts.tile_y, &slot_or_distance);
                                player_target = primary_actor_record;
                                (*(u16 *)&((ActorRecord *)creature)->facing) = target_direction;
                                ((ActorRecord *)creature)->target = player_target;
                                return 4;
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = g_dungeon_status.turn_counter & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            follow_ally_dist = get_tile_chebyshev_distance(position, target_pos);
                            follow_ally_range = get_definition_field_from_triple(creature, slot_or_distance);
                            if ((follow_ally_dist << 16) < (follow_ally_range << 16)) {
                                if ((check_scaled_value_threshold(*(void **)((ally_offset + (s32)primary_actor_record) + 0xAC)) << 16) != 0) {
                                    {
                                        {
                                            s32 player_base, slot_action;
                                            slot_index = *(u16 *)&slot_or_distance;
                                            player_base = (s32)primary_actor_record;
                                            slot_action = slot_index + 1;
                                            slot_action |= 0x8000;
                                            ally_slot_base = (u8 *)(ally_offset + player_base);
                                            ((ActorRecord *)creature)->action_flags = slot_action;
                                        }
                                        if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                                ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                                target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                        }
                                        ((ActorRecord *)creature)->target = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
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

            move_target = choose_best_eligible_entry(position, creature, -3);
            ((ActorRecord *)creature)->target = move_target;
            if (move_target == NULL) {
                break;
            }
            {
                s32 action_code;
                s32 result;
                action_code = choose_usable_ability_or_attack(creature, move_target, &direction, 0);
                action_or_flags = action_code;
                (*(u16 *)&((ActorRecord *)creature)->facing) = *(u16 *)&direction;
                case_code1 = action_code;
                if ((s16)case_code1 < 4) {
                    ((ActorRecord *)creature)->action_flags = 0x800B;
                    return 2;
                }
                pending_action = case_code1 | 0x8000;
                ((ActorRecord *)creature)->action_flags = pending_action;
                return 1;
            }

        case 2:
            if ((get_entity_effect_value(creature, STATUS_MAGIC_BIND) << 16) == 0) {
                s32 found_slot = find_slot_by_definition_kind(creature, 0x1E);
                slot_or_distance = found_slot;
                if ((found_slot << 16) >= 0) {
                    if (((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE) {
                        assist_player_pos = &reference_tile_object;
                        assist_player_dist = get_tile_chebyshev_distance(position, assist_player_pos);
                        assist_player_range = get_definition_field_from_triple(creature, slot_or_distance);
                        if ((assist_player_dist << 16) < (assist_player_range << 16)) {
                            if ((check_scaled_value_threshold(primary_actor_record) << 16) != 0) {
                                if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                                    return -1;
                                }
                                {
                                    ActorRecord *player_target;
                                    register s32 target_direction;
                                    ((ActorRecord *)creature)->action_flags = (*(u16 *)&slot_or_distance + 1) | 0x8000;
                                    target_direction = get_rounded_facing_and_rounding_flag(
                                        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                        assist_player_pos->tile_position.parts.tile_x, assist_player_pos->tile_position.parts.tile_y, &slot_or_distance);
                                    player_target = primary_actor_record;
                                    (*(u16 *)&((ActorRecord *)creature)->facing) = target_direction;
                                    ((ActorRecord *)creature)->target = player_target;
                                    return 4;
                                }
                            }
                        }
                    }
                    scan_index = 0;
                    ally_index = g_dungeon_status.turn_counter & 1;
                    do {
                        ally_offset = ally_index * 4;
                        ally = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
                        if (ally != NULL) {
                            target_pos = *(void **)(ally - 0x14);
                            assist_ally_dist = get_tile_chebyshev_distance(position, target_pos);
                            assist_ally_range = get_definition_field_from_triple(creature, slot_or_distance);
                            if ((assist_ally_dist << 16) < (assist_ally_range << 16)) {
                                if ((check_scaled_value_threshold(*(void **)((ally_offset + (s32)primary_actor_record) + 0xAC)) << 16) != 0) {
                                    if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                                        return -1;
                                    }
                                    {
                                        s32 player_base, slot_action;
                                        slot_index = *(u16 *)&slot_or_distance;
                                        player_base = (s32)primary_actor_record;
                                        slot_action = slot_index + 1;
                                        slot_action |= 0x8000;
                                        ally_slot_base = (u8 *)(ally_offset + player_base);
                                        ((ActorRecord *)creature)->action_flags = slot_action;
                                    }
                                    if (creature != *(u8 **)(ally_slot_base + 0xAC)) {
                                        (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                            ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                            target_pos[0x24], target_pos[0x25], &slot_or_distance);
                                    }
                                    ((ActorRecord *)creature)->target = *(void **)((ally_offset + (s32)primary_actor_record) + 0xAC);
                                    return 4;
                                }
                            }
                        }
                        scan_index++;
                        ally_index ^= 1;
                    } while (scan_index < 2);
                }
                if (((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE) {
                    if ((check_active_object_state_567() << 16) == 0) {
                        ActorRecord *player = primary_actor_record;
                        if (player->action_id == 0x11) {
                            ActorRecord *player_target = player->target;
                            if (player_target != NULL) {
                                if (!(player_target->flags14 & ACTOR_CLASS_ENABLED)) {
                                    {
                                        s32 action_code;
                                        u16 checked_action;
                                        action_or_flags = select_highest_value_item(creature, (u16)get_masked_record_flags(player_target, 7, 0));
                                        checked_action = action_or_flags;
                                        if ((checked_action << 16) >= 0) {
                                            action_code = checked_action | 0x8000;
                                            ((ActorRecord *)creature)->action_flags = action_code;
                                            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                                ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                                                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &action_or_flags);
                                            return 3;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((has_pending_actor_or_turn_action(creature) << 16) == 0) {
                break;
            }
            return -1;

        case 4:
            if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
                return -1;
            }
            move_target = find_monster_neighbor_candidate(creature, ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y);
            default_action = 0;
            ((ActorRecord *)creature)->target = move_target;
            if (move_target != NULL) {
                {
                    s32 action_code;
                    u16 move_direction;
                    action_code = choose_usable_ability_or_attack(creature, move_target, &direction, 0);
                    action_or_flags = action_code;
                    if ((action_code << 16) < 0) {
                        break;
                    }
                    move_direction = direction;
                    ((ActorRecord *)creature)->action_flags = action_code | 0x8000;
                    (*(u16 *)&((ActorRecord *)creature)->facing) = move_direction;
                    return 1;
                }
            }
        }
        if ((has_pending_actor_or_turn_action(creature) << 16) == 0) {
            delta_or_result = default_action << 16;
            return (u32)delta_or_result >> 16;
        }
        return -1;
    }
    if ((has_pending_actor_or_turn_action(creature) << 16) != 0) {
        return -1;
    }
    if (((ActorRecord *)creature)->flags1C & ACTOR_BLIND) {
        delta_or_result = default_action << 16;
        return (u32)delta_or_result >> 16;
    }
    {
        s8 room_index = ((TileObject *)position)->room_index;
        if (room_index >= 0) {
            if (dungeon_rooms[room_index].flags & ROOM_HOLY_BEAM) {
                delta_or_result = default_action << 16;
                return (u32)delta_or_result >> 16;
            }
        }
    }

    if ((get_entity_effect_value(creature, STATUS_MAGIC_BIND) << 16) == 0) {
        s32 found_slot = find_slot_by_definition_kind(creature, 0x1E);
        slot_or_distance = found_slot;
        if ((found_slot << 16) >= 0) {
            if ((check_scaled_value_threshold(creature) << 16) != 0) {
                slot_index = *(u16 *)&slot_or_distance;
                ((ActorRecord *)creature)->target = creature;
                ((ActorRecord *)creature)->action_flags = (slot_index + 1) | 0x8000;
                return 4;
            }
        }
    }

    switch (creature[0x13]) {

    case MONSTER_BALOON:
    roll_actor_flag_once(creature, 0x10);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    if (neighbor[0x13] != 0) {
        break;
    }
    if ((check_scaled_value_threshold(creature) << 16) == 0) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x800A;
    return 6;

    case MONSTER_TROLL:
    if (creature[0x48] != 0xF) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    near_player_pos = &reference_tile_object;
    if ((s16)get_tile_chebyshev_distance(near_player_pos, position) >= 0xB) {
        break;
    }
    if (check_row_column_or_diagonal_alignment(position, near_player_pos) == 0) {
        break;
    }
    if (check_tile_path_clear(creature, ((u8 *)dungeon_actor_ring_anchor)) == 0) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8008;
    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
        near_player_pos->tile_position.parts.tile_x, near_player_pos->tile_position.parts.tile_y, &action_or_flags);
    return 1;

    case MONSTER_GOLEM:
    roll_actor_flag_once(creature, 4);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    ranged_player_pos = &reference_tile_object;
    ranged_distance = get_tile_chebyshev_distance(ranged_player_pos, position);
    if ((u32)((ranged_distance - 2) & 0xFFFF) >= 7) {
        break;
    }
    if (check_row_column_or_diagonal_alignment(position, ranged_player_pos) == 0) {
        break;
    }
    {
        s32 height_delta = (s16)get_actor_height_difference(creature, ((u8 *)dungeon_actor_ring_anchor));
        height_delta = abs(height_delta);
        if (height_delta >= 0x21) {
            break;
        }
    }
    target = scan_actor_along_heading(creature, ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, ((ActorRecord *)creature)->facing, (s16)ranged_distance);
    if ((check_entity_interaction_compatibility(creature, target) << 16) == 0) {
        break;
    }
    if (check_tile_path_clear(creature, target) == 0) {
        break;
    }
    if (creature[0xAE] != 0) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
        ranged_player_pos->tile_position.parts.tile_x, ranged_player_pos->tile_position.parts.tile_y, &action_or_flags);
    return 5;

    case MONSTER_TYRANT:
    roll_actor_flag_once(creature, 0x20);
    {
        u16 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        if (!(ability_flags & 0x100)) {
            break;
        }
        if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
            break;
        }
        if (ability_flags & 0x8000) {
            break;
        }
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &action_or_flags);
    return 5;

    case MONSTER_WEADOG:
    roll_actor_flag_once(creature, 0x20);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    if ((s8)position[0x26] < 0) {
        break;
    }
    scan_index = 0;
    do {
        ally = *(void **)(((u8 *)((u8 *)dungeon_actor_ring_anchor) + scan_index * 4) + 0xAC);
        if (ally != NULL) {
            if ((has_low_actor_mp(ally) << 16) != 0) {
                ((ActorRecord *)creature)->action_flags = 0x8009;
                (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                    ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &action_or_flags);
                return 5;
            }
        }
        scan_index++;
    } while (scan_index < 2);
    break;

    case MONSTER_GARUDA:
    roll_actor_flag_once(creature, 0x10);
    scan_index = 0;
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    do {
        target = *(u8 **)(((u8 *)((u8 *)dungeon_actor_ring_anchor) + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)get_actor_height_difference(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((check_entity_eligibility(target) << 16) != 0) {
                    target_pos = *(void **)(target - 0x14);
                    if ((s16)get_tile_chebyshev_distance(target_pos, position) == 1) {
                        if (check_global_or_linked_flag_20000(target) == 0) {
                            ((ActorRecord *)creature)->action_flags = 0x8009;
                            *(void **)(creature + 0xA8) = target;
                            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                                ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
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

    case MONSTER_KILLER:
    roll_actor_flag_once(creature, 0x40);
    {
        u16 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        if (ability_flags & 0x100) {
            ((ActorRecord *)creature)->action_state_flags = ability_flags | 0x8000;
            break;
        }
        ((ActorRecord *)creature)->action_state_flags = ability_flags & 0x7FFF;
        break;
    }

    case MONSTER_DREAMIN:
    roll_actor_flag_once(creature, 2);
    {
        u16 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        ((ActorRecord *)creature)->action_state_flags = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            break;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if ((check_entity_interaction_compatibility(creature, target) << 16) == 0) {
        break;
    }
    if ((get_entity_effect_value(target, STATUS_SLEEP) << 16) != 0) {
        break;
    }
    ((ActorRecord *)creature)->action_state_flags |= 0x8000;
    break;

    case MONSTER_STEALTH:
    roll_actor_flag_once(creature, 4);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    if (*(s16 *)(creature + 0xA6) != 0) {
        break;
    }
    if (dungeon_floor_flags & 4) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    return 5;

    case MONSTER_ZU:
    roll_actor_flag_once(creature, 2);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    neighbor_check = check_entity_interaction_compatibility(creature, target) << 16;
    if (neighbor_check == 0) {
        break;
    }
    if ((get_entity_effect_value(target, STATUS_PARALYSIS) << 16) != 0) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    return 5;

    case MONSTER_MANDARA:
    roll_actor_flag_once(creature, 0x10);
    {
        u16 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        ((ActorRecord *)creature)->action_state_flags = ability_flags & 0x7FFF;
        if (!(ability_flags & 0x100)) {
            break;
        }
    }
    STEPVEC(neighbor);
    target = neighbor;
    if (target == NULL) {
        break;
    }
    if ((check_entity_interaction_compatibility(creature, target) << 16) == 0) {
        break;
    }
    if ((get_entity_effect_value(target, STATUS_CONFUSION) << 16) != 0) {
        break;
    }
    {
        ((ActorRecord *)creature)->action_flags = 0x8009;
        ((ActorRecord *)creature)->action_state_flags |= 0x8000;
        return 5;
    }

    case MONSTER_PICKET:
    if (creature[0x49] == 0) {
        roll_actor_flag_once(creature, 2);
        if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
            break;
        }
        STEPVEC(neighbor);
        if (neighbor != ((u8 *)dungeon_actor_ring_anchor)) {
            break;
        }
        ((ActorRecord *)creature)->action_flags = 0x8009;
        return 5;
    }
    if (((ActorRecord *)creature)->flags1C & (ACTOR_BLIND | ACTOR_CONFUSED)) {
        break;
    }
    refresh_actor_proximity_state(creature);
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        return 2;
    }
    if ((s8)position[0x26] >= 0) {
        select_actor_route_target(position, *(s8 *)(creature + 0x9C), creature, creature + 0x98);
    } else {
        flee_player_pos = &reference_tile_object;
        if ((s16)get_tile_chebyshev_distance(position, flee_player_pos) == 1) {
            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                flee_player_pos->tile_position.parts.tile_x, flee_player_pos->tile_position.parts.tile_y, creature + 0x98) + 0x800;
        }
    }
    ((ActorRecord *)creature)->action_flags = 0x800B;
    return 2;

    case MONSTER_VIPER:
    {
        u16 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        ((ActorRecord *)creature)->action_state_flags = ability_flags & 0x7FFF;
    }
    if (creature[0x49] != 0) {
        break;
    }
    if ((find_nearest_floor_item_in_room(position, 0x12, &tile_x, &tile_y) << 16) == 0) {
        break;
    }
    action_result = get_rounded_facing_and_rounding_flag(((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, tile_x, tile_y, creature + 0x98);
    {
        s32 target_x = *(u16 *)&tile_x;
        s32 target_y = *(u16 *)&tile_y;
        s32 ability_flags = ((ActorRecord *)creature)->action_state_flags;
        s32 x_delta, y_distance, y_delta;
        (*(u16 *)&((ActorRecord *)creature)->facing) = action_result;
        ability_flags |= 0x8000;
        *(u16 *)(creature + 0xA8) = target_x;
        target_x <<= 16;
        target_x >>= 16;
        *(u16 *)(creature + 0xAA) = target_y;
        target_y <<= 16;
        target_y >>= 16;
        ((ActorRecord *)creature)->action_state_flags = ability_flags;
        x_delta = ((TileObject *)position)->tile_position.parts.tile_x;
        x_delta -= target_x;
        x_delta = abs(x_delta);
        tile_x = x_delta;
        idle_ally_range = x_delta;
        x_delta <<= 16;
        y_delta = ((TileObject *)position)->tile_position.parts.tile_y - target_y;
        y_distance = y_delta;
        y_distance = abs(y_distance);
        tile_y = y_distance;
        distance = idle_ally_range;
        if (x_delta < (y_distance << 16)) {
            distance = y_distance;
        }
        if ((s16)distance == 1) {
            goto return_ability;
        }
        ((ActorRecord *)creature)->action_flags = 0x800B;
        return 2;
    }

    case MONSTER_NAPLASS:
    roll_actor_flag_once(creature, 0x20);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    return 5;

    case MONSTER_U_BOAT:
    if ((s16)get_tile_chebyshev_distance(position, ((u8 *)(&reference_tile_object))) >= 2) {
        if (creature[0xB5] == 0) {
            roll_actor_flag_once(creature, 8);
            if (((ActorRecord *)creature)->action_state_flags & 0x100) {
                ((ActorRecord *)creature)->action_flags = 0x800A;
                return 6;
            }
        }
    }
    if (creature[0xB5] == 0) {
        break;
    }
    neighbor = find_eligible_actor_at_tile_and_height(creature, ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, ((ActorRecord *)creature)->ground_height);
    if (neighbor == NULL) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        ((ActorRecord *)creature)->action_flags = 0x800B;
        return 2;
    }
    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, creature + 0x98);
    goto return_wait;

    case MONSTER_GLACIER:
    roll_actor_flag_once(creature, 4);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    {
        TileObject *player_pos = &reference_tile_object;
        u16 height;
        if (check_row_column_or_diagonal_alignment(position, player_pos) == 0) {
            break;
        }
        distance = get_tile_chebyshev_distance(player_pos, position);
        if ((u32)((distance - 2) & 0xFFFF) >= 7) {
            break;
        }
        height = *(u16 *)(creature + 0x88);
        scan_index = 0;
        direction = ((u32)get_rounded_facing_and_rounding_flag(((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y, &action_or_flags) >> 9) & 7;
        tile_x = ((TileObject *)position)->tile_position.parts.tile_x;
        tile_y = ((TileObject *)position)->tile_position.parts.tile_y;
        if ((distance << 16) > 0) {
            u16 *x_steps = dir_step_x;
            u16 *y_steps = dir_step_y;
            do {
                s32 next_x, next_y;
                s32 step_direction = *(s16 *)&direction;
                s32 x_step = x_steps[step_direction];
                s32 y_step = y_steps[step_direction];
                next_x = *(u16 *)&tile_x + x_step;
                next_y = *(u16 *)&tile_y + y_step;
                tile_x = next_x;
                tile_y = next_y;
                if ((check_left_tile_and_center_height((next_x << 6) & 0xFFC0, (next_y << 6) & 0xFFC0, (s16)(height + 0x20), next_x) << 16) != 0) {
                    step_limit = (s16)distance;
                    break;
                }
                {
                    s16 next_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0, ((tile_y << 6) + 0x20) & 0xFFE0, (s16)(height - 0x20));
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
            ((ActorRecord *)creature)->action_flags = action_word;
            (*(u16 *)&((ActorRecord *)creature)->facing) = facing << 9;
            return result;
        }
    }

    case MONSTER_BLUME:
    roll_actor_flag_once(creature, 4);
    scan_index = 0;
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    do {
        target = *(u8 **)(((u8 *)((u8 *)dungeon_actor_ring_anchor) + scan_index * 4) + 0xAC);
        if (target != NULL) {
            s32 height_delta = (s16)get_actor_height_difference(creature, target);
            height_delta = abs(height_delta);
            if (height_delta < 0x21) {
                if ((check_entity_eligibility(target) << 16) != 0) {
                    if ((get_entity_effect_value(target, STATUS_BRAINWASH) << 16) == 0) {
                        target_pos = *(void **)(target - 0x14);
                        if ((s16)get_tile_chebyshev_distance(target_pos, position) == 1) {
                            ((ActorRecord *)creature)->action_flags = 0x8009;
                            (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag( ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, target_pos[0x24], target_pos[0x25], &action_or_flags);
                            return 5;
                        }
                    }
                }
            }
        }
        scan_index++;
    } while (scan_index < 2);
    break;

    case MONSTER_SABER:
    case MONSTER_SNOWMAN:
    target = find_adjacent_actor(creature, ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y);
    if (target == NULL) {
        break;
    }
    if ((u32)(target[0x13] - MONSTER_WALL_OF_FIRE) >= 4) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    target_pos = *(void **)(target - 0x14);
    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
        target_pos[0x24], target_pos[0x25], &action_or_flags);
    return 5;

    case MONSTER_NOISE:
    roll_actor_flag_once(creature, 0x10);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
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
    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        break;
    }
    ((ActorRecord *)creature)->action_flags = 0x8009;
    return 5;

    case MONSTER_VOLCANO:
    if (!(((ActorRecord *)creature)->flags1C & ACTOR_PLAYER_AWARE)) {
        break;
    }
    roll_actor_flag_once(creature, 0x20);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
        break;
    }
    {
        s16 *tile_flags_out = &action_or_flags;
        TileObject *player_pos = &reference_tile_object;
        u16 player_direction;
        player_direction = ((u32)get_rounded_facing_and_rounding_flag(((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y, tile_flags_out) >> 9) & 7;
        direction = player_direction;
        if ((get_offset_map_cell_value_and_flags(((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y, player_direction, tile_flags_out) << 16) == 0) {
            break;
        }
        if (action_or_flags & 0xB712) {
            break;
        }
        if ((s16)get_tile_chebyshev_distance(player_pos, position) != 2) {
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
        ((ActorRecord *)creature)->action_flags = action_word;
        (*(u16 *)&((ActorRecord *)creature)->facing) = facing << 9;
        return result;
    }

    case MONSTER_CYCLONE:
    roll_actor_flag_once(creature, 8);
    if (!(((ActorRecord *)creature)->action_state_flags & 0x100)) {
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
        if ((get_entity_effect_value(target, STATUS_PARALYSIS) << 16) != 0) {
            break;
        }
        ((ActorRecord *)creature)->action_flags = 0x8009;
        return 5;
    }

    case MONSTER_PULUNPA:
    if (creature[0xA7] != 0) {
        if (creature[0xA8] == 0) {
            STEPVEC(neighbor);
            target = neighbor;
            if (target != NULL) {
                if (target == ((u8 *)dungeon_actor_ring_anchor)) {
                    ((ActorRecord *)creature)->action_flags = 0x8009;
                    (*(u16 *)&((ActorRecord *)creature)->facing) = get_rounded_facing_and_rounding_flag(
                        ((TileObject *)position)->tile_position.parts.tile_x, ((TileObject *)position)->tile_position.parts.tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &action_or_flags);
                    return 5;
                }
            }
        }
    }
    default:
        break;
    }
    move_target = choose_best_eligible_entry(position, creature, 2);
    ((ActorRecord *)creature)->target = move_target;
    if (move_target != NULL) {
        action_result = choose_usable_ability_or_attack(creature, move_target, &direction, 1);
        action_or_flags = action_result;
        (*(u16 *)&((ActorRecord *)creature)->facing) = *(u16 *)&direction;
        if ((action_result << 16) < 0) {
            ((ActorRecord *)creature)->action_flags = 0x800B;
            return 2;
        }
        pending_action = action_result | 0x8000;
        ((ActorRecord *)creature)->action_flags = pending_action;
        return 1;
    }
    goto check_forward_target;

return_wait:
    ((ActorRecord *)creature)->action_flags = 0x800B;
    return 2;

check_forward_target:
    {
        u8 kind = creature[0x13];
        if (kind != MONSTER_MANOEVA || (((ActorRecord *)creature)->flags14 & 0x20000000)) {
            {

                if ((s8)position[0x26] >= 0) {
                    return 2;
                }

                delta_or_result = default_action << 16;
                return (u32)delta_or_result >> 16;
            }
        }
        {
            u16 facing = ((*(u16 *)&((ActorRecord *)creature)->facing) >> 9) & 7;
            direction = facing;
            tile_x = ((TileObject *)position)->tile_position.parts.tile_x + *(u16 *)((facing * 2) + (u8 *)dir_step_x);
            tile_y = ((TileObject *)position)->tile_position.parts.tile_y + *(u16 *)((facing * 2) + (u8 *)dir_step_y);
        }
        target = NULL;
        if (creature[0xAC] == 0) {
            target = find_eligible_actor_at_tile_and_height(creature, *(u16 *)&tile_x, *(u16 *)&tile_y, ((ActorRecord *)creature)->ground_height);
            if (target != NULL) {
                u8 target_kind = target[0x13];
                if ((u32)(target_kind - 1) >= 0x2D || target_kind == kind) {
                    target = NULL;
                }
            }
        }
        if (creature[0xAC] < 2) {
            if (target == NULL) {
                target = (u8 *)((s16)find_floor_item_at_world_position(tile_x, tile_y, ((ActorRecord *)creature)->ground_height) + 1);
            } else {
                ((ActorRecord *)creature)->action_flags = 0x8009;
                return 5;
            }
        }
        if (target == NULL) {
            goto check_room;
        }
    }
return_ability:
    ((ActorRecord *)creature)->action_flags = 0x8009;
    return 5;

check_room:
    if ((s8)position[0x26] >= 0) {
        return 2;
    }
return_default:
    delta_or_result = default_action << 16;
    return (u32)delta_or_result >> 16;
}
