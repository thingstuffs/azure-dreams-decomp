/* Item query checks g01145.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01145 - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, CL:town/func_800AC278, CL:town/func_800AC2D8, CL:town/func_800AC37C, CL:town/func_800AC3CC (+1 more).
 */
#include "town/event/item_query_checks_g01145.h"

/* Returns the matching index in the sentinel-terminated table, or -1. */
s32 find_sentinel_table_value_index(s32 target_value) {
    s32 i = 0;

    while (D_800D1054[i] != -1) {
        if (D_800D1054[i] == target_value) {
            return i;
        }
        i++;
    }
    return -1;
}

/* Passes the selected table entry to test_resident_bitmap_bit. */
s32 test_selected_resident_flag(s32 table_index) {
    test_resident_bitmap_bit(D_800D1064[table_index]);
}

/* Returns the selected query result, testing for zero for check type 3. */
s32 get_query_result_for_check_type(s32 check_type)
{
    switch (check_type) {
    case 0:
        return test_resident_bitmap_bit(Fp_niko_kenkatyu);
    case 2:
        return test_resident_bitmap_bit(Fp_far_kenkatyu);
    case 3:
        return test_resident_bitmap_bit(F_sbs07_pad03) == 0;
    default:
        return 0;
    }
}

/* Checks whether a slot's indexed value is at least three or slot three passes the helper check. */
s32 check_slot_threshold_or_fallback(s32 slot) {
    s16 *entry_indices;
    u8 *data_page;
    s32 entry_index;

    entry_indices = D_800D1054;
    entry_index = entry_indices[slot];
    data_page = (u8 *) 0x80010000;
    if (data_page[(entry_index * 4) + 0x35C4] >= 3U) {
        return 1;
    }
    if (slot == 3) {
        return test_resident_bitmap_bit(F_sbs07_pad04) == 0;
    }
    return 0;
}

/* Returns 3 for the selected flag, 0 for the query check, otherwise 2 or 1 from the slot check. */
s32 classify_item_check_result(s32 input) {
    s32 result;

    if (test_selected_resident_flag(input) != 0) {
        return 3;
    }
    if (get_query_result_for_check_type(input) != 0) {
        return 0;
    }
    result = check_slot_threshold_or_fallback(input);
    if (result != 0) {
        return 2;
    }
    return 1;
}

/* Classifies listed entry types by two value thresholds, returning 3 for unlisted types. */
s32 classify_listed_entry_type(u8 *entry) {
    s32 type_index;
    s32 entry_value;

    if (D_800D1074[0] != -1) {
        type_index = 0;
        do {
            if (D_800D1074[type_index] == entry[1]) {
                entry_value = get_item_sell_money(entry);
                if (entry_value < D_800D1080[0]) {
                    return 0;
                }
                if (entry_value < D_800D1080[1]) {
                    return 1;
                }
                return 2;
            }
            type_index++;
        } while (D_800D1074[type_index] != -1);
    }

    return 3;
}

/* Check whether the entry passes its kind-specific value filter. */
s32 filter_entry_by_kind(s32 unused, u8 *entry) {
    s32 k = entry[1];

    if (k == 13) {
        if (entry[0] == 4) {
            return 1;
        }
        if (entry[0] == 3) {
            return 1;
        }
        return 0;
    }
    if (k == 1) {
        return entry[0] != 8;
    }
    return 1;
}

/* Returns the table entry for a group and record, with a special-case override. */
s32 get_group_record_table_entry(s32 group_id, void *record) {
    s32 table_index;
    register s32 **table_slot;
    s32 **tables;
    s32 row_index;
    s32 column;
    s32 result;

    table_index = find_sentinel_table_value_index(group_id);
    if ((table_index != -1) && (filter_entry_by_kind(group_id, record) != 0)) {
        if ((FIELD_U8(record, 1) == 13) && (group_id == 9)) {
            if (FIELD_U8(record, 0) == 3) {
                if (test_resident_bitmap_bit(F_takoyaki_morau) != 0) {
                    u8 *special_result;

                    special_result = (u8 *)&D_8006BC7A;
                    return (s32)special_result;
                }
                return 0;
            } else {
                column = 3;
            }
        } else {
            column = classify_listed_entry_type(record);
        }
        row_index = classify_item_check_result(table_index);
        tables = D_800D1038;
        table_slot = (s32 **)((table_index * 4) + (s32)tables);
        result = (table_slot[0] + (row_index * 4))[column];
        return result;
    }
    return 0;
}

