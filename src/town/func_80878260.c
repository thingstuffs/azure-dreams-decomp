#include "common.h"

extern u8 D_80701DFC[];
extern void townShopAdvanceEntryStep(s32 index);
extern s32 townShopTestIndexedFlag(u16 value);

/* Select the first table entry whose value check returns zero. */
void townShopFindFirstEligibleEntry(void) {
    s32 index = 0;
    s32 offset = 0;

    while (townShopTestIndexedFlag(*(u16 *)&D_80701DFC[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    townShopAdvanceEntryStep(index);
}
