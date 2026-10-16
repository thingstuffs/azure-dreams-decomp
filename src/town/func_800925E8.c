#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"

void townAppendSecondaryListNode(Rec_D_800FE490 *);                            /* extern */


/* Initialize the record, store its two values, and set its state flags. */
void townInitializeTheStoreTwoValuesSetStateFlags(Rec_D_800FE490 *record, s32 value_08, s32 value_0c) {
    townAppendSecondaryListNode(record);
    record->unk_08 = value_08;
    record->unk_0C = value_0c;
    record->unk_15 = 1;
    record->unk_14 = 0;
}
