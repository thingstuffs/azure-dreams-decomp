#include "common.h"

extern s32 townFindFirstEnabledEntryId(void);
extern s32 townCheckEventValueInList(s32);

/* Return the candidate if townCheckEventValueInList succeeds, otherwise use townFindFirstEnabledEntryId. */
s32 townChooseValidEntryOrFallback(s32 candidate) {
    if (townCheckEventValueInList(candidate) != 0) {
        return candidate;
    }
    return townFindFirstEnabledEntryId();
}
