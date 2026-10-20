#include "common.h"
#include "shared/resident_resources.h"


extern int find_item_data_slot(int first_value, int second_value);
extern void bzero(void *ptr, int len);

/* Clear the selected record and its paired values when the index is below 20. */
void free_item_data_slot(int first_value, int second_value)
{
    s32 record_index = find_item_data_slot(first_value, second_value);

    if (record_index < 0x14) {
        s32 offset = record_index * sizeof(ResourceCategoryPair);

        bzero((void *)(0x800133E8 + record_index * 19), 0x13);
        ((ResourceCategoryPair *)(offset + 0x80013564))->a = 0;
        ((ResourceCategoryPair *)(offset + 0x80013564))->b = 0;
    }
}
