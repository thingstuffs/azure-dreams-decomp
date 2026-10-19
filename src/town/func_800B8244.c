#include "common.h"
#include "m2c_compat.h"
#include "shared/widget_views.h"

typedef struct S_800B59A4_3 {
    u8 pad_00[0x30];
    void * unk_30;
} S_800B59A4_3;

typedef struct S_800B59A4_4 {
    s32 unk_00;
    void * unk_04;
} S_800B59A4_4;

typedef struct S_800B59A4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B59A4_5;


s32 lookup_item_category_mapped_value();
s32 func_8004AC3C();
M2C_UNK bzero(void **, M2C_UNK);
void set_display_entry_text_and_position();
M2C_UNK func_800B53BC();
void collect_selected_record_values(void **, s32);
s32 format_optional_signed_value();

typedef struct S_800B59A4_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
} S_800B59A4_0;

typedef struct S_800B59A4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B59A4_1;


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
next_row:
    entry_slot = (void **)((s32)(row_index << 2) + (s32)&scratch[0]);
    entry = *entry_slot;
    if (entry != NULL) {
        set_display_entry_text_and_position(((S_800B59A4_0 *)row_display)->unk_18, func_8004AC3C(entry, &scratch[8]), scratch[8], 0x58,
            text_y);
        func_800B53BC(((S_800B59A4_0 *)row_display)->unk_24, format_optional_signed_value(*entry_slot, &scratch[4]), 0, 0xA0, text_y);
        entry_info = *entry_slot;
        row_index += 1;
        ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_00 =
            lookup_item_category_mapped_value(entry_info->unk_01, entry_info->unk_00);
        ((S_800B59A4_5 *)(((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04))->unk_08 = -0x30;
        text_y += 0x10;
        icon = ((S_800B59A4_4 *)(((S_800B59A4_3 *)row_display)->unk_30))->unk_04;
        row_display += 4;
        icon->unk_0A = icon_y;
        icon_y += 0x10;
        if (row_index < 3) {
            goto next_row;
        }
    }
}
