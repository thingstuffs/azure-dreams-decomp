#include "shared/town_event_state.h"
#include "common.h"


s32 townPrepareSelectedEntryBuffer();
void func_8001E578();

// Updates the selected entry's value and signals the update when the state is 2.
s32 townStoreSelectedEntryAndDispatch402(void *entryOwner, s32 entryIndex) {
    s32 entryValue;
    s32 entriesBase;

    if (D_8001E950->unk_05 == 2) {
        entryValue = townPrepareSelectedEntryBuffer(D_8001E950->unk_04);
        entriesBase = *(s32 *)((u8 *)entryOwner + 0x10);
        *(s32 *)((entryIndex << 4) + entriesBase + 8) = entryValue;
        func_8001E578(0x402, entriesBase);
        return 0;
    }
    return 1;
}
