#include "common.h"

extern void func_80047784();
extern s16 D_80083208[16];
extern u8 D_8014A000[200000];
#define D_80173C8C_OFF 0x29C8C

// Initialize object state and apply the table entry for its eight-way orientation.
void func_80171D3C(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = &D_8014A000[D_80173C8C_OFF];
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((*(s16 *)((u8 *)D_80083208 + 0x20) + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    func_80047784(display, directionTable[directionIndex], 0);
}
