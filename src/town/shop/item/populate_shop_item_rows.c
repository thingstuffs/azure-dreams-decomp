#include "common.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "m2c_compat.h"
#include "sdk/libc.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "engine/text.h"
#include "engine/util.h"
#include "slus.h"
#include "town/shop.h"
#include "town/shop/item.h"
#include "town/shop/state.h"

extern M2C_UNK D_800D1600;

/* Populate up to five shop item rows with item details and buy or sell prices. */
void populate_shop_item_rows(ShopWindow *ctx) {
    char price_text[32];
    s32 item_info;
    s32 item_value;
    s32 page;
    s32 item_index;
    s32 row;
    DungeonItemEntry *item;
    void *widget_data;

    reset_five_shop_slots(ctx);
    row = 0;
    page = ctx->page;
    item_index = page * 5;
    while (row < 5 && item_index < ctx->entry_count) {
        item = (DungeonItemEntry *)(item_index * sizeof(*item) + (unsigned long)ctx->items);
        item_value = lookup_item_category_mapped_value(item->kind, item->unk_00);
        ctx->widgets->rows[0][row]->value.word = item_value;
        widget_data = create_label_glyph_entries(select_item_data(&ctx->items[item_index], &item_info), item_info);
        ctx->widgets->rows[2][row]->value.pointer = widget_data;
        if (check_shop_entry_type_and_flags(&ctx->items[item_index]) != 0) {
            if (ctx->price_mode == 0) {
                item_value = get_item_buy_money(&ctx->items[item_index]);
            } else {
                item_value = get_item_sell_money(&ctx->items[item_index]);
            }
            format_int_space_padded(item_value, 8, price_text);
            remap_flagged_string_bytes((u8 *)price_text);
            strcat(price_text, &D_800D1600);
            widget_data = alloc_parsed_string(price_text, 0);
            ctx->widgets->rows[3][row]->value.pointer = widget_data;
        }
        ctx->widgets->rows[4][row]->value.pointer = allocate_and_initialize_shop_object(&ctx->items[item_index]);
        row += 1;
        item_index += 1;
    }
    update_shop_page_edge_flags(ctx);
    update_current_shop_page(ctx);
}
