#include "common.h"
#include "shared/object_flags.h"

extern void func_80023194(void *arg0);
extern s32 D_80028808[4];

// Optionally flags the linked record, processes the global record, and sets status bits.
s32 func_800231E4(s32 flagLinkedRecord) {
    void *record = &D_80028808[0];
    if (flagLinkedRecord != 0) {
        void *linkedRecord = *(void **)((u8 *) record + 0x14);
        *(u16 *)((u8 *) linkedRecord + 0x1E) |= 0x2000;
    }
    func_80023194(record);
    *(u16 *)((u8 *) record - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    return D_80028808[0];
}
