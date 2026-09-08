#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800478B8();                      /* extern */


/* Advances the counter, increments both fields for the first eight steps, and updates the record. */
void func_80DE6A54(u16 *counter, M2C_UNK unused, Rec_D_80082E80 *record) {
    u16 step;
    u16 field_value;

    step = *counter + 1;
    *counter = step;
    if ((s16) step < 9) {
        field_value = record->unk_1C.at02_u16.v + 0x100;
        record->unk_1C.at02_u16.v = field_value;
        record->unk_1C.at00_u16.v = field_value;
    }
    func_800478B8(record);
}
