#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80033AA8();                     /* extern */
void func_80098928();        /* extern */


/* Move the record value toward 0x4C2 by four and invoke completion handlers on arrival. */
void func_80098244(s32 context_id, EntityRec *record, s32 context) {
    s16 raised_value;
    s16 lowered_value;
    u16 current_value;

    current_value = (u16) record->x.w.i;
    if (record->x.w.i < 0x4C2) {
        raised_value = current_value + 4;
        record->x.w.i = raised_value;
        if (raised_value >= 0x4C2) {
            goto target_reached;
        }
        return;
    }
    lowered_value = current_value - 4;
    record->x.w.i = lowered_value;
    if (lowered_value < 0x4C3) {
target_reached:
        record->x.w.i = 0x4C2;
        func_80033AA8(0x12);
        func_80098928(context_id, record, context);
    }
}
