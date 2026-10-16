#include "shared/town_event_state.h"
#include "common.h"

typedef unsigned long uptr;

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

extern s32 townBuildSelectedEntryOutput(s32);

/* Update the selected object record when the current state is 1. */
s32 townStoreValueInState1Record(TownObject *object, s32 record_index) {
    if (D_8001E950->unk_05 == 1) {
        *(s32 *)((record_index * 0x10) + (uptr)object->records + 8) =
            townBuildSelectedEntryOutput(0);
        return 0;
    }
    return 1;
}
