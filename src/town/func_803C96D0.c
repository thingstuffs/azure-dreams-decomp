/* Relink of matched town/func_80469664; every changed retail word is a paired relocation. */
#define D_80017BD8 D_80017C14
#include "common.h"

typedef struct Entry {
    u32 value;
    s32 unused[2];
} Entry;

extern Entry D_8001791C[8];
extern s32 D_80017AAC[3];
extern s32 D_80017AB8[3];
extern s32 D_80017C14[13];
extern void townCopyCallbackValueToDestination(void *, void *);

// Prepares and returns the shared buffer using the selected entry's value.
s32 *func_8001A6D0(s32 entryIndex) {
    s32 *sharedBuffer = D_80017C14;

    sharedBuffer[8] = D_8001791C[entryIndex].value;
    townCopyCallbackValueToDestination(sharedBuffer, D_80017AAC);
    townCopyCallbackValueToDestination(sharedBuffer + 5, D_80017AB8);
    return sharedBuffer;
}
