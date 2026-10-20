#include "script_symbols.h"
#include "common.h"

#include "common.h"

extern void set_resident_bits_for_matching_key(s16 entry_index);
extern s32 test_resident_bitmap_bit(s32 bit_id);

extern s32 message_control_string_table[];
extern s32 resident_bitmap_special_value[];
extern s32 resident_bitmap_words[];
extern s32 D_80080A50[];

/* Updates the selected entry and returns its value, applying special-case lookups. */
s32 select_resident_resource_table_value(s32 entry_index) {
    set_resident_bits_for_matching_key((s16)entry_index);

    if (entry_index == 1) {
        return message_control_string_table[0];
    }

    if (entry_index == 2) {
        return resident_bitmap_special_value[0];
    }

    if (entry_index == 10 && test_resident_bitmap_bit(Ft_mia_new) == 0) {
        return D_80080A50[0];
    }

    return resident_bitmap_words[entry_index];
}
