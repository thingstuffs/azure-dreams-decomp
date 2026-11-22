#include "common.h"

#include "town/map/body.h"

/* Decrease the record value by 0x200, clamp at -0x800, and handle the lower limit. */
void lower_town_map_record_value(TownMapBody *body) {
    Rec_D_80081FDC *record;
    Rec_D_80081FDC *first_record;
    u16 value;

    first_record = body->context;
    value = first_record->unk_08;
    value -= 0x200;
    first_record->unk_08 = value;
    record = body->context;
    if (record->unk_08 < -0x800) {
        record->unk_08 = -0x800;
        release_town_map_record(body);
    }
}
