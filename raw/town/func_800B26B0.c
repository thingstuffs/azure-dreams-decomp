#include "common.h"

extern u8 D_800891F8[0x29];
extern void func_800491F4(s32, void *, s32);

typedef struct CopyData {
    u32 words[10];
    u8 tail;
} CopyData;

void func_800AFE10(s32 arg0)
{
    CopyData copy;

    __builtin_memcpy(&copy, D_800891F8, 0x29);
    func_800491F4(arg0, &copy, 0x28);
}

/* MECHANISM: The true-space definition makes 0x800AFEB8 a compiler-generated local copy join.
   A word-aligned stack record plus a 41-byte builtin copy yields the 0x48 frame and both copy loops.
   The cdk-G0 lineage emits retail's split global address, $t1 argument hold, and dispatch schedule. */
