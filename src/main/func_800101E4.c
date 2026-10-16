#include "common.h"
#include "shared/object_flags.h"

extern void cardBootReleaseFiveMessageEntries(void *record);
extern s32 D_80028808[4];

// Optionally flags the linked record, processes the global record, and sets status bits.
s32 cardBootCloseMessageDialog(s32 flagLinkedRecord) {
    void *record = &D_80028808[0];
    if (flagLinkedRecord != 0) {
        void *linkedRecord = *(void **)((u8 *) record + 0x14);
        *(u16 *)((u8 *) linkedRecord + 0x1E) |= 0x2000;
    }
    cardBootReleaseFiveMessageEntries(record);
    *(u16 *)((u8 *) record - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    return D_80028808[0];
}
