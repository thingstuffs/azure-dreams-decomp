#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B2DA0_arg1.h"

void townForwardPagedRecordData();                 /* extern */
void townUpdateLinkedRecordData(Rec_func_800B2DA0_arg1 *);                            /* extern */
void townPrepareLinkedRecordData();                      /* extern */
M2C_UNK func_800B336C();                      /* extern */


/* Update the linked record components and finalize the data at offset 0x68. */
void townUpdateAndFinalizeRecord(Rec_func_800B2DA0_arg1 *record) {
    townUpdateLinkedRecordData(record);
    func_800B336C(record);
    townPrepareLinkedRecordData(record);
    townForwardPagedRecordData(record->unk_A8 + 0x68, record);
}
