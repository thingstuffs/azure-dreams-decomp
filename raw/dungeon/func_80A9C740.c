#include "common.h"
#include "shared/game_work.h"

extern void func_80047784();
extern u8 D_80174C4C[8];

// Initialize object state and apply the table entry for its eight-way orientation.
void func_80171F40(void *object, void *unused, void *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = D_80174C4C;
    *(void **)((u8 *)display + 0x2C) = directionTable;
    directionIndex = ((gameWork.view.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    func_80047784(display, directionTable[directionIndex], 0);
}
