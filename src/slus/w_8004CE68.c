#include "common.h"

/* Sets or clears status bit 0x2 in each variable-size record through the end marker. */
void func_8004CE68(u8 *record, s32 setStatusBit) {
    u8 *nextRecord = record;
    u8 recordFlags;

    if (record == 0) {
        return;
    }
    do {
        record = nextRecord;
        if (setStatusBit != 0) {
            recordFlags = record[1];
            recordFlags |= 2;
        } else {
            recordFlags = record[1];
            recordFlags &= 0xFD;
        }
        record[1] = recordFlags;
        recordFlags = *(volatile u8 *)(record + 1);
        recordFlags &= 0xFC;
        if (recordFlags == 0x38) {
            nextRecord = record + 0x18;
        } else {
            nextRecord = record + 0xC;
        }
    } while ((record[0] & 0x80) == 0);
}
