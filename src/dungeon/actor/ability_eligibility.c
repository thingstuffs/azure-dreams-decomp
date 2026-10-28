#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Select eligible actor abilities and entries, check tile clearance, and advance status timers.
 * Evidence: proven (string literals).
 * dungeon/engine#g0246 J1[80089000]
 * B1@0x80089000; B1@0x80089080; partial span, complete TU edges unknown.
 */
#include "dungeon/actor/ability_eligibility.h"
#include "dungeon/actor.h"

/* Copy the indexed entry data into the entity and clear its final byte. */
void copy_indexed_entry_data(void *entity) {
    void *entry_data;

    entry_data = ((S_800A34BC_0 *)(((*(u8 *)((u8 *)entity + 0x13)) * 0x14) + (s8 *)monster_species_table[0]))->unk_04;
    (*(Copy12 *)((u8 *)entity + 0x34)) = (*(Copy12 *)((u8 *)entry_data + 0));
    (*(s8 *)((u8 *)entity + 0x3C)) = 0;
}

/* Checks whether the scaled value reaches the stored threshold. */
s32 check_scaled_value_threshold(ActorRecord *state) {
    return ((s32) state->max_hp / (s32) (((u8) state->level >> 1) + 2)) >= (s32) state->hp;
}

/* Return the first of three slots with a matching entry kind, or -1. */
s16 find_slot_by_definition_kind(u8 *slots, u8 kind) {
    s32 slot_index;

    for (slot_index = 0; slot_index < 3; slot_index++) {
        if (slots[slot_index * 3 + 8] != 0 && item_action_definitions[slots[slot_index * 3 + 8]].unk_11 == kind) {
            return slot_index;
        }
    }
    return -1;
}

/* Returns the table field selected by the byte at offset 8 of a three-byte entry. */
u8 get_definition_field_from_triple(s32 entry_addr, s32 entry_index) {
    S_D_8006DE24 *lookup_table = item_action_definitions;

    entry_addr = entry_addr + entry_index * 3;
    return lookup_table[*(u8 *)(entry_addr + 8)].f13;
}

/* Computes a signed cyclic comparison score for two three-bit masks. */
s32 compare_three_bit_masks_cyclically(s32 left_mask, s32 right_mask) {
    s16 score;
    s16 left_bits;
    s16 right_bits;
    s32 masked_bit;

    score = 0;
    left_bits = left_mask;
    right_bits = right_mask;
    left_mask &= 1;
    if (left_mask) {
        masked_bit = right_mask & 4;
        left_mask = masked_bit != 0;
        score = left_mask;
        masked_bit = right_mask & 2;
        if (masked_bit) {
            score = left_mask - 1;
        }
    }
    if (left_bits & 2) {
        masked_bit = right_bits & 1;
        if (masked_bit) {
            score++;
        }
        masked_bit = right_bits & 4;
        if (masked_bit) {
            score--;
        }
    }
    masked_bit = left_bits & 4;
    if (!masked_bit) {
        return (s16)score;
    }
    masked_bit = right_bits & 2;
    if (masked_bit) {
        score++;
    }
    masked_bit = right_bits & 1;
    if (masked_bit) {
        score--;
    }
    return (s16)score;
}

/* arg1 in check_row_column_or_diagonal_alignment */

static __inline__ s32 position_delta_abs(u8 a, u8 b) {
    return __builtin_abs(a - b);
}

/* Return whether two positions share a row, column, or diagonal. */
s32 check_row_column_or_diagonal_alignment(MovingTile *source, MovingTile *target) {
    s32 aligned;
    s32 y_delta;
    s32 x_delta;

    x_delta = position_delta_abs(source->tile_x, target->tile_x);
    y_delta = position_delta_abs(source->tile_y, target->tile_y);

    aligned = 0;
    if ((x_delta == y_delta) || (x_delta == 0) || (y_delta == 0)) {
        aligned = 1;
    }
    return aligned;
}

