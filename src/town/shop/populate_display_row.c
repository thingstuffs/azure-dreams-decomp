#include "common.h"

typedef struct S_800B61C0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x8];
    s32 unk_2C;
    u8 pad_30[0x8];
    void * unk_38;
} S_800B61C0_0;

typedef struct S_800B61C0_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B61C0_1;   /* arg0 in populate_display_row */

typedef struct S_800B61C0_2 {
    s32 unk_00;
    void * unk_04;
} S_800B61C0_2;

typedef struct S_800B61C0_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B61C0_3;


s32 lookup_item_category_mapped_value(s32, s32);
extern s32 select_item_data();
extern s32 set_display_entry_text_and_position();
extern s32 set_storage_entry_text();
extern u8 * format_optional_signed_value();


/* Populate and position a display row from an entry. */
void populate_display_row(S_800B61C0_1 *entry, s32 widgets_base, s32 row)
{
    s32 detail_info[4];
    s32 entry_info[2];
    s32 row_offset;
    s32 text_y;
    s32 entry_value;
    s32 *info_out;
    S_800B61C0_0 *widgets;

    info_out = entry_info;
    entry_value = select_item_data(entry, info_out);
    row_offset = row * 0x10;
    text_y = row_offset + 0xD8;
    widgets = (void *)(row * 4 + widgets_base);
    set_display_entry_text_and_position(widgets->unk_20, entry_value, entry_info[0], 0x58, text_y);
    set_storage_entry_text(widgets->unk_2C,
                  format_optional_signed_value(entry, detail_info), 0, 0xA0, text_y);
    ((S_800B61C0_2 *)(widgets->unk_38))->unk_00 = lookup_item_category_mapped_value(
        entry->unk_01, entry->unk_00);
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(widgets->unk_38))->unk_04))->unk_08 = -0x30;
    ((S_800B61C0_3 *)(((S_800B61C0_2 *)(widgets->unk_38))->unk_04))->unk_0A =
        (s16)(row_offset + 0x66);
}

/* MECHANISM: Sibling detail_info/entry_info arrays produce the retail 0x48 frame; keeping the
   entry_info pointer live hoists sp+0x28 and lets the $s2 save fill the first jal slot. */
