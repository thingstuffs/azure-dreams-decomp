#include "common.h"
#include "engine/util.h"
#include "slus.h"
#include "town/shop.h"
#include "town/shop/item.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"

extern u8 menu_leaf_template_6[12];
extern u8 D_80077EF0[12];
extern u8 D_80077EFC[12];

/* Initializes the list display entries and activates the list. */
void initialize_item_menu_list_entries(ItemMenuTransition *list) {
    s16 row_y;
    s16 entry_y;
    s32 row_index;

    list->rows.as_rows->cursor->handler = menu_leaf_template_6;
    row_index = 0;
    list->rows.as_rows->count_display->handler = get_menu_count_template(list->entry_count);
    list->rows.as_rows->count_display->data->y = (s16)((list->entry_count * 8) + 2);
    if (list->entry_count > 0) {
        u8 *row_data_a = D_80077EF0;
        u8 *row_data_b = D_80077EFC;
        entry_y = 0x82;
        row_y = 0xA;
        do {
            void *entry_handle;

            list->rows.as_rows->text[row_index]->data->y = row_y;
            list->rows.as_rows->text[row_index]->handler = &list->row_data;
            list->rows.as_rows->left[row_index]->data->y = row_y;
            list->rows.as_rows->left[row_index]->handler = row_data_a;
            list->rows.as_rows->middle[row_index]->data->y = row_y;
            list->rows.as_rows->middle[row_index]->handler = row_data_b;
            row_y += 0x10;
            entry_handle = create_label_glyph_entries(get_item_menu_table_entry(list->entry_ids[row_index]), 1);
            list->rows.as_rows->right[row_index]->handler = entry_handle;
            list->rows.as_rows->right[row_index]->data->y = entry_y;
            row_index++;
            entry_y += 0x10;
        } while (row_index < list->entry_count);
    }
    list->duration = 1;
    list->progress = 1;
    animate_item_menu_cursor_transition(list);
}
