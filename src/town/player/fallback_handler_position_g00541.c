/* G00541: fallback handler position. */
/* Original-file evidence (G00541): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800991C4, CL:town/func_800992D0, CL:town/func_800992FC. */
#include "town/player/fallback_handler_position_g00541.h"

/* Dispatch to the matching or fallback handler using sentinel-terminated key lists. */
void dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(Unk99108 *entry, s32 forwarded_a, s32 forwarded_b, s32 *match_cursor)
{
    s32 *key_cursor;
    s32 entry_key;

    key_cursor = D_800D04A4;
    if (*key_cursor != 0) {
        do {
            entry_key = entry->unk0;
            if (entry_key == *key_cursor) {
                if (entry_key == (s32)D_80097D2C) {
                    match_cursor = D_800D04B8;
                    if (*match_cursor != 0) {
                        do {
                            if (entry->unk4 == *match_cursor++) {
                                compute_the_based_position_offset_publishes_resulting_vector(entry, (IntVector3 *)forwarded_a, (void *)forwarded_b);
                                return;
                            }
                        } while (*match_cursor != 0);
                    }
                } else {
                    compute_the_based_position_offset_publishes_resulting_vector(entry, (IntVector3 *)forwarded_a, (void *)forwarded_b);
                    return;
                }
            }
            key_cursor++;
        } while (*key_cursor != 0);
    }
    clear_global_80100_d_20();
}

/* Clears D_80100D20. */
void clear_global_80100_d_20(void) {
    D_80100D20 = 0;
}

/* Computes the record-based position offset and publishes the resulting vector. */
void compute_the_based_position_offset_publishes_resulting_vector(void *object, IntVector3 *offset, void *resources) {
    Record *record;
    s32 angle;
    s32 x;
    s32 y;
    s32 height;

    record = find_flagged_record_by_id(
        (void *)call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(resources, (u8 *)*(s32 *)((u8 *)object + 0x1C), 4), 0);
    if (record != 0) {
        angle = (*(u16 *)((u8 *)object + 0x10) - 0xC00) & 0xFFF;
        x = (record->scale * func_80064584(angle)) << 5;
        y = (-record->scale * func_800644B8(angle)) << 5;
        height = record->height;
        D_80100D20 = &D_800D0AFC;
        D_800D0AFC.x = D_800D0AE4.x + offset->x + x;
        D_800D0AFC.y = D_800D0AE4.y + offset->y + y;
        height <<= 17;
        D_800D0AFC.z = D_800D0AE4.z + offset->z + height;
        return;
    }
    D_80100D20 = 0;
}

/* Passes an indexed byte and the object's signed field to get_second_word_indexed_entry_in_s_nested_table. */
s32 call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(void *object, u8 *values, s32 index) {
    return get_second_word_indexed_entry_in_s_nested_table(object, values[index], ((s8 *)object)[4], 0);
}

/* Return the second word of an indexed entry in the record's nested table. */
s32 get_second_word_indexed_entry_in_s_nested_table(void *record, s32 row_index, s32 entry_index, s32 unused) {
    u8 *table_handle = *(u8 **)((u8 *)record + 0x28);
    u8 *table_ref = *(u8 **)table_handle;
    u8 *rows = *(u8 **)table_ref;
    u8 *entries = *(u8 **)(((s32)(row_index << 0x10) >> 0xE) + (s32)rows);
    return *(s32 *)(entries + ((s32)(entry_index << 0x10) >> 0xD) + 4);
}
