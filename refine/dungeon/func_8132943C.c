#include "common.h"

extern void *D_80174CE0[];
extern s32 D_800814A0[3];
extern void func_800A32A4(void *arg0);

// Processes and clears slot zero's entry, setting entry and global status flags.
void func_80170C3C(void) {
    void *entryData;

    entryData = D_80174CE0[0];
    if (entryData != 0) {
        entryData = (u8 *)entryData + 0x20;
        func_800A32A4(entryData);
        *(u16 *)((u8 *)entryData - 2) |= 0x8000;
        D_80174CE0[0] = 0;
        D_800814A0[0] |= 0x8000;
    }
}
