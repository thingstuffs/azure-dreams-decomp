#include "common.h"

extern u8 D_800891F8[0x29];
extern void func_800491F4(s32, void *, s32);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

/* Passes a local copy of D_800891F8 to func_800491F4 for the target. */
void func_800AFE10(s32 target)
{
    CopyData data_copy;

    __builtin_memcpy(&data_copy, D_800891F8, 0x29);
    func_800491F4(target, &data_copy, 0x28);
}
