/* Build selected entry output.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01237 - PR:town/ll34_3e5000_80016000:80017ADC, PR:town/ll34_3e5000_80016000:80017AE8, PR:town/ll34_3e5000_80016000:80017AF4, PR:town/ll34_3e5000_80016000:80017B00, PR:town/ll34_3e5000_80016000:80017B0C, PR:town/ll34_3e5000_80016000:80017B18.
 */
#include "town/scene/build_selected_entry_output_g01237.h"

/* Sets entry flags from record state and selection, then prepares the output buffer. */
u8 *build_selected_entry_output(s32 selected_index) {
    s32 entry_index;
    s32 first_marked;
    u8 *output_base;
    Record12 *record;
    void *entry;

    first_marked = 0;
    output_base = &D_80017D50;
    if (selected_index != 0) {
        for (entry_index = 1; entry_index < 8; entry_index++) {
            record = &((Record12 *)town_selection_records)[entry_index];
            entry = output_base + entry_index * 0x14;
            if (func_8001E670(record->field4) != 0) {
                if (record->field8 != 0) {
                    ((S_8001A86C_0 *)entry)->unk_02 = 0x400;
                    if (entry_index == 1) {
                        first_marked = 1;
                    }
                } else if (selected_index == entry_index) {
                    ((S_8001A86C_0 *)entry)->unk_02 = 0x400;
                }
            }
        }

    }

    dispatch_records_by_kind(output_base, &D_80017ADC);
    copy_callback_value_to_destination(output_base, &D_80017AE8);
    if (first_marked != 0) {
        *(s16 *)(output_base + 0xA2) = 0x400;
        copy_callback_value_to_destination(output_base + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(output_base + 0xB6) = 0x400;
        copy_callback_value_to_destination(output_base + 0xB4, &D_80017B0C);
    }
    copy_callback_value_to_destination(output_base + 0xDC, &D_80017AF4);
    copy_callback_value_to_destination(output_base + 0xC8, &D_80017B18);
    return output_base;
}

/* Builds the entry list and flags entries according to the selected index. */
void *build_entry_list(s32 entry_index) {
    u8 *entries = &D_80017D50;

    if (entry_index != 0) {
        *(s16 *)(entries + (entry_index * 0x14) + 2) = 0x400;
    }

    dispatch_records_by_kind(entries, &D_80017ADC);
    copy_callback_value_to_destination(entries, &D_80017AE8);

    if (entry_index == 1) {
        *(s16 *)(entries + 0xA2) = 0x400;
        copy_callback_value_to_destination(entries + 0xA0, &D_80017B00);
    } else {
        *(s16 *)(entries + 0xB6) = 0x400;
        copy_callback_value_to_destination(entries + 0xB4, &D_80017B0C);
    }

    copy_callback_value_to_destination(entries + 0xDC, &D_80017AF4);
    copy_callback_value_to_destination(entries + 0xC8, &D_80017B18);
    return entries;
}

/* Initialize the shared buffer using the selected table entry and return it. */
void *build_selected_record_buffer(s32 entry_index) {
    u8 *buffer = D_80017E54;

    *(s32 *)(buffer + 0xC) = *(s32 *)(((u8 *)town_selection_records) + (entry_index * 0xC));
    dispatch_records_by_kind(buffer, &D_80017AD0);
    copy_callback_value_to_destination(buffer + 0x14, &D_80017B0C);
    copy_callback_value_to_destination(buffer + 0x28, &D_80017B18);
    return buffer;
}

/* Initializes four consecutive entries in D_80017EA4 and returns their base address. */
s32 *build_four_record_value_block(void) {
    copy_callback_value_to_destination(&D_80017EA4, &D_80017AF4);
    copy_callback_value_to_destination(&D_80017EA4 + 0x14, &D_80017B24);
    copy_callback_value_to_destination(&D_80017EA4 + 0x28, &D_80017B0C);
    copy_callback_value_to_destination(&D_80017EA4 + 0x3C, &D_80017B18);
    return &D_80017EA4;
}

/* Process two locations in the data block and return its base address. */
s32 *build_two_record_value_block(void) {
    copy_callback_value_to_destination(&D_80017F08, &D_80017B0C);
    copy_callback_value_to_destination(&D_80017F08 + 0x14, &D_80017B18);
    return &D_80017F08;
}

/* Apply three value tables to consecutive global destinations and return their base. */
s32 *build_three_record_value_block(void) {
    copy_callback_value_to_destination(&D_80017F44, &D_80017AF4);
    copy_callback_value_to_destination(&D_80017F44 + 0x14, &D_80017B0C);
    copy_callback_value_to_destination(&D_80017F44 + 0x28, &D_80017B18);
    return &D_80017F44;
}
