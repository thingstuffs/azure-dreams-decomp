#include "sdk/libc.h"
/* Format compared object statistics and populate display rows.
 * Evidence: proven (string literals).
 * town/engine#g1058 J1[800892C0,800892C8,800892CC,800892F0,800892FC,80089304,80089324,8008933C,80089340]
 * B2@0x8008929c; B2@0x80089ae8; partial span, complete TU edges unknown.
 */
#include "town/shop/stat_display.h"

/* Builds a formatted marker string for the object's value, including an odd remainder. */
void *format_object_value_marker(void *output, void *object)
{
    u32 value;
    s32 pair_test;
    s16 count;
    u32 marker_page;
    u8 format_buf[64];
    s32 pair_count;
    s32 pair_index;

    *(Text5 *)output = D_800892DC;
    strcat(output, func_8004E634(1, format_buf));
    value = calc_gauge_fill(object);
    count = value;
    pair_test = (s16)value / 2;
    pair_index = 0;
    if (pair_test > 0) {
        marker_page = 0x80090000;
        pair_count = pair_test;
        do {
            strcat(output, (void *)(marker_page - 0x6D1C));
            pair_index++;
        } while (pair_index < pair_count);
    }
    value = count & 1;
    if (value) {
        strcat(output, D_800892E8);
    }
    strcat(output, D_800892EC);
    strcat(output, func_8004E634(0, format_buf));
    return output;
}

/* Return 0 if equal, 3 if left is greater, or 4 if left is less. */
s32 compare_values_to_display_code(s32 left, s32 right) {
    s32 result;

    result = 0;
    if (left != right) {
        result = 3;
        if (left < right) {
            result = 4;
        }
    }
    return result;
}

/* Formats two pairs of stat values with comparison indicators. */
void *format_compared_stat_pairs(void *text, ActorRecord *stats) {
    s32 format_buf[3];
    s32 first_indicator;
    s32 second_indicator;
    Vec3s *prefix;

    prefix = &D_800892F0;
    *(Vec3s *)text = *prefix;
    first_indicator = compare_values_to_display_code(stats->base_attack, stats->current_attack);
    if (first_indicator != 0) {
        strcat(text, stat_text_format_separator);
        strcat(text, func_8004E634(first_indicator, (char *)(&format_buf)));
    }
    strcat(text, D_800892F8);
    func_8004E5A0(stats->current_attack, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, stat_text_format_separator);
    strcat(text, func_8004E634(0, (char *)(&format_buf)));
    strcat(text, D_800892FC);
    second_indicator = compare_values_to_display_code(stats->base_defense, stats->current_defense);
    if (second_indicator != 0) {
        strcat(text, stat_text_format_separator);
        strcat(text, func_8004E634(second_indicator, (char *)(&format_buf)));
    }
    func_8004E5A0(stats->current_defense, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, stat_text_format_separator);
    strcat(text, func_8004E634(0, (char *)(&format_buf)));
    strcat(text, D_800892D8);
    strcat(text, &D_80089304);
    func_8004E5A0(stats->base_attack, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    strcat(text, D_800892FC);
    func_8004E5A0(stats->base_defense, 3, (char *)(&format_buf));
    strcat(text, &format_buf);
    return text;
}

/* Format and display numeric stats and descriptive text. */
void format_and_display_entity_stats(void *stats, void *panels) {
    u8 digits[64];
    u8 text[64];

    memcpy(text, D_80089308, 5);

    func_8004E5A0(((u8 *)stats)[0x11], 2, digits);
    remap_flagged_string_bytes(digits);
    strcat(text, digits);
    strcat(text, D_80089310);
    strcat(text, D_80089318);

    func_8004E5A0(((u8 *)stats)[0x28], 3, digits);
    strcat(text, digits);
    strcat(text, D_8008931C);

    func_8004E5A0(((u8 *)stats)[0x29], 3, digits);
    strcat(text, digits);

    set_storage_entry_text(*(s32 *)((u8 *)panels + 0x10), text, 0, 0x6C, 0x98);
    set_storage_entry_text(*(s32 *)((u8 *)panels + 0x4C), D_80089324, 0, 0x48,
                  0xB8);
    set_storage_entry_text(*(s32 *)((u8 *)panels + 0x14),
                  format_object_value_marker(text, stats), 0, 0x48, 0xC0);
}

/* Collect nonzero record values, including the extra value for the selected record. */
void collect_selected_record_values(s32 *output, EntityRec *record) {
    s32 *write_ptr;
    s32 extra_value;
    s32 first_value;
    s32 second_value;

    write_ptr = output;
    first_value = ((s32)record->unk_4C);
    if (first_value != 0) {
        *write_ptr = first_value;
        write_ptr += 1;
    }
    second_value = (*(s32 *)&record->unk_50);
    if (second_value != 0) {
        *write_ptr = second_value;
        write_ptr += 1;
    }
    if (record == ((s32)primary_actor_record)) {
        extra_value = record->unk_D8;
        if (extra_value != 0) {
            *write_ptr = extra_value;
        }
    }
}

/* Formats a nonzero signed value into text, using default text for zero. */
u8 *format_optional_signed_value(Input *input, u8 *text) {
    s8 value;

    memcpy(text, D_80089304, 4);
    value = input->value;
    if (value != 0) {
        text[0] = value > 0 ? 0x6B : 0x6C;
        func_8004E5A0(input->value >= 0 ? input->value : -input->value,
                      2, text + 1);
        remap_flagged_string_bytes(text);
    }
    return text;
}

/* Populate up to three display rows with entry text and positioned icons. */
void populate_display_rows(s32 source_id, void *display) {
    s32 scratch[10];
    s16 icon_y;
    s32 text_y;
    s32 row_index;
    void **entry_slot;
    void *entry;
    S_800B59A4_1 *entry_info;
    SignedWidgetYView *icon;
    void *row_display;

    row_display = display;
    bzero((void **) &scratch[0], 0xC);
    collect_selected_record_values((void **) &scratch[0], source_id);
    row_index = 0;
    icon_y = 0x66;
    text_y = 0xD8;
    for (; row_index < 3; row_index++) {
        entry_slot = (void **)((s32)(row_index << 2) + (s32)&scratch[0]);
        row_display = (u8 *)display + row_index * 4;
        entry = *entry_slot;
        if (entry == NULL) {
            break;
        }
        set_display_entry_text_and_position((struct S_800B5264_0 *)(((S_800B59A4_0 *)row_display)->unk_18), select_item_data(entry, &scratch[8]), scratch[8], 0x58,
            text_y);
        set_storage_entry_text(((S_800B59A4_0 *)row_display)->unk_24, format_optional_signed_value(*entry_slot, &scratch[4]), 0, 0xA0, text_y);
        entry_info = *entry_slot;
        ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_00 =
            lookup_item_category_mapped_value(entry_info->unk_01, entry_info->unk_00);
        ((S_800B59A4_5 *)(((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04))->unk_08 = -0x30;
        text_y += 0x10;
        icon = ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04;
        icon->unk_0A = icon_y;
        icon_y += 0x10;
    }
}