/* Checks whether the tile path from source to target is clear. */
s32 check_tile_path_clear(void *source, void *target) {
    s32 step_y;
    s32 step_x;
    MovingTile *source_pos;
    MovingTile *target_pos;
    s32 check_param;
    s32 tile_x;
    s32 tile_y;
    s32 height;
    s16 check_height;

    source_pos = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_00;
    target_pos = ((S_800A36B4_1 *)((u8 *)target - 0x14))->unk_00;
    step_x = source_pos->tile_x - target_pos->tile_x;
    check_param = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_3E;
    if (step_x != 0) {
        if (step_x > 0) {
            step_x = 1;
        } else {
            step_x = -1;
        }
    }
    step_y = source_pos->tile_y - target_pos->tile_y;
    if (step_y != 0) {
        if (step_y > 0) {
            step_y = 1;
        } else {
            step_y = -1;
        }
    }
    tile_x = source_pos->tile_x;
    tile_y = source_pos->tile_y;
    height = ((S_800A36B4_0 *)((u8 *)source - 0x14))->unk_9C;

    while (tile_x != target_pos->tile_x ||
           tile_y != target_pos->tile_y) {
        check_height = height;
        if ((check_layer_offset_height((tile_x << 6) & 0xFFC0,
                           (tile_y << 6) & 0xFFC0,
                           check_height, (s16)check_param) << 16) != 0) {
            return 0;
        }
        tile_x -= step_x;
        tile_y -= step_y;
        {
            s32 next_height;
            next_height = sample_terrain_surface_height(((tile_x << 6) + 0x20) & 0xFFE0,
                                        ((tile_y << 6) + 0x20) & 0xFFE0,
                                        height - 0x20);
            if ((s16)next_height < check_height) {
                height = next_height;
            }
        }
    }
    return 1;
}

/* Returns the last byte of the selected 20-byte table entry. */
s32 get_definition_entry_byte_13(s16 entry_index) {
    DefEntry *entry = &item_action_definitions[entry_index];
    return entry->unk_13;
}