/* Increments the selected byte counter and clamps the result to three. */
void initialize_actor_sprite_and_animation(s32 entry_index) {
    u8 count;
    S_800A9C18_0 *entry;
    void *table_base;

    table_base = (void *) 0x80010000;
    entry = (entry_index * 4) + table_base;
    count = entry->unk_35C4 + 1;
    entry->unk_35C4 = count;
    if ((u32) (count & 0xFF) >= 4U) {
        entry->unk_35C4 = 3U;
    }
}

/* Returns whether D_8006ADD4 equals 0xD000C. */
s32 is_expected_movie_state(void) {
    return map_scene_selector_alias == 0xD000C;
}

/* Passes 0x11FA to test_resident_bitmap_bit. */
void test_resident_bit_11fa(void) {
    test_resident_bitmap_bit(Fp_niko_kenkatyu);
}

/* Calls test_resident_bitmap_bit with 0x11FB. */
void test_resident_bit_11fb(void) {
    test_resident_bitmap_bit(Fp_far_kenkatyu);
}

/* Returns the node matching a negative key with flag 0x400 clear, or NULL. */
void *find_unflagged_node_by_key(s32 target_key)
{
    S_80081498 *node;
    S_80081498 *next;
    s32 key;
    void *result;

    node = active_node_list_head.head;
    result = 0;
    while (node != 0) {
        key = node->field_10;
        next = node->next;
        if (key < 0 && !(node->field_1E & 0x400) && key == target_key) {
            return node;
        }
        node = next;
        result = 0;
    }
    return result;
}

/* Invokes retry_sound_sequence_when_ready for an eligible linked object with code 0xD04, then calls plt_carry_item_del_ext. */
void retry_sound_for_linked_item_and_remove_carry_item(void) {
    s8 *stateBase;
    S_800A9D00_0 *precedingState;

    stateBase = scene_object_payload_alias;
    precedingState = stateBase - 0x20;
    if ((get_linked_carry_item_data(stateBase, precedingState->unk_08,
                       precedingState->unk_0C) != 0) &&
        (((S_800A9D00_1 *)stateBase)->unk_2C != NULL) &&
        (((S_800A9D00_2 *)(((S_800A9D00_1 *)stateBase)->unk_2C))->unk_4C == 0xD04)) {
        retry_sound_sequence_when_ready();
    }
    plt_carry_item_del_ext();
}

/* Selects a response for the source and target, storing any associated text. */
void *select_response_for_source_and_target(void *source, void *target) {
    s32 response_kind;
    void *data_base;

    if ((source != 0) && (target != 0)) {
        if (((*(u8 *)((u8 *)target + 0x14) == 4) ||
             (*(u8 *)((u8 *)target + 0x4D) != 0)) &&
            ((data_base = *(void **)((u8 *)source - 0x10),
              (data_base == D_800C3174)) ||
             (data_base == D_800C321C) ||
             ((data_base == D_800C25C0) &&
              (*(s32 *)((u8 *)source + 0x60) != 0)))) {
            response_kind = *(s32 *)((u8 *)source + 0x60);
            if (response_kind == 4) {
                return D_8006C9E4;
            }
            if (response_kind == 5) {
                void *text5;
                if (*(u16 *)((u8 *)target + 0x4C) == 0xB05) {
                    data_base = (void *)0x80100000;
                    text5 = D_8006C8F7;
                } else {
                    data_base = (void *)0x80100000;
                    text5 = D_8006C982;
                }
                *(void **)((u8 *)data_base + 0xE38) = text5;
            } else {
                void *text_call;
                text_call = get_group_record_table_entry(response_kind, (u8 *)target + 0x4C);
                D_80100E38[0] = text_call;
                if (text_call == 0) {
                    return 0;
                }
            }
            return D_8006C894;
        }
    }
    return 0;
}
