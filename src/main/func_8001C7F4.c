#include "common.h"

extern s32 D_80408C8C;
__asm__(".set D_80408C8C, 0x80408C8C");

extern void func_80051B50(s32 arg0, s32 arg1, s32 arg2);

// Process four entries spaced 0x3C bytes apart using consecutive table values.
void func_8001C7F4(s32 baseAddress) {
    s32 *tableValue;
    s32 entryOffset;
    s32 entryIndex;

    entryIndex = 0;
    tableValue = &D_80408C8C;
    entryOffset = 0x90;
    do {
        func_80051B50(baseAddress + entryOffset, *tableValue, 1);
        tableValue++;
        entryOffset += 0x3C;
        entryIndex++;
    } while (entryIndex < 4);
}