/* Selects a usable ability or adjacent attack and sets the angle toward the target. */
s32 choose_usable_ability_or_attack(Actor *actor, Actor *target, u16 *out_angle, s32 prefer_ability)
{
    u16 tile_flags;
    s32 slots_checked;
    s16 selected_action;
    s16 best_score;
    s16 line_valid;
    Entity *actor_entity;
    Actor *self;
    Entity *target_entity;
    DefEntry *ability;
    u8 ability_id;
    s32 effect_id;
    s16 effect_blocked;
    s16 obstacles;
    s32 move_flags;
    s32 path_flags;
    s32 distance;
    s32 angle;
    s16 slot;
    s32 temp;
    s32 offset;
    s16 steps;
    s16 x;
    s16 y;
    s32 score;
    s32 flags;
    s16 dir;

    selected_action = -1;
    best_score = -0x100;
    *out_angle = actor->field2a;
    self = actor;
    target_entity = *(Entity **)((u8 *)target - 0x14);
    actor_entity = *(Entity **)((u8 *)self - 0x14);
    if (abs(actor->coord88 - target->coord88) >= 0x40) {
        return -1;
    }
    line_valid = check_row_column_or_diagonal_alignment(actor_entity, target_entity);
    distance = (s16)get_tile_chebyshev_distance(target_entity, actor_entity);
    angle = get_rounded_facing_and_rounding_flag(actor_entity->x, actor_entity->y, target_entity->x, target_entity->y, &tile_flags);
    *out_angle = angle;
    if (prefer_ability == 0 && distance == 1) {
        if ((s16)check_diagonal_side_height((u16)((s16)angle >> 9), actor_entity->x, actor_entity->y,
                actor->coord88 - 0x20) != 0) {
            return 8;
        }
    }
    flags = actor->flags14;
    if (!(flags & 0x10000)) {
        actor->flags14 = flags | 0x10000;
        if ((s16)get_tile_chebyshev_distance(&reference_tile_object, actor_entity) < 0x11
            && ((actor->flags14 & (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER)) || !(self->status98 & 0x10) || !(generate_random_value() & 0xF))
            && !(generate_random_value() & 3) && (s16)get_entity_effect_value(actor, STATUS_MAGIC_BIND) == 0) {
            self->status98 |= 0x11;
        } else {
            self->status98 &= 0xFFFE;
        }
    }
    if (self->status98 & 1) {
        slot = g_dungeon_status.turn_counter & 3;
        for (slots_checked = 0; slots_checked < 3; slots_checked++, slot++) {
            if (slot == 3) {
                slot = 0;
            }
            offset = slot * 3;
            temp = (s32)actor + offset;
            ability_id = ((u8 *)temp)[8];
            if (ability_id == 0) {
                continue;
            }
            offset = ability_id << 2;
            offset += ability_id;
            offset <<= 2;
            ability = (DefEntry *)((u8 *)item_action_definitions + offset);
            effect_id = ability->unk_11;
            if ((u32)effect_id >= 0x12) {
                continue;
            }
            effect_blocked = get_entity_effect_value(target, (s8)effect_id);
            if (effect_blocked != 0) {
                continue;
            }
            if (ability->unk_13 < distance) {
                continue;
            }
            score = compare_three_bit_masks_cyclically(ability->unk_10, *(u16 *)&actor->flags14);
            if ((s16)score <= best_score) {
                continue;
            }
            temp = ability->kind;
            if (temp != 1) {
                if (temp == 0 || temp >= 4) {
                    continue;
                }
            } else {
                if (line_valid == 0) {
                    continue;
                }
                x = actor_entity->x;
                y = actor_entity->y;
                dir = (*out_angle >> 9) & 7;
                for (steps = 0; steps < distance; steps++) {
                    get_offset_map_cell_value_and_flags(x, y, dir, &tile_flags);
                    move_flags = actor->flags1c;
                    if (!(move_flags & 0x410)) {
                        path_flags = (s16)tile_flags;
                        if (move_flags & 0x2000) {
                            obstacles = path_flags & 0x300;
                        } else {
                            obstacles = path_flags & 0x3000;
                        }
                        if (obstacles != 0) {
                            break;
                        }
                    }
                    x += dir_step_x[dir];
                    y += dir_step_y[dir];
                }
                if (steps < distance) {
                    continue;
                }
            }
            best_score = score;
            selected_action = slot + 1;
        }
    }
    if (prefer_ability != 0 && distance == 1) {
        if ((s16)check_diagonal_side_height((u16)((s16)*out_angle >> 9), actor_entity->x, actor_entity->y,
                actor->coord88 - 0x20) != 0) {
            if (selected_action < 0) {
                selected_action = 8;
            }
        }
    }
    return selected_action;
}

