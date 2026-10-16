#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

s32 townGetMonsterStatusTypeData();                             /* extern */
s32 townInvalidateCachedStateAndQueueRead();                      /* extern */
extern M2C_UNK D_800B66E8;


/* Initializes the record, resolves its type data, and runs its setup routine. */
void townInitializeMonsterStatusState(Rec_func_800B683C_arg0 *record, s32 context, s16 type_id) {
    record->unk_08 = type_id;
    record->unk_04 = context;
    record->unk_0C = 0;
    record->unk_0E = 0;
    record->unk_00 = &D_800B66E8;
    record->unk_14 = townGetMonsterStatusTypeData(record->unk_08);
    townInvalidateCachedStateAndQueueRead(record);
}
