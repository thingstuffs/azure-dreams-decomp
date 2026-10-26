#include "common.h"
#include "shared/item_ids.h"
#include "shared/dungeon_item_entries.h"

#include "common.h"
#include "engine/item.h"
typedef struct
{
    s16 a;
    s16 b;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
}
S_8004AC3C_Rec20;
typedef struct
{
    s16 a;
    s16 b;
    s32 f4;
    s32 f8;
}
S_8004AC3C_Rec12;
typedef struct
{
    u8 f0;
    u8 pad[0xF];
}
S_80082E6A;
extern S_80082E6A runtime_dispatch_mode_alias;
extern s32 resolve_record_value(DungeonItemEntry *);
/* Select item data by category and state, and report its mode. */
s32 select_item_data(DungeonItemEntry *item, s32 *out_mode)
{
    s32 item_flags;
    ItemCategory *categories;
    ItemCategory *category;
    s32 data_addr;
    u8 kind;
    *out_mode = 0;
    if (runtime_dispatch_mode_alias.f0 != 1) {
        if (item->kind == ITEM_KIND_FAMILIAR) {
            data_addr = resolve_record_value(item) + 0x34;
        }
        else {
            item_flags = get_item_category_flags(item);
            if (item_flags != 0) {
                kind = item->kind;
                if ((((u32) (kind - ITEM_KIND_SWORD)) < 3U) || ((kind == ITEM_KIND_BALL) && ((item_flags & 0x400) == 0))) {
                    data_addr =
                        ((S_8004AC3C_Rec20 *) itemCategoryTable[item->kind].records)[item->unk_00].f4;
                }
                else {
                    data_addr =
                        ((S_8004AC3C_Rec20 *) itemCategoryTable[item->kind].records)[item->unk_00].fC;
                }
                *out_mode = 4;
            }
            else {
                categories = itemCategoryTable;
                category = categories + item->kind;
                data_addr = (category->record_format == 0)
                    ? (((S_8004AC3C_Rec20 *) category->records)[item->unk_00].f4) : (((S_8004AC3C_Rec12 *) category->records)[item->unk_00].f4);
            }
        }
    }
    else
        if (item->kind == ITEM_KIND_FAMILIAR) {
            data_addr = 0x80010324 + ((item->unk_03 & 0x1F) * 0x54);
        }
    else {
        ItemCategory *category_table;
        if (item->kind == 0x16) {
            *out_mode = 7;
        }
        category_table = itemCategoryTable;
        category = category_table + item->kind;
        data_addr = (category->record_format == 0)
            ? (((S_8004AC3C_Rec20 *) category->records)[item->unk_00].f4) : (((S_8004AC3C_Rec12 *) category->records)[item->unk_00].f4);
    }
    return data_addr;
}