/* Selects the best eligible list candidate, resolving ties with the global candidate. */
void *choose_best_eligible_entry(void *owner_arg, void *start, s32 score_limit)
{
    void *candidate;
    S_800A3D18_4 *base;
    S_800A3D18_5 *best;
    void *special;
    s16 special_score;
    s16 best_score;
    S_800A3D18_3 *global_page;
    S_800A3D18_2 *candidate_owner;
    void *next_link;
    s32 score;
    s32 special_cmp;
    s32 best_cmp;

    candidate = start;
    best = 0;
    special = best;
    special_score = 0x100;
    base = candidate;

    if ((s16)score_limit < 0) {
        best_score = -score_limit;
    } else {
        best_score = 0x100;
        if (((S_800A3D18_0 *)owner_arg)->unk_26 < 0) {
            best_score = score_limit;
        }
    }

    next_link = ((S_800A3D18_1 *)candidate)->unk_5C;
    candidate = (u8 *)next_link + 0x20;
    if (candidate != base) {
        global_page = (S_800A3D18_3 *)0x800e0000;
        while (candidate != base) {
            void *entry_link;
            if ((s16)check_entity_interaction_compatibility(base, candidate) != 0 && (s16)check_entity_eligibility(candidate) != 0) {
                candidate_owner = ((S_800A3D18_1_pre *)candidate)[-1].unk_00;
                if (((S_800A3D18_0 *)owner_arg)->unk_26 == candidate_owner->unk_26) {
                    score = get_tile_chebyshev_distance(candidate_owner, owner_arg);
                    if ((s16)score < best_score) {
                        if (candidate == global_page->unk_3D7C) {
                            special = candidate;
                            special_score = score;
                        } else {
                            best = candidate;
                            best_score = score;
                        }
                    }
                } else if ((s16)check_monster_neighbor_relations(((S_800A3D18_0 *)owner_arg)->unk_24,
                                              ((S_800A3D18_0 *)owner_arg)->unk_25,
                                              base->unk_88,
                                              candidate_owner->unk_24,
                                              candidate_owner->unk_25,
                                              ((S_800A3D18_1 *)candidate)->unk_88) != 0) {
                    if (candidate == global_page->unk_3D7C) {
                        special = candidate;
                        special_score = 1;
                    } else {
                        best = candidate;
                        best_score = 1;
                    }
                    break;
                }
            }
            entry_link = ((S_800A3D18_1 *)candidate)->unk_5C;
            candidate = (u8 *)entry_link + 0x20;
        }
    }

    if (special == 0) {
        return best;
    }
    if (best == 0) {
        best = special;
    } else {
        special_cmp = (s16)special_score;
        best_cmp = (s16)best_score;
        if (special_cmp == best_cmp) {
            if (best->unk_1C & 8) {
                best = special;
            } else if (!((((PlayerRecord *)((u8 *)dungeon_actor_ring_anchor))->unk_128 + ((S_800A3D18_1 *)candidate)->unk_43) & 3)) {
                best = special;
            }
        } else if (special_cmp < best_cmp) {
            best = special;
        }
    }
    return best;
}

/* Finds the first eligible entry with a matching nonnegative lookup ID or within one tile of (x, y). */
void *find_eligible_nearby_entry(s32 x, s32 y, void *end, void *owner)
{
    s32 lookup_id;
    s32 found_id;
    s32 target_x;
    void *current;
    S_800A3F28_1 *entry_data;
    s32 distance;
    s32 radius;
    s32 target_y;

    found_id = find_active_rect_containing_point((u16)x, (u16)y);
    current = (u8 *)((S_800A3F28_0 *)owner)->unk_5C + 0x20;
    if (current != end) {
        lookup_id = (s16)found_id;
        target_x = (s16)x;
        radius = 1;
        target_y = (s16)y;
        do {
            if ((check_entity_eligibility(current) << 16) != 0) {
                entry_data = (S_800A3F28_1 *)((S_800A3F28_0_pre *)current)[-1].unk_00;
                if (lookup_id == entry_data->unk_26 && lookup_id >= 0) {
                    return current;
                }
                distance = target_x - entry_data->unk_24;
                if (distance < 0) {
                    distance = -distance;
                }
                if (radius >= distance) {
                    distance = target_y - entry_data->unk_25;
                    if (distance < 0) {
                        distance = -distance;
                    }
                    if (radius >= distance) {
                        return current;
                    }
                }
            }
            current = (u8 *)((S_800A3F28_0 *)current)->unk_5C + 0x20;
        } while (current != end);
    }
    return NULL;
}

/* Return whether either object has the high state bit set and state code 5 through 7. */
s32 check_active_object_state_567(void) {
    s32 index;
    s32 result;
    u16 state;
    void *object;
    void *base;

    index = 0;
    base = primary_actor_record;
    do {
        object = *(void **)(base + 0xAC);
        if ((object != NULL) &&
            (state = *(u16 *)(object + 0x46), (state & 0x8000) != 0) &&
            ((u32)((state & 0x3FFF) - 5) < 3U)) {
            result = 1;
            return result;
        }

        index++;
        base += 4;
    } while (index < 2);

    result = 0;
    return result;
    result = 1;
    return result;
}

