#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004DA74();           /* extern */
extern s32 D_800282BC;
__asm__(".set D_800282BC, 0x800282BC");

/* Processes three table values with addresses spaced 0x48 bytes apart from base + 0x90. */
void func_8002352C(s32 baseAddress) {
    s32 *tableEntry;
    s32 entryAddress;
    s32 tableValue;
    s32 entryOffset;
    s32 entriesProcessed;

    entriesProcessed = 0;
    tableEntry = &D_800282BC;
    entryOffset = 0x90;
    do {
        tableValue = *tableEntry;
        tableEntry += 1;
        entryAddress = baseAddress + entryOffset;
        entryOffset += 0x48;
        entriesProcessed += 1;
        func_8004DA74(entryAddress, tableValue, 1);
    } while (entriesProcessed < 3);
}
