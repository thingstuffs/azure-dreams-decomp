#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

void populate_item_menu_page_entries(s32, void * *);                 /* extern */
void populate_item_menu_lower_entries(Rec_func_800AF254_arg1 *);                            /* extern */
struct S_800AF674_0; void populate_current_item_menu_page(struct S_800AF674_0 *);                      /* extern */
void update_item_menu_page_bounds();                      /* extern */
void item_menu_no_op();                 /* extern */


/* Run the record update sequence and process its stored value. */
void update_item_menu_record(Rec_func_800AF254_arg1 *record) {
    populate_item_menu_lower_entries(record);
    update_item_menu_page_bounds(record);
    populate_current_item_menu_page((struct S_800AF674_0 *)(record));
    populate_item_menu_page_entries(record->unk_A8.as_s32, (void * *)(record));
    item_menu_no_op(record->unk_A8.as_s32, record);
}
