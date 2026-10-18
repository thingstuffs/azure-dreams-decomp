#include "common.h"

extern u8 D_80081484[];
extern u8 D_80081470[];
s16 find_table_entry_address_index();

// Returns a one-based lookup index, a special code for known data addresses, or zero.
s32 get_special_table_data_index(s32 dataAddress) {
    s32 lookupIndex;

    lookupIndex = (s16)find_table_entry_address_index();
    if (lookupIndex >= 0) {
        lookupIndex++;
        return (s16)lookupIndex;
    }
    if (dataAddress == D_80081484) {
        return 0x15;
    }
    if (dataAddress == D_80081470) {
        return 0x16;
    }
    return 0;
}
