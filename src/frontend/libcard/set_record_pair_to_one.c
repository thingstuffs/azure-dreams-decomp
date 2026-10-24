#include "common.h"
#include "frontend/libcard.h"


/* Sets both record fields to one. */
void set_record_pair_to_one(CardSlotMenuState *record) {
    record->unk_48 = 1;
    record->unk_4C = 1;
}
