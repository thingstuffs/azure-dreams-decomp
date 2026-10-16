#include "common.h"
#include "m2c_compat.h"

void townCopyCallbackValueToDestination();        /* extern */
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017F08;

/* Process two locations in the data block and return its base address. */
M2C_UNK *townBuildTwoRecordValueBlock(void) {
    townCopyCallbackValueToDestination(&D_80017F08, &D_80017B0C);
    townCopyCallbackValueToDestination(&D_80017F08 + 0x14, &D_80017B18);
    return &D_80017F08;
}
