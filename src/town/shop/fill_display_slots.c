#include "common.h"
#include "shared/entity.h"

typedef struct S_800B62A4_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800B62A4_0;
void bzero(void *, s32);            /* extern */
void collect_selected_record_values();             /* extern */
void populate_display_row_with_icon(void *entry_data, s32 display_base, s32 row_index);            /* extern */
void populate_display_row();            /* extern */

typedef struct DisplaySlot {
    u8 pad_00[0x38];
    s32 *value;
} DisplaySlot;

/* Fill up to three output slots from source entries and clear unused slots. */
void fill_display_slots(EntityRec *source, s32 output) {
    void *entries[3];
    s32 index;
    s32 slot_count;
    s32 scan_base;
    s32 has_room;
    void *entry;
    s32 *slot_value;
    void *slot_cursor;
    void *source_cursor;

    slot_count = 0;
    index = slot_count;
    scan_base = 8;
    source_cursor = source;
    do {
        if (((S_800B62A4_0 *)source_cursor)->unk_08 != 0) {
            populate_display_row_with_icon((u8 *)source + scan_base, output, slot_count);
            slot_count += 1;
        }
        scan_base += 3;
        index += 1;
        source_cursor += 3;
    } while (index < 3);
    bzero(entries, 0xC);
    collect_selected_record_values(entries, source);
    index = 0;
    has_room = slot_count < 3;
    scan_base = slot_count;
    if (has_room != 0) {
        source_cursor = entries;
        do {
            entry = *(void **)source_cursor;
            if (entry != 0) {
                populate_display_row(entry, output, slot_count);
                slot_count += 1;
            }
            index += 1;
            source_cursor = (void *)((s8 *)source_cursor + 4);
        } while ((index + scan_base) < 3);
    }
    if ((slot_count < 3) && (source->unk_49 != 0)) {
        populate_display_row((u8 *)source + 0x48, output, slot_count);
        slot_count += 1;
    }
    index = slot_count;
    if (index < 3) {
        slot_cursor = (index * 4) + output;
        do {
            slot_value = ((DisplaySlot *)slot_cursor)->value;
            slot_cursor += 4;
            index += 1;
            *slot_value = 0;
        } while (index < 3);
    }
}
/* MECHANISM: A 3-pointer stack array forces the retail 0x40 frame. */
