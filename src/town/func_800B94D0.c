#include "common.h"
#include "m2c_compat.h"

void townProcessObjectDataByMode();                      /* extern */
void townProcessHandledEntryTypes();                         /* extern */
s32 townInvalidateCachedStateAndQueueRead();                      /* extern */

typedef struct S_800B6C30_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0x8E];
    s32 unk_98;
} S_800B6C30_0;   /* temp_s0 in townChangeMonsterStatusDisplayTarget */

/* Updates the embedded object state and runs its associated helpers. */
void townChangeMonsterStatusDisplayTarget(s32 objectAddress, s32 field04Value, s16 field08Value) {
    S_800B6C30_0 *objectState;

    if (objectAddress != 0) {
        objectState = objectAddress + 0x20;
        townProcessHandledEntryTypes(objectState->unk_98);
        objectState->unk_08 = field08Value;
        objectState->unk_04 = field04Value;
        townProcessObjectDataByMode(objectState);
        townInvalidateCachedStateAndQueueRead(objectState);
    }
}
