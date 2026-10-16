#include "common.h"

extern u8 D_800891F8[0x29];
extern void buildReverseIndexedChain(s32, void *, s32);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

/* Passes a local copy of D_800891F8 to buildReverseIndexedChain for the target. */
void townLinkItemMenuObjectEntries(s32 target)
{
    CopyData data_copy;

    __builtin_memcpy(&data_copy, D_800891F8, 0x29);
    buildReverseIndexedChain(target, &data_copy, 0x28);
}
