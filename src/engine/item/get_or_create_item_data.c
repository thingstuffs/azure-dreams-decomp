#include "common.h"

#include "common.h"
#include "engine/item.h"
#include "sdk/libc.h"

typedef struct ItemRecord {
    s16 f0;
    s16 f1;
    u8 pad0[8];
    void *ptr;
    u8 pad1[4];
} ItemRecord;

typedef struct ItemCategory {
    u8 pad0[0xC];
    ItemRecord *records;
    u8 pad1[4];
} ItemCategory;

extern ItemCategory itemCategoryTable[];
extern void *alloc_item_data_slot(s32 category, s32 item);
extern void *get_item_data_record(s32 category, s32 item);

/* Return existing item data, or allocate, clear, and register it. */
void *get_or_create_item_data(s32 category, s32 item)
{
    void *item_data;
    ItemCategory *categories;
    ItemRecord *records;

    item_data = get_item_data_record(category, item);

    if (item_data == 0) {
        item_data = alloc_item_data_slot(category, item);
        if (item_data != 0) {
            bzero(item_data, 0x13);
            categories = itemCategoryTable;
            records = categories[category].records;
            records[item].ptr = item_data;
        }
    }

    return item_data;
}
