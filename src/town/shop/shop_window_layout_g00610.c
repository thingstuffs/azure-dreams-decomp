/* Shop window layout (G00610). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3A28, CL:town/func_800B3C30. */
#include "town/shop/shop_window_layout_g00610.h"

/* Initialize UI resources and position five rows of display elements. */
void initialize_shop_window_layout(void *ui) {
    s32 lower_y;
    s32 left_y;
    s32 right_y;
    s32 row_offset;
    s32 row;
    void *header;

    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_00 = &D_800788E0;
    header = ui + 0x34;
    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_04 = header;
    ((SignedWidgetYView *)(((S_800B1188_9 *)(((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_04))->unk_04))->unk_0A =
        0x2F;
    process_shop_record_and_subrecord((s32)(header));
    position_shop_row_widgets(ui);
    initialize_scaled_entry_cursor(ui + 0x28, (struct S8004CBFC_a1 *)(&shop_cursor_template), (int *)(((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_08));
    row = 4;
    lower_y = 0xC8;
    right_y = 0x55;
    left_y = 0x58;
    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_0C = &D_800D15F4;
    do {
        row_offset = row * 4;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_10))->unk_04))->unk_08 = -0x50;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_10))->unk_04))->unk_0A = left_y;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_24))->unk_04))->unk_08 = 0x56;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_24))->unk_04))->unk_0A = right_y;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_38))->unk_04))->unk_08 = 0x3C;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_38))->unk_04))->unk_0A = lower_y;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_4C))->unk_04))->unk_08 = 0x8C;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_4C))->unk_04))->unk_0A = lower_y;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_60))->unk_04))->unk_08 = 0x34;
        row -= 1;
        left_y -= 0x10;
        right_y -= 0x10;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((row_offset
            + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_60))->unk_04))->unk_0A = lower_y;
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
