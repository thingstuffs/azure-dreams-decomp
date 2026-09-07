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
    u8 *data_page;
    register s32 zero ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    zero = 0;
    ASM_KEEP(zero);   /* MATCH pin: keeps a statement from moving across a call/branch */
    entry_index = zero;
    match_count = zero;
    match_first = first_key;
    match_second = second_key;
#ifdef NON_MATCHING
    key_entry = &D_800E36C8;
    status_entry = &D_800E3548;
#else
    ASM_USE(match_second);   /* MATCH pin: retail schedule: same instructions, different order without it */
    data_page = (u8 *)0x800E0000;
    ASM_KEEP(data_page);   /* MATCH pin: load-bearing for the whole function shape */
    key_entry = (M2C_UNK *)(data_page + 0x36C8);
    data_page = (u8 *)0x800E0000;
    ASM_KEEP(data_page);   /* MATCH pin: load-bearing for the whole function shape */
    status_entry = (M2C_UNK *)(data_page + 0x3548);
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
