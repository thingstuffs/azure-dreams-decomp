/* Shop window layout (G00610). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3A28, CL:town/func_800B3C30. */
#include "town/shop/shop_window_layout_g00610.h"
#include "town/shop.h"
#include "town/shop/item.h"

/* Initialize UI resources and position five rows of display elements. */
void initialize_shop_window_layout(ShopWindow *ui) {
    s32 lower_y;
    s32 left_y;
    s32 right_y;
    s32 row_offset;
    s32 row;
    void *header;
    ShopWindowWidgets *row_widgets;

    ui->widgets->unk_00->value.pointer = &D_800788E0;
    header = ui->header_record;
    ui->widgets->record_widget->value.pointer = header;
    ui->widgets->record_widget->data->y.s = 0x2F;
    process_shop_record_and_subrecord((s32)(header));
    position_shop_row_widgets(ui);
    initialize_scaled_entry_cursor(ui->cursor_record, (struct S8004CBFC_a1 *)(&shop_cursor_template), (int *)ui->widgets->cursor);
    row = 4;
    lower_y = 0xC8;
    right_y = 0x55;
    left_y = 0x58;
    ui->widgets->unk_0C->value.pointer = &D_800D15F4;
    do {
        row_offset = row * 4;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[0][0]->data->x = -0x50;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[0][0]->data->y.s = left_y;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[1][0]->data->x = 0x56;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[1][0]->data->y.s = right_y;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[2][0]->data->x = 0x3C;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[2][0]->data->y.s = lower_y;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[3][0]->data->x = 0x8C;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[3][0]->data->y.s = lower_y;
        row_widgets = row_offset + (s32)ui->widgets;
        row_widgets->rows[4][0]->data->x = 0x34;
        row -= 1;
        left_y -= 0x10;
        right_y -= 0x10;
        row_offset += (s32)ui->widgets;
        row_widgets = row_offset;
        row_widgets->rows[4][0]->data->y.s = lower_y;
        lower_y -= 0x10;
    } while (row >= 0);
    position_shop_child_elements(ui);
    populate_shop_item_rows(ui);
}

/* Stores the supplied shop subrecord values, enables it, and installs its update callback. */
void initialize_shop_subrecord(void *record_data, s32 value_20, s32 value_08, s32 value_0c, s32 value_10,
                   s32 value_14, s32 value_24, s32 value_18) {
    S_800B1390_1 *r = record_data;
    r->unk_04 = 1;
    r->unk_08 = value_08;
    r->unk_0C = value_0c;
    r->unk_20 = value_20;
    ((S_800B1390_0 *)r)[-1].unk_m10 = D_800B0824;
    r->unk_10 = value_10;
    r->unk_14 = value_14;
    r->unk_24 = value_24;
    r->unk_18 = value_18;
}

/* Configure the object, update its embedded records, and finalize it. */
void configure_shop_object_and_finalize(void *object, s32 setup_value_1, s32 setup_value_2, s32 setup_value_3,
                   s32 setup_value_4, s32 setup_value_5, s32 setup_value_6, s32 setup_value_7) {
    initialize_shop_subrecord(object, setup_value_1, setup_value_2, setup_value_3, setup_value_4, setup_value_5, setup_value_6,
        setup_value_7);
    initialize_shop_parts((u8 *)object + 0xBC, (u8 *)object + 0x94,
                  (u8 *)object + 0xA4);
    initialize_shop_window_layout(object);
}
