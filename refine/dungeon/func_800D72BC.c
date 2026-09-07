#include "common.h"
#include "m2c_compat.h"



typedef s8 M2C_UNK8;

typedef struct S_800DCA1C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800DCA1C_0;   /* ((*var_a1 * 0x10) + arg0) in func_800DCA1C */


extern u8 D_800E2954;
extern u8 D_800E2960[];


/* Links entries backward in the selected index order and returns the last entry's address. */
s32 func_800DCA1C(s32 entriesBase, s32 useAlternateOrder) {
    s32 previousEntryAddress;
    u8 *indexCursor;
    u8 *indexOrder;
    u8 entryIndex;

    previousEntryAddress = 0;
    if (useAlternateOrder != 0) {
        indexOrder = D_800E2960;
    } else {
        indexOrder = &D_800E2954;
    }
    if (*indexOrder < 9U) {
        indexCursor = indexOrder;
        do {
            ((S_800DCA1C_0 *)(((*indexCursor * 0x10) + entriesBase)))->unk_0C = previousEntryAddress;
            entryIndex = *indexCursor;
            indexCursor += 1;
            previousEntryAddress = entriesBase + (entryIndex * 0x10);
        } while ((u8) *indexCursor < 9U);
    }
    return previousEntryAddress;
}
