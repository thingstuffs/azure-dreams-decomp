/* fallback handler position. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800991C4, CL:town/func_800992D0, CL:town/func_800992FC. */
#include "town/player/fallback_handler_position_g00541.h"
#include "town/player.h"
#include "engine/graphics.h"
#include "town/player/record.h"
#include "shared/sprite_frame_state.h"

/*
 * Computes and publishes a position offset for a matching primary key, requiring a second key
 * match for town_position_callback_address. Clears town_overlap_origin when neither key list
 * matches.
 */
void dispatch_fallback_position(TownPlayerRecord *entry, ObjectPosition *forwarded_a, void *forwarded_b)
{
    void **key_cursor;
    void **match_cursor;
    void *entry_key;

    key_cursor = D_800D04A4;
    if (*key_cursor != 0) {
        do {
            entry_key = entry->unk_00;
            if (entry_key == *key_cursor) {
                if (entry_key == town_position_callback_address) {
                    match_cursor = D_800D04B8;
                    if (*match_cursor != 0) {
                        do {
                            if (entry->unk_04 == *match_cursor++) {
                                compute_fallback_position_offset(entry, forwarded_a, forwarded_b);
                                return;
                            }
                        } while (*match_cursor != 0);
                    }
                } else {
                    compute_fallback_position_offset(entry, forwarded_a, forwarded_b);
                    return;
                }
            }
            key_cursor++;
        } while (*key_cursor != 0);
    }
    clear_town_overlap_origin();
}

/* Clears town_overlap_origin. */
void clear_town_overlap_origin(void) {
    town_overlap_origin = 0;
}

/*
 * Looks up the flagged resource record and computes a rotated scale/height offset from D_800D0AE4
 * plus the supplied vector, publishing computed_position through town_overlap_origin. Clears the
 * published pointer when no record is found.
 */
void compute_fallback_position_offset(TownPlayerRecord *object_arg, ObjectPosition *offset, void *resources) {
    TownPlayerRecord *object = object_arg;

    Record *record;
    s32 angle;
    s32 x;
    s32 y;
    s32 height;

    record = find_flagged_record_by_id(
        lookup_entry_by_byte_index(resources, *(u8 **)((u8 *)object + 0x1C), 4), 0);
    if (record != 0) {
        angle = ((u16)object->unk_10 - 0xC00) & 0xFFF;
        x = (record->scale * rcos(angle)) << 5;
        y = (-record->scale * rsin(angle)) << 5;
        height = record->height;
        town_overlap_origin = &computed_position;
        computed_position.x = town_fallback_origin.x + offset->x.v + x;
        computed_position.y = town_fallback_origin.y + offset->y.v + y;
        height <<= 17;
        computed_position.z = town_fallback_origin.z + offset->z.v + height;
        return;
    }
    town_overlap_origin = 0;
}

/* Passes an indexed byte and the object's signed field to get_nested_table_entry_data. */
void *lookup_entry_by_byte_index(SpriteFrameState *object, u8 *values, s32 index) {
    return get_nested_table_entry_data(object, values[index], object->unk_04, 0);
}

/* Return the second word of an indexed entry in the record's nested table. */
void *get_nested_table_entry_data(void *record, s32 row_index, s32 entry_index, s32 unused) {
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
