#include "script_symbols.h"
#include "common.h"

extern void clear_resident_bitmap_bit(s32 flag_id);
extern s16 shop_resident_flag_ids[];

/* Processes the terminated ID list, 54 evenly spaced IDs, and ID 0xD31. */
void clear_resident_bit_patterns(void)
{
    s32 list_index;
    s32 range_index;

    if (shop_resident_flag_ids[0] != 0) {
        list_index = 0;
        do {
            clear_resident_bitmap_bit(shop_resident_flag_ids[list_index]);
            list_index++;
        } while (shop_resident_flag_ids[list_index] != 0);
    }

    range_index = 0;
    do {
        clear_resident_bitmap_bit((0x03F40000 + (range_index * 0x2B0000)) >> 16);
        range_index++;
    } while (range_index < 54);

    clear_resident_bitmap_bit(Ftt_top);
}
