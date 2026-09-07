#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

// Process the source and set destination and global flags when source status bits are set.
void func_80174A00(void *destination, s32 unused, void *source)
{
    func_800478B8(source);
    if (*(u16 *)((u8 *)source + 0x14) & 0x6000) {
        *(u16 *)((u8 *)destination - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
