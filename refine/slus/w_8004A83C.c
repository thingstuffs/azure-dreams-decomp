#include "common.h"

#include "common.h"

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

extern volatile ItemCategory itemCategoryTable[];
extern void bzero(void *ptr, s32 len);
extern void *func_8004A700(s32 category, s32 item);
extern void *func_8004A784(s32 category, s32 item);

/* Return existing item data, or allocate, clear, and register it. */
void *func_8004A83C(s32 category, s32 item)
{
    void *item_data;
    volatile ItemCategory *categories;
    ItemRecord *records;

    item_data = func_8004A784(category, item);

    if (item_data == 0) {
        item_data = func_8004A700(category, item);
        if (item_data != 0) {
            bzero(item_data, 0x13);
            categories = itemCategoryTable;
            records = categories[category].records;
            records[item].ptr = item_data;
        }
    }

    return item_data;
}
