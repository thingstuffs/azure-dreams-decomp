/* Monster resource slots (G00325). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_8009BE50, PD:dungeon/engine:800E3DA0, PD:dungeon/engine:800E3DB0, PD:dungeon/engine:800E3DD0, PD:dungeon/engine:800E3DE0. */
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "dungeon/item.h"

/* BYTES: this caller passes the promoted key; a narrow prototype changes its register allocation. */
extern void mark_sprite_resource_for_purge(s32 lookup_key);

/* Return whether one of six entries matches the ID, treating 0x39 as 2. */
s32 has_matching_six_slot_entry(entry_id)
s16 entry_id;
{
    s16 match_id = entry_id;
    u8 *entry = monster_resource_cache_slots;
    s16 index;

    if (entry_id == 0x39)
        match_id = 2;
    for (index = 0; index < 6; index++, entry += 8) {
        if (entry[1] != match_id) {
            continue;
        }
        return 1;
    }
    return 0;
}

/* Selects a slot by type and ID, clearing flags for special IDs. */
u8 *find_or_retain_sprite_resource_slot(s32 requested_id, s32 requested_type) {
    u8 *result;
    s32 slot_type;
    s32 match_id;
    s32 short_id;
    s16 slot_id;
    s32 saved_type;
    s32 slot_index;
    u8 *entry_id;
    u8 *candidate;
    u8 *entry;
    slot_id = requested_id;
    candidate = 0;
    saved_type = requested_type;
    slot_type = requested_type;
    short_id = requested_id;
    short_id = (s16)short_id;
    if (short_id == 0x38) {
        u8 *table;
        table = monster_resource_cache_slots;
        result = table + 0x10;
        table[0x11] = 0;
        monster_resource_cache_ids[2] = 0;
        monster_resource_cache_ids[1] = 0;
        monster_resource_cache_ids[0] = 0;
        return result;
    }
    match_id = 0x31;
    if (short_id == 0x31) {
        u8 *table;
        table = monster_resource_cache_slots;
        result = table + 8;
        table[9] = 0;
        monster_resource_cache_ids[1] = 0;
        monster_resource_cache_ids[0] = 0;
        return result;
    }
    if (short_id == 0x39)
        slot_id = 2;
    if ((s16)slot_type == 3) {
        entry = monster_resource_cache_slots + 0x20;
        slot_index = 4;
    } else {
        if ((s16)slot_type == 2) {
            u8 *slot_result;
            slot_result = monster_fixed_resource_slot;
            return slot_result;
        }
        entry = monster_resource_cache_slots;
        if (entry[0x11] == 0x38) {
            s32 start_index;
            start_index = 3;
            entry += 0x18;
            slot_index = start_index;
        } else {
            slot_index = 0;
            if (entry[9] == 0x31) {
                entry += 0x10;
                slot_index = 2;
            }
        }
    }
    goto scan;
return_type_two:
    {
        u8 *slot_result;
        monster_resource_cache_ids[6] = 0;
        slot_result = entry;
        return slot_result;
    }
scan:
    if (slot_index < 6) {
        s32 type_one;
        s32 type_three;
        s32 type_two;
        s8 *slot_ids;
        u8 entry_value;
        slot_type = (s16)saved_type;
        type_one = 1;
        type_three = 3;
        match_id = (s16)slot_id;
        type_two = 2;
        slot_ids = monster_resource_cache_ids;
        entry_id = entry + 1;
        do {
            if (((slot_type != type_one) && (slot_type != type_three)) || (*entry == slot_type)) {
                entry_value = *entry_id;
                if ((entry_value == 0) || (entry_value == match_id)) {
                    if (slot_type == type_two) {
                        goto return_type_two;
                    }
                    candidate = entry;
                    if ((*entry_id == match_id) || (*(s8 *)((unsigned long)slot_index + (unsigned long)slot_ids)
                        == match_id))
                        break;
                }
            } else
                break;
            slot_index++;
            entry_id += 8;
            entry += 8;
        } while (slot_index < 6);
    }
    if (candidate)
        retain_sprite_resource_in_cache((s16)slot_id);
    return candidate;
}

/* Returns an entry selected by type and ID, or null if no match is found. */
u8 *find_monster_entry_by_type_and_id(s16 entry_id, s32 entry_type) {
    s16 entry_index;
    u8 *entry;
    s16 next_index;
    s16 raw_type;

    raw_type = entry_type;
    entry_type <<= 16;
    entry_type >>= 16;
    if (entry_type == 3) {
        entry = D_800E3DD0;
        entry_index = 4;
    } else if (entry_type == 2) {
        return monster_fixed_resource_slot;
    } else if (monster_resource_cache_slots[0x11] == 0x38) {
        entry = monster_resource_cache_slots + 0x18;
        entry_index = 3;
    } else if (monster_resource_cache_slots[9] == 0x31) {
        entry = monster_resource_cache_slots + 0x10;
        entry_index = 2;
    } else {
        entry = monster_resource_cache_slots;
        entry_index = 0;
    }

    if (entry_index < 6) {
        entry_type = raw_type;
        do {
            if ((entry_type == 1 || entry_type == 3) && entry[0] != entry_type) {
                return 0;
            }
            if (entry[1] == entry_id) {
                return entry;
            }
            next_index = entry_index + 1;
            entry_index = next_index;
            entry += 8;
        } while (next_index < 6);
    }
    return 0;
}

/* Decrements a matching type-3 entry's count and clears it when exhausted. */
void decrement_monster_entry_count(s16 requested_id, s16 requested_type) {
    s16 slot;
    s16 match_id = requested_id;
    u8 *entry = monster_resource_cache_slots;

    if (requested_id == 0x39) {
        match_id = 2;
    }

    if (requested_type == 1 || requested_type == 3) {
        for (slot = 0; slot < 6; slot++, entry += 8) {
            u8 *count = entry + 2;
            u8 entry_type = entry[0];
            u8 entry_id;

            if (entry_type == requested_type && (entry_id = count[-1], entry_id == match_id)) {
                if ((s8)count[0] > 0) {
                    if (entry_type != 1) {
                        if ((s8)--count[0] <= 0) {
                            count[-1] = 0;
                            count[0] = 0;
                            if ((has_matching_six_slot_entry(entry_id) << 16) == 0) {
                                mark_sprite_resource_for_purge(entry_id);
                                return;
                            }
                        }
                    }
                }
                return;
            }
        }
    }
}
