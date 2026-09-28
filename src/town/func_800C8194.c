#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern M2C_UNK D_800C3BF4;


/* Clear the record's indexed flag and set its state pointer. */
void func_800C58F4(Rec_func_80094268_arg0 *record) {
    D_80082660[record->unk_60].unk_00 = 0;
    record->unk_54 = &D_800C3BF4;
}
