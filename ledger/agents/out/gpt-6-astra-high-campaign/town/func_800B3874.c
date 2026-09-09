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
} S_800B0FD4_2;   /* (var_s2 + ctx->unk_CC) in func_800B0FD4 */


s32 get_item_sell_money();                             /* extern */
M2C_UNK get_item_buy_money();                         /* extern */
s32 func_8004A658();                          /* extern */
s32 func_8004AC3C();                      /* extern */
s32 func_8004DC14();                        /* extern */
M2C_UNK func_8004E5A0();     /* extern */
M2C_UNK func_8004E69C();                   /* extern */
s32 func_8004E928();              /* extern */
M2C_UNK strcat();        /* extern */
M2C_UNK func_800B0BD0();                      /* extern */
M2C_UNK func_800B0D7C();                      /* extern */
s32 func_800B0F30();                             /* extern */
s32 func_800B0F94();                             /* extern */
M2C_UNK func_800B15B8(void *);                            /* extern */
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
} S_800B0FD4_0;   /* ctx in func_800B0FD4 */

typedef struct S_800B0FD4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B0FD4_1;   /* temp_v0 in func_800B0FD4 */

/* Populate up to five shop item rows with item details and buy or sell prices. */
void func_800B0FD4(void *menu) {
    register S_800B0FD4_0 *ctx ASM_REG("$17") = menu;
    M2C_UNK price_text[8];
    s32 item_info;
    s32 item_value;
    s32 page;
    s32 item_offset;
    s32 row_offset;
    s32 item_index;
    s32 row;
    S_800B0FD4_1 *item;

    func_800B15B8(menu);
    row = 0;
    page = ctx->unk_10;
    row_offset = 0;
    item_index = page * 5;
    item_offset = page * 0x14;
next_item:
    if (item_index < ctx->unk_0C) {
        item = item_offset + ctx->unk_24;
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_10 = func_8004A658(item->unk_01, item->unk_00);
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_38 = func_8004DC14(func_8004AC3C(ctx->unk_24 + item_offset, &item_info), item_info);
        if (func_800B0F94(ctx->unk_24 + item_offset) != 0) {
            if (ctx->unk_18 == 0) {
                item_value = get_item_buy_money(ctx->unk_24 + item_offset);
            } else {
                item_value = get_item_sell_money(ctx->unk_24 + item_offset);
            }
            func_8004E5A0(item_value, 8, &price_text);
            func_8004E69C(&price_text);
            strcat(&price_text, &D_800D1600);
            *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_4C = func_8004E928(&price_text, 0);
        }
        row += 1;
        item_index += 1;
        item_value = func_800B0F30(ctx->unk_24 + item_offset);
        item_offset += 4;
        *((S_800B0FD4_2 *)((row_offset + ctx->unk_CC)))->unk_60 = item_value;
        row_offset += 4;
        if (row >= 5) {
            func_800B0D7C(ctx);
            func_800B0BD0(ctx);
            return;
        }
        goto next_item;
    }
    func_800B0D7C(ctx);
    func_800B0BD0(ctx);
}
