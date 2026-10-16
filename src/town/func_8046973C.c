#include "common.h"

extern void townCopyCallbackValueToDestination(s32, u32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AB8[];
extern s32 D_80017AC4[];
extern s32 D_80017CA0[];

/* Apply three value tables to consecutive destinations and return their base. */
s32 townBuildThreeValueBlock(void) {
    s32 *base_ptr = D_80017CA0;

    townCopyCallbackValueToDestination(base_ptr[0], D_80017AAC);
    townCopyCallbackValueToDestination(base_ptr[0] + 0x14, D_80017AB8);
    townCopyCallbackValueToDestination(base_ptr[0] + 0x28, D_80017AC4);
    return base_ptr[0];
}
