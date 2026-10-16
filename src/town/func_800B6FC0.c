#include "common.h"

extern void townFillTenPagedEntrySlots(s32, void *, s32);

/* Forwards a value and the record's fields to townFillTenPagedEntrySlots. */
void townForwardRecordFieldsToPageLoader(s32 value, u8 **record_ref) {
    u8 *record = *record_ref;
    townFillTenPagedEntrySlots(value, record + 0x2C, *(s32 *)(record + 0x40));
}
