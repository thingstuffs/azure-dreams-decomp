#include "common.h"

// Initializes two adjacent records with global values and fixed fields, returning the end pointer.
void *func_8001D818(u8 *record) {
    s32 recordWord8;
    s32 recordWord4;
    s32 recordWordC;
    void *end;

    *(record + 1) = 0xB0;
    recordWord8 = *(s32 *)0x80408CD0;
    *(s32 *)(record + 8) = recordWord8;
    recordWord4 = *(s32 *)0x80408CD8;
    recordWordC = *(s32 *)0x80408CD4;
    *(record + 1) = *(record + 1) | 2;
    *record = *record | 0x40;
    *(s32 *)(record + 4) = recordWord4;
    *(s32 *)(record + 0xC) = recordWordC;
    record = record + 24;
    *(record + 1) = 0x81;
    *(s16 *)(record + 4) = 0x20;
    end = record + 0xC;
    *(s16 *)(record + 6) = 0;
    *record = *record | 0x80;
    return end;
}
