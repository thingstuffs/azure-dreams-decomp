#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

extern int func_80049490();
extern void populate_item_menu_page_entries();
extern void update_item_menu_enabled_record(Rec_func_800AF254_arg1 *);
extern void populate_item_menu_lower_entries();
extern void populate_current_item_menu_page();
extern void update_item_menu_page_bounds();
extern void item_menu_no_op();


typedef struct S_800AFFA8_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 * unk_20;
} S_800AFFA8_1;

/* Runs the record handlers, then processes the selected entry. */
void process_item_menu_selected_entry(Rec_func_800AF254_arg1 *record) {
    S_800AFFA8_1 *selection;

    update_item_menu_enabled_record(record);
    populate_item_menu_lower_entries(record);
    populate_current_item_menu_page(record);
    update_item_menu_page_bounds(record);
    populate_item_menu_page_entries(record->unk_A8.as_s32, record);
    item_menu_no_op(record->unk_A8.as_s32, record);
    selection = record->unk_00;
    func_80049490(selection->unk_20[selection->unk_18]);
}
