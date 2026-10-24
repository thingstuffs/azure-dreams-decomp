/* G00541: fallback handler position. */
/* Original-file evidence (G00541): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800991C4, CL:town/func_800992D0, CL:town/func_800992FC. */
#include "town/player/fallback_handler_position_g00541.h"

/*
 * Computes and publishes a position offset for a matching primary key, requiring a second key
 * match for town_position_callback_address. Clears town_overlap_origin when neither key list
 * matches.
 */
void dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(Unk99108 *entry, void *forwarded_a, void *forwarded_b)
{
    void **key_cursor;
    void **match_cursor;
    void *entry_key;

    key_cursor = D_800D04A4;
    if (*key_cursor != 0) {
        do {
            entry_key = entry->unk0;
            if (entry_key == *key_cursor) {
                if (entry_key == town_position_callback_address) {
                    match_cursor = D_800D04B8;
                    if (*match_cursor != 0) {
                        do {
                            if (entry->unk4 == *match_cursor++) {
                                compute_the_based_position_offset_publishes_resulting_vector(entry, forwarded_a, forwarded_b);
                                return;
                            }
                        } while (*match_cursor != 0);
                    }
                } else {
                    compute_the_based_position_offset_publishes_resulting_vector(entry, forwarded_a, forwarded_b);
                    return;
                }
            }
            key_cursor++;
        } while (*key_cursor != 0);
    }
    clear_global_80100_d_20();
}

/* Clears town_overlap_origin. */
void clear_global_80100_d_20(void) {
    town_overlap_origin = 0;
}

/*
 * Looks up the flagged resource record and computes a rotated scale/height offset from D_800D0AE4
 * plus the supplied vector, publishing computed_position through town_overlap_origin. Clears the
 * published pointer when no record is found.
 */
void compute_the_based_position_offset_publishes_resulting_vector(void *object, IntVector3 *offset, void *resources) {
    Record *record;
    s32 angle;
    s32 x;
    s32 y;
    s32 height;

    record = find_flagged_record_by_id(
        call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(resources, *(u8 **)((u8 *)object + 0x1C), 4), 0);
    if (record != 0) {
        angle = (*(u16 *)((u8 *)object + 0x10) - 0xC00) & 0xFFF;
        x = (record->scale * rcos(angle)) << 5;
        y = (-record->scale * rsin(angle)) << 5;
        height = record->height;
        town_overlap_origin = &computed_position;
        computed_position.x = town_fallback_origin.x + offset->x + x;
        computed_position.y = town_fallback_origin.y + offset->y + y;
        height <<= 17;
        computed_position.z = town_fallback_origin.z + offset->z + height;
        return;
    }
    town_overlap_origin = 0;
}

/* Passes an indexed byte and the object's signed field to get_second_word_indexed_entry_in_s_nested_table. */
void *call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(void *object, u8 *values, s32 index) {
    return get_second_word_indexed_entry_in_s_nested_table(object, values[index], ((s8 *)object)[4], 0);
}

/* Return the second word of an indexed entry in the record's nested table. */
void *get_second_word_indexed_entry_in_s_nested_table(void *record, s32 row_index, s32 entry_index, s32 unused) {
    typedef struct {
        s32 unk_00;
        void *data;
    } ResourceEntry;
    u8 *table_handle = *(u8 **)((u8 *)record + 0x28);
    u8 *table_ref = *(u8 **)table_handle;
    ResourceEntry **rows = *(ResourceEntry ***)table_ref;
    ResourceEntry *entries = rows[(s16)row_index];
    entries += (s16)entry_index;
    return entries->data;
}
