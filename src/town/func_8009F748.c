#include "modules/town_town_windows.h"

/* Run both update routines on the shared state and clear the global flag. */
void townUpdateSharedStateAndClearFlag(void) {
    void *state = D_80100900;

    townInitAndPublishScriptState(state);
    townProcessZeroTerminatedEntryLists(state);
    D_801007F8[0] = 0;
}
