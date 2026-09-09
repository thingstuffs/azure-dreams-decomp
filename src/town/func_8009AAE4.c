#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80098928();        /* extern */


/* Move the record value toward 0x4C2 by four and invoke completion handlers on arrival. */
void func_80098244(s32 context_id, Rec_D_800E3D7C *record, M2C_UNK context) {
    s16 raised_value;
    s16 lowered_value;
    u16 current_value;

    current_value = (u16) record->unk_00.at02_s16.v;
    if (record->unk_00.at02_s16.v < 0x4C2) {
        raised_value = current_value + 4;
        record->unk_00.at02_s16.v = raised_value;
        if (raised_value >= 0x4C2) {
            goto target_reached;
        }
        return;
    }
    lowered_value = current_value - 4;
    record->unk_00.at02_s16.v = lowered_value;
    if (lowered_value < 0x4C3) {
target_reached:
        record->unk_00.at02_s16.v = 0x4C2;
        func_80033AA8(0x12);
        func_80098928(context_id, record, context);
    }
}
