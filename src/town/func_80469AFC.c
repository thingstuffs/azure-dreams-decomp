#include "common.h"
#include "m2c_compat.h"

void townCopyCallbackValueToDestination();        /* extern */
extern u8 D_80017AF4;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern M2C_UNK D_80017B24;
extern u8 D_80017EA4;

/* Initializes four consecutive entries in D_80017EA4 and returns their base address. */
M2C_UNK *townBuildFourRecordValueBlock(void) {
    townCopyCallbackValueToDestination(&D_80017EA4, &D_80017AF4);
    townCopyCallbackValueToDestination(&D_80017EA4 + 0x14, &D_80017B24);
    townCopyCallbackValueToDestination(&D_80017EA4 + 0x28, &D_80017B0C);
    townCopyCallbackValueToDestination(&D_80017EA4 + 0x3C, &D_80017B18);
    return &D_80017EA4;
}
