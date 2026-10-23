#include "common.h"
#include "shared/item_ids.h"

#include "common.h"
#include "engine/item.h"

typedef struct S_80042A80_Item
{
    u8 f0;
    u8 f1;
    u8 pad2;
    u8 f3;
}
S_80042A80_Item;
typedef struct S_80042A80_Rec20
{
    u16 f0;
    u8 pad[18];
}
S_80042A80_Rec20;
extern u8 runtime_dispatch_mode_alias[9];
extern S_80042A80_Rec20 *item_category_tables[3];
/* Returns category-dependent item flags when the current mode is 2. */
s32 get_item_category_flags(S_80042A80_Item *item)
{
    ItemCategory *category;
    s32 item_flags;
    u8 kind;
    s32 category_index;
    u16 category_id;
    S_80042A80_Rec20 *records;
    if (runtime_dispatch_mode_alias[0] != 2) {
        return 0;
    }
    kind = item->f1;
    if (kind == ITEM_KIND_BALL) {
        item_flags = ((item_category_tables[0][item->f0].f0 & 0x400) != 0) << 10;
        if (item->f3 & 0x80) {
            item_flags |= 0x80;
        }
        return item_flags;
    }
    if (3 > ((u32) (kind - ITEM_KIND_SWORD))) {
        return item->f3 & 0x80;
    }
    {
        ItemCategory *categories = itemCategoryTable;
        category_id = item->f1;
        category = &categories[category_id];
    }
    if (category->record_format != 0) {
        return 0;
    }
    records = category->records;
    category_index = records[item->f0].f0;
    category_index &= 0x400;
    category_index <<= 16;
    category_index >>= 16;
    return category_index;
}
