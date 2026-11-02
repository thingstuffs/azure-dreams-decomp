/* Refreshes catalog grid entries and positions the selection sprite using row and column indices. */
#include "common.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/catalog.h"
#include "town/menu.h"
#include "town/data.h"

extern void *D_80126998[4];
extern void *catalog_normal_digits[10];
extern u16 catalog_cursor_rows[2];
extern u16 catalog_cursor_columns[8];
extern u8 catalog_number_marker[16];
extern u8 D_80127E4C[16];
extern u8 D_80127F48[16];
extern u8 D_801289EC[16];

/* Returns eight times the signed row plus the entry index. */
static __inline__ s32 menu_row_index(s16 row, s16 index)
{
    return (row << 3) + index;
}

/* Updates the numbered menu entries and selection sprite. */
void refresh_catalog_entry_grid(CatalogDisplay *menu)
{
    s32 sprite_slot;
    CatalogDisplay *obj = menu;
    s16 entry_number;
    s32 entry_index;
    s16 entry_id;
    void **normal_digits;
    void **selected_digits;
    s16 digit_base;
    s32 blank_count;
    CatalogCursorPosition *display_sprite;

    draw_catalog_entry_page(menu);
    obj->parts.table->entries[28]->handler = D_80127E4C;
    obj->parts.table->entries[29]->handler = D_80127F48;
    obj->parts.table->entries[30]->handler = catalog_detail_pages[obj->unk_0F];
    obj->parts.table->entries[31]->handler = D_80126998[obj->unk_0F];
    obj->parts.table->entries[32]->handler = D_801289EC;

    if (obj->unk_0F == 3) {
        sprite_slot = 33;
        entry_index = 0;
        selected_digits = catalog_selected_digits;
        digit_base = obj->unk_0F << 4;
        normal_digits = catalog_normal_digits;
        entry_id = digit_base;
        entry_number = digit_base | 1;
        do {
            if (is_catalog_entry_available((u8)entry_id) != 0) {
                obj->parts.table->entries[sprite_slot++]->handler = catalog_number_marker;
                if (entry_index == obj->unk_10) {
                    obj->parts.table->entries[sprite_slot]->handler = selected_digits[entry_number / 10];
                    sprite_slot++;
                    obj->parts.table->entries[sprite_slot++]->handler = selected_digits[entry_number % 10];
                } else {
                    obj->parts.table->entries[sprite_slot]->handler = normal_digits[entry_number / 10];
                    sprite_slot++;
                    obj->parts.table->entries[sprite_slot++]->handler = normal_digits[entry_number % 10];
                }
            } else {
                obj->parts.table->entries[sprite_slot++]->handler = catalog_unavailable_marker;
                obj->parts.table->entries[sprite_slot++]->handler = 0;
                obj->parts.table->entries[sprite_slot++]->handler = 0;
            }

            blank_count = 0;
            do {
                obj->parts.table->entries[sprite_slot++]->handler = 0;
                blank_count++;
            } while (blank_count < 21);
            entry_index++;
            entry_id++;
            entry_number++;
        } while (entry_index < 2);

        obj->parts.table->cursor->position->x = catalog_cursor_rows[obj->unk_10];
        obj->parts.table->cursor->position->y = catalog_cursor_columns[0];
        if (obj->unk_10 != 0) {
            obj->parts.table->entries[30]->handler = catalog_detail_fallback;
        }
    } else {
        sprite_slot = 33;
        entry_index = 0;
        selected_digits = catalog_selected_digits;
        digit_base = obj->unk_0F << 4;
        normal_digits = catalog_normal_digits;
        entry_id = digit_base;
        entry_number = digit_base | 1;
        do {
            if (is_catalog_entry_available((u8)entry_id) != 0) {
                obj->parts.table->entries[sprite_slot++]->handler = catalog_number_marker;
                if (entry_index == menu_row_index(obj->unk_10, obj->unk_11)) {
                    obj->parts.table->entries[sprite_slot]->handler = selected_digits[entry_number / 10];
                    sprite_slot++;
                    obj->parts.table->entries[sprite_slot++]->handler = selected_digits[entry_number % 10];
                } else {
                    obj->parts.table->entries[sprite_slot]->handler = normal_digits[entry_number / 10];
                    sprite_slot++;
                    obj->parts.table->entries[sprite_slot++]->handler = normal_digits[entry_number % 10];
                }
            } else {
                obj->parts.table->entries[sprite_slot++]->handler = catalog_unavailable_marker;
                obj->parts.table->entries[sprite_slot++]->handler = 0;
                obj->parts.table->entries[sprite_slot++]->handler = 0;
            }

            entry_index++;
            entry_id++;
            entry_number++;
        } while (entry_index < 16);

        obj->parts.table->cursor->position->x = catalog_cursor_rows[obj->unk_10];
        obj->parts.table->cursor->position->y = catalog_cursor_columns[obj->unk_11];
    }

    display_sprite = obj->parts.table->cursor->position;
    display_sprite->scale_y = 0x1000;
    display_sprite->scale_x = 0x1000;
}
