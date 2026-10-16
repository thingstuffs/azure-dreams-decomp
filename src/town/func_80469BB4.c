#include "common.h"
#include "m2c_compat.h"

void townCopyCallbackValueToDestination();        /* extern */
extern u8 D_80017AF4;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017F44;

/* Apply three value tables to consecutive global destinations and return their base. */
M2C_UNK *townBuildThreeRecordValueBlock(void) {
    townCopyCallbackValueToDestination(&D_80017F44, &D_80017AF4);
    townCopyCallbackValueToDestination(&D_80017F44 + 0x14, &D_80017B0C);
    townCopyCallbackValueToDestination(&D_80017F44 + 0x28, &D_80017B18);
    return &D_80017F44;
}
