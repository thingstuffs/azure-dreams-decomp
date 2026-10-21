#include "common.h"
#include "records/Rec_func_80025030_arg0.h"
#include "frontend/libcard.h"


/* Sets both record fields to one. */
void set_record_pair_to_one(Rec_func_80025030_arg0 *record) {
    record->unk_48 = 1;
    record->unk_4C = 1;
}
