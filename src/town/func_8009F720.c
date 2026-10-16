#include "modules/town_town_windows.h"

/* Runs townBuildEntryListAndProcessItems followed by townRunDualContextCallbacks. */
void townBuildEntriesAndUpdateState(void) {
    townBuildEntryListAndProcessItems();
    townRunDualContextCallbacks();
}
