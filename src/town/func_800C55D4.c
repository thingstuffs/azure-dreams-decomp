/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

void townClearObjectStatusAndDispatchTarget();
s32 townGetFacingSector();


/* Store the value table, apply the selected value to the target, and clear its status byte. */
void townStoreValueTableAndResetTarget(Rec_func_80094268_arg0 *object, Rec_D_80082E80 *target, s32 *value_table) {
    object->unk_78 = value_table;
    townClearObjectStatusAndDispatchTarget(object, target, object->unk_78[townGetFacingSector(object->unk_72.as_s16)], 0);
    target->unk_05.as_s8 = 0;
}
