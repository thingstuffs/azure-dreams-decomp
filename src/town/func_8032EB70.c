#include "common.h"

/* Returns 20 minus the value from townCountShopEntries. */
s32 townGetFreeShopSlotCount(void) {
    return 0x14 - townCountShopEntries();
}
