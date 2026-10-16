/* Relink of matched town/func_800B26B0; every changed retail word is a paired relocation. */
#define D_800891F8 D_8008926C
#include "common.h"

extern u8 D_8008926C[0x29];
extern void buildReverseIndexedChain(s32, void *, s32);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

/* Passes a local copy of D_8008926C to buildReverseIndexedChain for the target. */
void func_800B3598(s32 target)
{
    CopyData data_copy;

    __builtin_memcpy(&data_copy, D_8008926C, 0x29);
    buildReverseIndexedChain(target, &data_copy, 0x28);
}
