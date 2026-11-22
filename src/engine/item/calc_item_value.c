#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "engine/item.h"
#include "slus/data.h"

/* Returns the selected item value scaled by its category multiplier and adjusted by its callback. */
s32 calc_item_value(DungeonItemEntry *item, s32 use_value1) {
    ItemCategory *category;
    ItemRecord *record;

    category = &itemCategoryTable[item->kind];
    record = &((ItemRecord *)category->records)[item->unk_00];

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
