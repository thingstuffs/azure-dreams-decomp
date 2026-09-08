#include "common.h"

/* Sets or clears status bit 0x2 in each variable-size record through the end marker. */
void func_8004CE68(u8 *record, s32 set_status_bit) {
    u8 *next_record = record;
    u8 record_flags;

    if (record == 0) {
        return;
    }
    do {
        record = next_record;
        if (set_status_bit != 0) {
            record_flags = record[1];
            record_flags |= 2;
        } else {
            record_flags = record[1];
            record_flags &= 0xFD;
        }
        record[1] = record_flags;
        record_flags = *(volatile u8 *)(record + 1);
        record_flags &= 0xFC;
        if (record_flags == 0x38) {
            next_record = record + 0x18;
        } else {
            next_record = record + 0xC;
        }
    } while ((record[0] & 0x80) == 0);
}
