#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_80701DCE[];
extern TownPair D_80701DFC[];

extern s32 townShopSkipAcceptedEntries(s32 index);
extern void townShopSetEntryStepFlag(s32 index, s32 value);
extern s32 townShopFindFirstEligibleEntry(void);
extern void townShopSetIndexedFlag(u16 value);
extern void townShopClearIndexedFlag(s32 value);
extern s32 townShopTestIndexedFlag(u16 value);

/* Advance the shop entry at `index`: start its 0x1F9 step when eligible, otherwise just clear it. */
s32 townShopAdvanceEntryStep(s32 index) {
    if (townShopTestIndexedFlag(D_80701DCE[0]) == 0 &&
        townShopTestIndexedFlag(0x1F9) != 0) {
        if (townShopSkipAcceptedEntries(index) != 0) {
            townShopSetIndexedFlag(D_80701DFC[index].field_0);
            townShopClearIndexedFlag(0x1F9);
            return townShopFindFirstEligibleEntry();
        }
        townShopSetEntryStepFlag(index, 0);
        return index;
    }
    townShopSetEntryStepFlag(index, 0);
    return index;
}
