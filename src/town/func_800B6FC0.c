#include "common.h"

extern void fill_ten_paged_entry_slots(s32, void *, s32);

/* Forwards a value and the record's fields to fill_ten_paged_entry_slots. */
void forward_record_fields_to_page_loader(s32 value, u8 **record_ref) {
    u8 *record = *record_ref;
    fill_ten_paged_entry_slots(value, record + 0x2C, *(s32 *)(record + 0x40));
}
