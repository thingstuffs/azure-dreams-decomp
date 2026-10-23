#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* Clears the record's unk_94 field. */
void clear_mother_event_record_field(Rec_func_80094268_arg0 *record) {
    record->unk_94 = 0;
}
