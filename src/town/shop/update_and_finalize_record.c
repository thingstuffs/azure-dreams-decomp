#include "common.h"
#include "records/Rec_func_800B2DA0_arg1.h"

void forward_paged_record_data(s32, void * *);                 /* extern */
void update_linked_record_data(Rec_func_800B2DA0_arg1 *);                            /* extern */
struct Rec_func_800B2DA0_arg1; void prepare_linked_record_data(struct Rec_func_800B2DA0_arg1 *);                      /* extern */
s32 func_800B336C(void *);


/* Update the linked record components and finalize the data at offset 0x68. */
void update_and_finalize_record(Rec_func_800B2DA0_arg1 *record) {
    update_linked_record_data(record);
    func_800B336C(record);
    prepare_linked_record_data(record);
    forward_paged_record_data(record->unk_A8 + 0x68, (void * *)(record));
}
