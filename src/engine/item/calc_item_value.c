#include "common.h"
#include "engine/item.h"
#include "slus/data.h"

/* Returns the selected item value scaled by its category multiplier and adjusted by its callback. */
s32 calc_item_value(u8 *item, s32 use_value1) {
    ItemCategory *category;
    ItemRecord *record;

    category = &itemCategoryTable[item[1]];
    record = &((ItemRecord *)category->records)[item[0]];

    {
        s32 multiplier;
        s32 value;
        s32 (*callback)(s32, void *, void *, void *);

        multiplier = item_value_multipliers[category->multiplier_index];

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
