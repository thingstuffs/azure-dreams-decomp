#include "common.h"
#include "m2c_compat.h"

M2C_UNK restoreActorStatsFromSnapshot();              /* extern */
M2C_UNK buildEntitySlotSnapshot();              /* extern */
void townResetPersonObjectEntries();                   /* extern */
extern M2C_UNK D_80100A10;

/* Load a record into the shared buffer, process it, and write it back. */
void townLoadASharedBufferProcessWriteBack(s32 record_ref) {
    restoreActorStatsFromSnapshot(&D_80100A10, record_ref);
    townResetPersonObjectEntries(&D_80100A10);
    buildEntitySlotSnapshot(record_ref, &D_80100A10);
}
