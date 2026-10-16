/* Relink of matched town/func_8046979C; every changed retail word is a paired relocation. */
#define D_80017AC4 D_80017AB8
#define D_80017CE0 D_80017D20
#include "common.h"

extern void townCopyCallbackValueToDestination(s32, s32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AB8[];
extern s32 D_80017D20[];

/* Process the stored value and its offset by 0x14, then return the stored value. */
s32 func_8001A7E8(void) {
    s32 *stored_value = D_80017D20;

    townCopyCallbackValueToDestination(stored_value[0], D_80017AAC);
    townCopyCallbackValueToDestination(stored_value[0] + 0x14, D_80017AB8);
    return stored_value[0];
}
