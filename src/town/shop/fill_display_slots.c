#include "common.h"
#include "shared/entity.h"
#include "sdk/libc.h"
#include "town/shop.h"

typedef struct S_800B62A4_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800B62A4_0;

/* Fill up to three output slots from source entries and clear unused slots. */
void fill_display_slots(ActorRecord *source, ItemMenuPart **output) {
    void *entries[3];
    s32 index;
    s32 slot_count;
    s32 scan_base;
    s32 has_room;
    void *entry;
    ItemMenuPart *part;
    ItemMenuPart **slot_cursor;
    /* Three-byte source slots and four-byte pointer slots share this byte cursor. */
    u8 *source_cursor;

    slot_count = 0;
    index = slot_count;
    scan_base = 8;
    source_cursor = (u8 *)source;
    do {
        if (((S_800B62A4_0 *)source_cursor)->unk_08 != 0) {
            populate_action_display_row((u8 *)source + scan_base, output, slot_count);
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
        source_cursor = (u8 *)entries;
        do {
            entry = *(void **)source_cursor;
            if (entry != 0) {
                populate_display_row(entry, output, slot_count);
                slot_count += 1;
            }
            index += 1;
            source_cursor = ((s8 *)source_cursor + 4);
        } while ((index + scan_base) < 3);
    }
    if ((slot_count < 3) && (source->carried_item.kind != 0)) {
        populate_display_row((u8 *)source + 0x48, output, slot_count);
        slot_count += 1;
    }
    index = slot_count;
    if (index < 3) {
        slot_cursor = (ItemMenuPart **)(index * sizeof(*output) + (unsigned long)output);
        do {
            part = slot_cursor[14];
            slot_cursor++;
            index += 1;
            part->handler = 0;
        } while (index < 3);
    }
}
/* MECHANISM: A 3-pointer stack array forces the retail 0x40 frame. */
