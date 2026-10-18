#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B2DA0_arg1.h"

void forward_paged_record_data();                 /* extern */
void update_linked_record_data(Rec_func_800B2DA0_arg1 *);                            /* extern */
void prepare_linked_record_data();                      /* extern */
M2C_UNK func_800B336C();                      /* extern */


/* Update the linked record components and finalize the data at offset 0x68. */
void update_and_finalize_record(Rec_func_800B2DA0_arg1 *record) {
    update_linked_record_data(record);
    func_800B336C(record);
    prepare_linked_record_data(record);
    forward_paged_record_data(record->unk_A8 + 0x68, record);
}
