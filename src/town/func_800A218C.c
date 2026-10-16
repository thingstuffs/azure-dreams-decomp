#include "common.h"

extern s32 townGetIndexAddressInRangeFourByteSlotsN1(void *target_addr, void *slot_addr, s32 slot_count);

/* Set the entry flag and save the returned table index on success. */
s32 townSetTheEntryFlagSaveReturnedTableIndexSuccess(void *entry) {
    s32 entry_index;

    *((u8 *)entry + 3) |= 0x20;
    entry_index = townGetIndexAddressInRangeFourByteSlotsN1(entry, (void *)0x80010248, 0x14);
    if (entry_index != -1) {
        *(s8 *)0x80012D52 = entry_index;
    }
    return entry_index;
}
