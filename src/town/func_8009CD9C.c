#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"



extern M2C_UNK func_80033CD8();
extern void townInitializeRecordWithHandlerTable();
extern M2C_UNK D_800970FC;


/* Processes the object, clears its indexed flag, and invokes the next handler. */
void townProcessPlayerMotionState(Rec_func_80094268_arg0 *object, M2C_UNK forwardedArg1, M2C_UNK forwardedArg2) {
    func_80033CD8(object, &D_800970FC);
    D_80082660[object->unk_40].unk_00 = 0;
    townInitializeRecordWithHandlerTable(object, forwardedArg1, forwardedArg2);
}
