/* Relink of matched dungeon/func_8132943C; every changed retail word is a paired relocation. */
#define D_80174CE0 D_80174CDC
#include "common.h"
#include "shared/object_flags.h"

extern void *D_80174CDC[];
extern void func_800A32A4(void *record);

// Processes and clears slot zero's entry, setting entry and global status flags.
void func_80170CE0(void) {
    void *entryData;

    entryData = D_80174CDC[0];
    if (entryData != 0) {
        entryData = (u8 *)entryData + 0x20;
        func_800A32A4(entryData);
        *(u16 *)((u8 *)entryData - 2) |= 0x8000;
        D_80174CDC[0] = 0;
        objectFlagBlock.flags |= 0x8000;
    }
}