/* Selects the highest-value nonempty item among three slots, breaking ties by kind score. */
s16 select_highest_value_item(s32 records_addr, s32 item_kind)
{
    s16 result;
    s32 best_score;
    s16 best_value;
    s32 count;
    s32 table_or_result;
    s16 index;
    s32 value;
    s32 tripled_index;
    u8 item;

    s32 records;
    u8 *record;

    records = records_addr;
    records_addr = item_kind;
    result = -1;
    best_score = -4;
    best_value = 0;
    count = 0;
    tripled_index = g_dungeon_status.turn_counter;
    table_or_result = (s32)item_action_definitions;
    index = tripled_index & 3;
    do {
        if (((s16)(index)) == 3) {
            index = 0;
        }
        tripled_index = ((s16)(index)) * 3;
        record = (u8 *)records + tripled_index;
        item = record[8];
        if (item != 0) {
            s32 score;
            s32 prior_value;
            s16 candidate_value;

            value = record[9];
            tripled_index = item * 4;
            tripled_index += item;
            tripled_index *= 4;
            tripled_index += table_or_result;
            score = compare_three_bit_masks_cyclically(*(u8 *)(tripled_index + 16), (u16)records_addr);
            prior_value = best_value;
            candidate_value = value;
            if (prior_value < candidate_value) {
                best_value = value;
                result = index + 5;
                best_score = score;
            } else if (prior_value == candidate_value) {
                if ((best_score << 16) < (score << 16)) {
                    best_score = score;
                    result = index + 5;
                }
            }
            count++;
        } else {
            count++;
        }
        index++;
        if (count >= 3) {
            break;
        }
    } while (1);
    table_or_result = result;
    return table_or_result;
}

/* Checks entity eligibility using status flags and the linked entity's position. */
s32 check_entity_eligibility(void *entity) {
    u16 tile_flags;
    void *linked_entity;
    s32 check_result;

    if ((*(u8 *)((u8 *)entity + 0x28) + *(s16 *)((u8 *)entity + 0x64)) > 0) {
        if (*(s32 *)((u8 *)entity + 0x1C) & ACTOR_PLAYER_SIDE) {
            linked_entity = *(void **)((u8 *)entity - 0x14);
            get_offset_map_cell_value_and_flags(*(u8 *)((u8 *)linked_entity + 0x24) - 1,
                          *(u8 *)((u8 *)linked_entity + 0x25), 0, &tile_flags);
            if (tile_flags & 2) {
                return 0;
            }
        }
        if (!(*(s32 *)((u8 *)entity + 0x1C) & 0x290000)) {
            check_result = get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 16;
            return check_result == 0;
        }
        return 0;
    }
    return 0;
}

/* Finds the familiar slot referenced by a type-19 inventory record, or returns -1. */
s32 find_type_13_slot_index(DungeonSlot *targetSlot) {
    s32 recordIndex;
    s32 requiredRecordType;
    DungeonSlot **slotTable;
    u8 *recordSlotByte;
    s32 slotIndex;

    recordIndex = 0;
    requiredRecordType = 0x13;
    slotTable = familiar_record_slots;
    recordSlotByte = (u8 *) 0x8001024B;
    do {
        if (recordSlotByte[-2] == requiredRecordType) {
            slotIndex = recordSlotByte[0] & 0x1F;
            if (slotTable[slotIndex] == targetSlot) {
                return slotIndex;
            }
        }
        recordIndex++;
        recordSlotByte += 4;
    } while (recordIndex < 0x14);
    return -1;
}

