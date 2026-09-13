#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;

/* Counts active entries whose first two key bytes match the given values. */
s16 func_800A6E10(s16 first_key, s16 second_key) {
    M2C_UNK *status_entry;
    M2C_UNK *key_entry;
    s16 match_count;
    s32 entry_index;
    s32 match_first;
    s32 match_second;
    s8 zero;

    zero = 0;
    match_count = zero;
    entry_index = zero;
    match_first = first_key;
    match_second = second_key;
#ifdef NON_MATCHING
    key_entry = &D_800E36C8;
    status_entry = &D_800E3548;
#else
    key_entry = &D_800E36C8;
    status_entry = &D_800E3548;
#endif
    do {
        if ((*((u8 *) status_entry + 1) != 0) && (*((u8 *) key_entry) == match_first) && (*((u8 *) key_entry + 1) == match_second)) {
            match_count += 1;
        }
        key_entry += 3;
        entry_index += 1;
        status_entry += 1;
    } while (entry_index < 0x40);
    return match_count;
}
