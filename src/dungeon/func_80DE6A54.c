#include "modules/dungeon_ovl_e0365c.h"

void advance_effect_record_counters(u16 *counter, s32 unused, Rec_D_80082E80 *record) {
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