/* Selects data at the entity's position and updates the owner's map or floor entry. */
void select_position_data_and_update_owner(SpriteFrameState *entity, ActorRecord *search_state) {
    s32 lookup_code;
    void *owner;
    u32 map_index_bits, floor_index_bits;
    u8 *map_base, *floor_base;
    s16 floor_index, map_index;
    u8 *floor_entry, *map_entry;

    lookup_code = lookup_definition_pair_value(entity->tile_x, entity->tile_y);
    if ((lookup_code << 16) != 0) {
        *(s16 *)temporary_item_record = (s16)(lookup_code | 0x1400);
        ((PlayerRecord *)primary_actor_record)->selected_floor_entry = 0;
        return;
    } else {
        map_index_bits = (u32)find_entry_at_tile_coordinates(entity->tile_x,
                                            entity->tile_y,
                                            search_state->ground_height) << 16;
        map_index = (s16)((s32)map_index_bits >> 16);
        if (map_index >= 0) {
            map_base = floor_objects;
            map_entry = map_base + map_index * 4;
            if (!(map_entry[3] & 0x40)) {
                *(void **)temporary_item_record = *(void **)map_entry;
                ((PlayerRecord *)primary_actor_record)->selected_floor_entry = map_entry;
                return;
            }
            ((PlayerRecord *)primary_actor_record)->selected_floor_entry = 0;
            return;
        }

        floor_index_bits = (u32)find_floor_item_at_world_position(entity->tile_x,
                                              entity->tile_y,
                                              search_state->ground_height) << 16;
        floor_index = (s16)((s32)floor_index_bits >> 16);
        if (floor_index >= 0) {
            floor_base = ((u8 *)dungeon_ground_items);
            floor_entry = floor_base + floor_index * 4;
            *(void **)temporary_item_record = *(void **)floor_entry;
            ((PlayerRecord *)primary_actor_record)->selected_floor_entry = floor_entry;
            return;
        }

        owner = primary_actor_record;
        *(void **)temporary_item_record = 0;
    }
    ((S_800A4300_2 *)owner)->unk_F0.i = 0;
}

/* Return the stored pointer when available, otherwise the fallback data buffer. */
u8 *get_stored_or_fallback_data(void) {
    u8 *stored_data;

    if (temporary_item_record[1] < 0x14U) {
        stored_data = *(u8 **)((u8 *)primary_actor_record + 0xF0);
        if (stored_data != NULL) {
            return stored_data;
        }
        *(s32 *)temporary_item_record = 0;
    }
    return temporary_item_record;
}

/*
 * Scans up to four floor-marker entries for the key pair and returns its value, stopping with zero
 * at the first value below two or on no match.
 */
s32 lookup_definition_pair_value(s16 firstKey, s16 secondKey) {
    s32 entryIndex;
    s16 entryValue;

    for (entryIndex = 0; entryIndex < 4; entryIndex++) {
        entryValue = dungeon_floor_marker_entries[entryIndex].kind;
        if (entryValue < 2) {
            return 0;
        }
        if ((firstKey == dungeon_floor_marker_entries[entryIndex].x) &&
            (secondKey == dungeon_floor_marker_entries[entryIndex].y)) {
            return entryValue;
        }
    }
    return 0;
}

