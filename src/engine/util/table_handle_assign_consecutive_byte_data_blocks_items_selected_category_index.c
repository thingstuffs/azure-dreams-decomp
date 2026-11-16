#include "common.h"
#include "shared/resident_resources.h"
#include "engine/item.h"
#include "engine/util.h"

/* {category, index} pair table at raw address 0x80013564 (not referenced
   elsewhere in this TU via a %hi/%lo symbol, so materialized as a literal,
   matching sibling get_item_data_record's treatment of the neighboring 0x800133E8
   table). */


/*
 * Walks 20 category/index pairs at 0x80013564 and assigns successive 0x13-byte blocks starting at
 * 0x800133E8 to records with a nonzero category.
 */
void assign_item_category_data_blocks(void)
{
    ResourceCategoryPair *item_pair = (ResourceCategoryPair *)0x80013564;
    void *item_data = (void *)0x800133E8;
    ItemCategory *category_table;
    s32 pair_index = 0;

    category_table = itemCategoryTable;
    for (; pair_index < 20; pair_index++) {
        if (item_pair->a != 0) {
            ItemRecord *records = category_table[item_pair->a].records;
            records[item_pair->b].data = item_data;
        }
        item_pair++;
        item_data = (u8 *)item_data + 0x13;
    }
}
