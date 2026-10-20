#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0FD4_2 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x24];
    s32 * unk_38;
    u8 pad_3C[0x10];
    s32 * unk_4C;
    u8 pad_50[0x10];
    s32 * unk_60;
} S_800B0FD4_2;


s32 get_item_sell_money();                             /* extern */
s32 get_item_buy_money();                         /* extern */
s32 lookup_item_category_mapped_value();                          /* extern */
s32 select_item_data();                      /* extern */
s32 func_8004DC14();                        /* extern */
char *func_8004E5A0();     /* extern */
u8 *remap_flagged_string_bytes();                   /* extern */
s32 func_8004E928();              /* extern */
char *strcat();        /* extern */
void update_current_shop_page();                      /* extern */
void update_shop_state_flags();                      /* extern */
s32 allocate_and_initialize_shop_object();                             /* extern */
s32 check_shop_entry_type_and_flags();                             /* extern */
void reset_five_shop_slots(void *);                            /* extern */
extern M2C_UNK D_800D1600;

typedef struct S_800B0FD4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
    u8 pad_28[0xA4];
    s32 unk_CC;
} S_800B0FD4_0;   /* ctx in populate_shop_item_rows */

typedef struct S_800B0FD4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B0FD4_1;

/* Populate up to five shop item rows with item details and buy or sell prices. */
void populate_shop_item_rows(S_800B0FD4_0 *ctx) {
    s32 price_text[8];
    s32 item_info;
    s32 item_value;
    s32 page;
    s32 item_offset;
    s32 row_offset;
    s32 item_index;
    s32 row;
    S_800B0FD4_1 *item;

    reset_five_shop_slots(ctx);
    row = 0;
    page = ctx->unk_10;
    row_offset = 0;
    item_index = page * 5;
    item_offset = page * 0x14;
    while (row < 5 && item_index < ctx->unk_0C) {
        item = item_offset + ctx->unk_24;
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_10 = lookup_item_category_mapped_value(item->unk_01, item->unk_00);
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_38 =
            func_8004DC14(select_item_data(ctx->unk_24 + item_offset, &item_info), item_info);
        if (check_shop_entry_type_and_flags(ctx->unk_24 + item_offset) != 0) {
            if (ctx->unk_18 == 0) {
                item_value = get_item_buy_money(ctx->unk_24 + item_offset);
            } else {
                item_value = get_item_sell_money(ctx->unk_24 + item_offset);
            }
            func_8004E5A0(item_value, 8, &price_text);
            remap_flagged_string_bytes(&price_text);
            strcat(&price_text, &D_800D1600);
            *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_4C = func_8004E928(&price_text, 0);
        }
        row += 1;
        item_index += 1;
        item_value = allocate_and_initialize_shop_object(ctx->unk_24 + item_offset);
        item_offset += 4;
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_60 = item_value;
        row_offset += 4;
    }
    update_shop_state_flags(ctx);
    update_current_shop_page(ctx);
}
