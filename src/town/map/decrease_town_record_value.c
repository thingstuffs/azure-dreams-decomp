#include "common.h"

#include "town/map/body.h"

/* Decrease the record value by 0x100, clamp at -0x400, and handle the lower limit. */
void decrease_town_record_value(TownMapBody *body) {
    Rec_D_80081FDC *record;
    Rec_D_80081FDC *first_record;
    u16 value;

    first_record = body->context;
    value = first_record->unk_0A;
    value -= 0x100;
    first_record->unk_0A = value;
    record = body->context;
    if (record->unk_0A < -0x400) {
        record->unk_0A = -0x400;
        release_town_map_record(body);
    }
}
