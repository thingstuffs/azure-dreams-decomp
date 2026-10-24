/* Check development flag test records and require all listed flags. */

#include "common.h"
#include "town/scene/flags/event_checks.h"

typedef struct S_800165E4_0 {
    u8 pad_00[0x10];
    u32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800165E4_0;   /* arg0 in set_one */

typedef struct S_800165E4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_800165E4_1;   /* (void *)entry in set_one */


extern void set_flag_test_indexed_bit();
extern void clear_indexed_flag_unless_identifier();

/* Processes a selected nonzero table value and its owner's parameter if the check succeeds. */
s32 set_one(S_800165E4_0 *tableOwner, s32 entryIndex) {
    u32 entryAddress;
    s16 entryValue;

    do {
        entryIndex *= 0x10;
        entryAddress = entryIndex + tableOwner->unk_10;
    } while (0);
    entryValue = ((S_800165E4_1 *)((void *)entryAddress))->unk_0C;
    if (entryValue != 0 && check_flag_test_record(tableOwner) != 0) {
        set_flag_test_indexed_bit(entryValue);
        clear_indexed_flag_unless_identifier(tableOwner->unk_18);
        return 1;
    }
    return 0;
}

extern s32 select_data_array_based_flag(s16);

/* Check whether every flag in the zero-terminated list is set. */
s32 check_all_flag_test_bits(s16 *flag_ids) {
    s16 *flag_id = flag_ids;

    while (*flag_id != 0) {
        if (select_data_array_based_flag(*(u16 *)flag_id) == 0) {
            break;
        }
        flag_id++;
    }

    return *flag_id == 0;
}