/* Tests for a flagged floor or a height above 0x200 at the layer-offset cell. */
s16 check_layer_offset_height(u16 x, u16 y, s16 height, u32 flags)
{
    s16 floor_height;
    s16 offset_height;
    s32 probe_height;
    s32 layer_offset;
    u16 offset_cell_x;
    u16 offset_cell_y;
    u16 *x_offsets;
    u16 *layer_x_offset;
    u16 *layer_y_offset;
    s16 saved_height;
    u32 cell_x;
    u32 cell_y;
    s32 layer;
    s32 query_cell_x;
    s32 query_cell_y;

    saved_height = height;
    cell_x = x >> 6;
    query_cell_x = cell_x;
    cell_y = y >> 6;
    query_cell_y = cell_y;
    layer = (flags >> 9) & 7;

    if ((get_offset_map_cell_value_and_flags(query_cell_x, query_cell_y, layer, &floor_height) << 16) == 0) {
        return 0;
    }
    if (floor_height & 0x8000) {
        return 1;
    }

    probe_height = (s16)(saved_height - 0x20);
    x_offsets = (u16 *)((s8 *)dir_step_x);
    layer_offset = layer * 2;
    layer_x_offset = (u16 *)((s8 *)x_offsets + layer_offset);
    layer_y_offset = (u16 *)((s8 *)((s8 *)dir_step_y) + layer_offset);
    offset_cell_x = *layer_x_offset + cell_x;
    offset_cell_y = *layer_y_offset + cell_y;
    offset_height = sample_terrain_surface_height(
        ((((offset_cell_x) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((offset_cell_y) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        probe_height);
    floor_height = offset_height;
    return (offset_height << 16) > 0x02000000;
}

/* Checks the left tile and tests the height at the current tile center. */
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z)
{
    s16 height;
    s32 grid_x;
    s32 grid_y;
    u16 tile_x;
    u16 tile_y;
    s32 height_result;
    s32 height_limit;

    grid_x = (u16)x >> 6;
    grid_y = (u16)y >> 6;
    tile_x = grid_x;
    tile_y = grid_y;
    if ((get_offset_map_cell_value_and_flags(grid_x - 1, grid_y, 0, &height) << 16) == 0) {
        return 0;
    }
    if (height & 0x8000) {
        return 1;
    }

    height_result = sample_terrain_surface_height((tile_x << 6) | 0x20,
                                  (tile_y << 6) | 0x20,
                                  (s16)(z - 0x20));
    height = height_result;
    height_result <<= 16;
    height_limit = 0x02000000;

    return height_limit < height_result;
}

/* Checks whether the selected neighbor has a sampled height above 512 when enabled. */
s32 check_enabled_neighbor_height(s32 world_x, s32 world_y, s16 world_z, u32 direction, s32 disabled) {
    u16 tile_value;
    u16 x_offset;
    u16 y_offset;
    u32 tile_x;
    s32 tile_y;
    u32 shifted_sector;
    s32 sector_arg;
    s32 call_x;
    u32 call_y;
    u16 sector;
    s32 height;
    s32 sample_z;
    u16 neighbor_x;
    u16 neighbor_y;
    register s32 result;

    tile_x = (u32)(world_x & 0xFFFF) >> 6;
    tile_y = (u32)(world_y & 0xFFFF) >> 6;
    shifted_sector = direction >> 9;
    sector_arg = shifted_sector & 7;

    if (disabled != 0) {
        return 0;
    }
    call_x = tile_x;
    call_y = tile_y;
    sector = sector_arg;
    if ((get_offset_map_cell_value_and_flags(call_x, call_y, sector_arg, &tile_value) << 16) == 0) {
        return 0;
    }

    sample_z = (s16)(world_z - 0x20);
    x_offset = dir_step_x[sector];
    y_offset = dir_step_y[sector];
    neighbor_x = x_offset + tile_x;
    neighbor_y = y_offset + tile_y;
    height = sample_terrain_surface_height(
        ((((neighbor_x) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((neighbor_y) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        sample_z);
    result = 0x02000000 < (height << 16);
    tile_value = height;
    return result;
}

/* Checks whether the current and offset tile centers both yield values above 0x200. */
s16 check_adjacent_tile_height_clearance(u16 x, u16 y, s32 z, void *skip_check) {
    s16 probe_result;
    s16 center_result;
    s32 center_delta;
    s32 x_distance;
    u32 center_x;
    s16 source_z;
    u32 center_y;
    u16 start_y;
    u16 start_x;
    s32 x_offset;
    s32 x_step;
    s32 y_offset;
    u32 probe_x;
    u32 probe_y;
    u32 cell;
    u32 cell_y;
    u32 coord_work;

    source_z = z;
    if (skip_check == 0) {
        cell = x >> 6;
        probe_x = cell - 1;
        cell_y = y >> 6;
        start_x = cell;
        start_y = cell_y;
        if (get_offset_map_cell_value_and_flags(probe_x, cell_y, 0, &probe_result) != 0) {
            center_x = (start_x << 6) + 0x20;
            probe_x = center_x & 0xFFE0;
            coord_work = (start_y << 6) + 0x20;
            probe_y = coord_work & 0xFFE0;
            center_y = coord_work;
            center_result = sample_terrain_surface_height(probe_x, probe_y, (s16) (z - 0x20));
            probe_result = center_result;
            z = center_x;
            if (center_result >= 0x201) {
                center_delta = (s16) (center_x - x);
                x_distance = (s32) (s16) center_delta;
                if (center_delta < 0) {
                    x_distance = 0 - x_distance;
                }
                x_offset = 0;
                if (x_distance >= 0x16) {
                    x_step = 0x40;
                    if (center_delta > 0) {
                        x_step = -0x40;
                    }
                    x_offset = x_step;
                }
                center_delta = (s16) (center_y - y);
                y_offset = (s32) (s16) center_delta;
                if (center_delta < 0) {
                    y_offset = 0 - y_offset;
                }
                if (y_offset >= 0x16) {
                    y_offset = 0x40;
                    if (center_delta > 0) {
                        y_offset = -0x40;
                    }
                } else {
                    y_offset = 0;
                }
                probe_result = sample_terrain_surface_height((z + x_offset) & 0xFFFF, (center_y + y_offset) & 0xFFFF,
                    (s16) (source_z - 0x20));
                center_x = probe_result > 0x200;
                return center_x;
            }
        }
    }
    return 0;
}

/* Updates or inserts a four-slot entry, clearing conflicts or evicting an entry when full. */
s16 set_or_clear_actor_status_slot(ActorRecord *owner, s8 id, s8 value) {
    s16 min_id;
    s32 i;
    s32 used;

    min_id = 0x100;
    for (i = 3; i >= 0; i--) {
        if (owner->status[i].type == id) {
            if ((((u8)value ^ (u8)owner->status[i].value) & 0x80) || value == 0) {
                end_status_effect_message(owner, owner->status[i].type);
                owner->status[i].type = 0;
                owner->status[i].value = 0;
            } else {
                owner->status[i].value = value;
            }
            apply_entity_action_flags(owner, id);
            return i;
        }
    }
    for (i = 3; i >= 0; i--) {
        used = owner->status[i].type;
        if (used == 0) {
            if (id == STATUS_SLEEP) {
                clear_slots_of_type(owner, STATUS_PARALYSIS);
            } else if (id == STATUS_PARALYSIS) {
                clear_slots_of_type(owner, STATUS_SLEEP);
            }
            owner->status[i].type = id;
            owner->status[i].value = value;
            apply_entity_action_flags(owner, id);
            return i;
        }
        if (used < min_id) {
            min_id = used;
        }
    }
    if (min_id > id) {
        clear_slots_of_type(owner, min_id);
        return set_or_clear_actor_status_slot(owner, id, value);
    }
    return -1;
}

/* Return whether any of the four spaced status bytes is zero. */
s32 has_empty_status_slot(s32 record_addr) {
    s32 status_index;
    void *status_cursor;

    for (status_index = 3, status_cursor = (void *)(record_addr + 6); status_index >= 0; status_index--, status_cursor -= 2) {
        if (((S_800A4A9C_0 *)status_cursor)->unk_2C == 0) {
            return 1;
        }
    }
    return 0;
}

/* Advance four status timers toward zero and clear expired statuses. */
void advance_status_timers(void *record) {
    s32 slot_index;
    s8 status;
    s8 duration;
    u8 expired_status;
    slot_index = 3;
    do {
        status = ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C;
        if (status != 0) {
            if (status == STATUS_POISON) {
                apply_capped_damage_and_hit_effect(record, ((S_800A4ACC_1 *)((u8 *)record - 0x18))->unk_00);
            }
            duration = ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D;
            if (duration != 0) {
                if (duration > 0) {
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D - 1);
                } else if (duration < 0) {
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D + 1);
                }
                if (((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D == 0) {
                    expired_status = (u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C;
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C = 0;
                    end_status_effect_message(record, (s8)expired_status);
                }
            }
        }
        slot_index -= 1;
    } while (slot_index >= 0);
}
