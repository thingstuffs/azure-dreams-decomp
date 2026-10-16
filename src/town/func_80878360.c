#include "common.h"

extern void townShopSetIndexedFlag(s32);
extern void townShopClearIndexedFlag(s32);
extern s32 townShopTestIndexedFlag(s32);

/* Update flag 0x24C based on flags 0x20C and 0x268. */
void townShopUpdateAvailabilityFlag(void) {
    if ((townShopTestIndexedFlag(0x20C) == 0) && (townShopTestIndexedFlag(0x268) == 0)) {
        townShopSetIndexedFlag(0x24C);
        return;
    }
    townShopClearIndexedFlag(0x24C);
}
