#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern void D_800C3BF4();


/* Clear the record's indexed flag and set its state pointer. */
void clear_record_indexed_flag(Rec_func_80094268_arg0 *record) {
    object_index_slots[record->unk_60].unk_00 = 0;
    record->unk_54 = &D_800C3BF4;
}
