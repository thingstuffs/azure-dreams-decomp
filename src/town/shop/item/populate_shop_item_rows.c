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

struct S_func_800B361C_0; void update_shop_state_flags(struct S_func_800B361C_0 *);                      /* extern */
s32 allocate_and_initialize_shop_object(s32);                             /* extern */
extern M2C_UNK D_800D1600;


typedef struct S_800B0FD4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B0FD4_1;

/* Populate up to five shop item rows with item details and buy or sell prices. */
void populate_shop_item_rows(ShopWindow *ctx) {
    s32 price_text[8];
    s32 item_info;
    s32 item_value;
    s32 page;
    s32 item_offset;
    s32 row_offset;
    s32 item_index;
    s32 row;
    S_800B0FD4_1 *item;
    ShopWindowWidgets *row_widgets;

    reset_five_shop_slots(ctx);
    row = 0;
    page = ctx->page;
    row_offset = 0;
    item_index = page * 5;
    item_offset = page * 0x14;
    while (row < 5 && item_index < ctx->entry_count) {
        item = item_offset + ctx->item_address;
        item_value = lookup_item_category_mapped_value(item->unk_01, item->unk_00);
        row_widgets = row_offset + (s32)ctx->widgets;
        row_widgets->rows[0][0]->value.word = item_value;
        item_value = func_8004DC14(select_item_data(ctx->item_address + item_offset, &item_info), item_info);
        row_widgets = row_offset + (s32)ctx->widgets;
        row_widgets->rows[2][0]->value.word = item_value;
        if (check_shop_entry_type_and_flags((void *)(ctx->item_address + item_offset)) != 0) {
            if (ctx->price_mode == 0) {
                item_value = get_item_buy_money((void *)(ctx->item_address + item_offset));
            } else {
                item_value = get_item_sell_money((void *)(ctx->item_address + item_offset));
            }
            func_8004E5A0(item_value, 8, (char *)(&price_text));
            remap_flagged_string_bytes((u8 *)(&price_text));
            strcat(&price_text, &D_800D1600);
            item_value = func_8004E928(&price_text, 0);
            row_widgets = row_offset + (s32)ctx->widgets;
            row_widgets->rows[3][0]->value.word = item_value;
        }
        row += 1;
        item_index += 1;
        item_value = allocate_and_initialize_shop_object(ctx->item_address + item_offset);
        item_offset += 4;
        row_widgets = row_offset + (s32)ctx->widgets;
        row_widgets->rows[4][0]->value.word = item_value;
        row_offset += 4;
    }
    update_shop_state_flags((struct S_func_800B361C_0 *)(ctx));
    update_current_shop_page(ctx);
}
