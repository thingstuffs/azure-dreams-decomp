#include "common.h"

// Initializes two consecutive buffer records and returns the end pointer.
void *func_8001D7B0(u8 *record) {
    s32 wordAtOffset8;
    s32 wordAtOffset4;
    s32 wordAtOffsetC;
    void *end;

    *(record + 1) = 0xB0;
    wordAtOffset8 = *(s32 *)0x80408CC4;
    *(s32 *)(record + 8) = wordAtOffset8;
    wordAtOffset4 = *(s32 *)0x80408CCC;
    wordAtOffsetC = *(s32 *)0x80408CC8;
    *(record + 1) = *(record + 1) | 2;
    *(s32 *)(record + 4) = wordAtOffset4;
    *(s32 *)(record + 0xC) = wordAtOffsetC;
    record = record + 24;
    *(record + 1) = 0x81;
    *(s16 *)(record + 4) = 0x20;
    end = record + 0xC;
    *(s16 *)(record + 6) = 0;
    *record = *record | 0x80;
    return end;
}
