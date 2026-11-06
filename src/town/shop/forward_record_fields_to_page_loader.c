#include "common.h"
#include "town/shop.h"

/* Forwards output slots and the record's fields to fill_ten_paged_entry_slots. */
void forward_record_fields_to_page_loader(s32 **outputs, u8 **record_ref) {
    u8 *record = *record_ref;
    fill_ten_paged_entry_slots(outputs, record + 0x2C, *(s32 *)(record + 0x40));
}
