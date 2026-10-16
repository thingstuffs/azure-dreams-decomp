#include "common.h"

extern s32 townSumFlaggedEntryValues(u8 *entry, s32 mode);
extern s32 D_80082AB8;

/* Store whether the record check returns a nonzero result. */
void townStoreRecordCheckResult(void *record) {
    if (townSumFlaggedEntryValues(*(s32 *)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        D_80082AB8 = 1;
        return;
    }
    D_80082AB8 = 0;
}
