/* Recovered retail twin. */
#include "common.h"
#include "town.h"

#include "town/map/body.h"

/* Raises field +8 by 0x200; clamps and releases the town map record once it exceeds 0x800. */
void raise_town_map_record_value(TownMapBody *body) {
    Rec_D_80081FDC *record;
    Rec_D_80081FDC *first_record;
    u16 value;

    first_record = body->context;
    value = first_record->unk_08;
    value += 0x200;
    first_record->unk_08 = value;
    record = body->context;
    if (record->unk_08 > 0x800) {
        record->unk_08 = 0x800;
        release_town_map_record(body);
    }
}
