#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void set_resident_bitmap_bit(s32);                     /* extern */
#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */


/* Move the record value toward 0x4C2 by four and invoke completion handlers on arrival. */
void raise_record_value_to_target(s32 context_id, EntityRec *record, s32 context) {
    s16 raised_value;
    s16 lowered_value;
    u16 current_value;

    current_value = (u16) record->x.w.i;
    if (record->x.w.i < 0x4C2
            ? (raised_value = current_value + 4,
               record->x.w.i = raised_value,
               raised_value >= 0x4C2)
            : (lowered_value = current_value - 4,
               record->x.w.i = lowered_value,
               lowered_value < 0x4C3)) {
        record->x.w.i = 0x4C2;
        set_resident_bitmap_bit(0x12);
        initialize_record_with_handler_table((Struct8009B1C8 *)(context_id), (s32)(record), context);
    }
}
