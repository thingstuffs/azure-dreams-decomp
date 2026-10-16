#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void setResidentBitmapBit();                     /* extern */
void townInitializeRecordWithHandlerTable();        /* extern */


/* Move the record value toward 0x4C2 by four and invoke completion handlers on arrival. */
void townRaiseRecordValueToTarget(s32 context_id, EntityRec *record, s32 context) {
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
        setResidentBitmapBit(0x12);
        townInitializeRecordWithHandlerTable(context_id, record, context);
    }
}
