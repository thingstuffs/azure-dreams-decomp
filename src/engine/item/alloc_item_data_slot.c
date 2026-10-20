#include "common.h"
#include "shared/resident_resources.h"


typedef struct {
    char unk[0x13];
} S_800133E8;

extern s32 find_item_data_slot(s32 a0, s32 a1);

/* Stores two values in the selected slot and returns the corresponding record. */
S_800133E8 *alloc_item_data_slot(s16 first_value, s16 second_value)
{
    S_800133E8 *record = 0;
    s32 slot = find_item_data_slot(0, 0);

    if (slot < 0x14) {
        s32 offset = slot * sizeof(ResourceCategoryPair);

        record = (S_800133E8 *)0x800133E8 + slot;
        ((ResourceCategoryPair *)(offset + 0x80013564))->a = first_value;
        ((ResourceCategoryPair *)(offset + 0x80013564))->b = second_value;
    }

    return record;
}
