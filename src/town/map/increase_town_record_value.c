#include "common.h"

#include "town/map/body.h"

/* Increase the record value by 0x200, clamp at 0x800, and handle the upper limit. */
void increase_town_record_value(TownMapBody *body) {
    Rec_D_80081FDC *record;
    Rec_D_80081FDC *first_record;
    u16 value;

    first_record = body->context;
    value = first_record->unk_0A;
    value += 0x200;
    first_record->unk_0A = value;
    record = body->context;
    if (record->unk_0A >= 0x801) {
        record->unk_0A = 0x800;
        release_town_map_record(body);
    }
}

/* MECHANISM: A block-scoped first record is held in v0 while its explicit u16
   value occupies v1; the independent clamp reload is held in v1 across the
   signed test and call-delay-slot store. */
