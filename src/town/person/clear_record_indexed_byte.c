#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"
typedef struct S_800C3C28_0 S_800C3C28_0;
void dispatch_status_triggered_handler(s32 object, s32 unused, S_800C3C28_0 *status);

/* Clear the record's indexed byte and set its data pointer. */
void clear_record_indexed_byte(Rec_func_80094268_arg0 *record) {
    D_80082660[record->unk_60].unk_00 = 0;
    record->unk_54 = &dispatch_status_triggered_handler;
}
