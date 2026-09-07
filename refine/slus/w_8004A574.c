#include "common.h"

typedef struct ItemRecord {
    u8 pad[0x10];
    u16 value0;
    u16 value1;
} ItemRecord;

typedef struct ItemCategory {
    u8 pad0[3];
    u8 multiplierIndex;
    u8 pad4[4];
    s32 (* volatile callback)(s32, void *, void *, void *);
    ItemRecord *records;
    u8 pad10[4];
} ItemCategory;

extern ItemCategory itemCategoryTable[];
extern s32 D_800713CC[];

/* Returns the selected item value scaled by its category multiplier and adjusted by its callback. */
s32 func_8004A574(u8 *item, s32 use_value1) {
    ItemCategory *category;
    ItemRecord *record;

    category = &itemCategoryTable[item[1]];
    record = &category->records[item[0]];
    asm("" : : "r"(record));

    {
        s32 multiplier;
        s32 value;
        s32 (*callback)(s32, void *, void *, void *);

        multiplier = D_800713CC[category->multiplierIndex];

        if (use_value1 == 0) {
            value = record->value0 * multiplier;
        } else {
            value = record->value1 * multiplier;
        }

        callback = category->callback;
        if (callback != 0) {
            value = callback(value, item, category, record);
        }

        return value;
    }
}
