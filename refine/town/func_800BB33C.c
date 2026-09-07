#include "common.h"

extern u8 D_800D2644[];

/* Clears record flags, then marks records referenced by nonzero indices in the strided list. */
void func_800B8A9C(void) {
    register s32 entryIndex ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    u8 *recordCursor;
    u8 *indexPageCursor;
    u8 *recordBase;
    u8 recordIndex;
    s16 markedFlag;

    entryIndex = 0x42;
    recordCursor = D_800D2644;
    recordCursor += 0x840;
    do {
        *(s16 *)(recordCursor + 0xA) = 0;
        entryIndex--;
        recordCursor -= 0x20;
    } while (entryIndex >= 0);

    entryIndex = 0;
    recordBase = D_800D2644;
    markedFlag = 1;
    indexPageCursor = (u8 *)0x80010000;
    do {
        recordIndex = indexPageCursor[0x33A4];
        if (recordIndex != 0) {
            u8 *record = (u8 *)((recordIndex << 5) + (u32)recordBase);
            *(s16 *)(record + 0xA) = markedFlag;
        }
        entryIndex++;
        indexPageCursor += 2;
    } while (entryIndex < 0x22);
}
