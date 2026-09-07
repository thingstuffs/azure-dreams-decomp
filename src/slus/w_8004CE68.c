#include "common.h"

/* Walks a chain of fixed-size sub-records starting at a0: sets/clears status bit
 * 0x2 in byte[1] of each record depending on a1, then advances by +0x18 or +0xC
 * depending on the record's type field (byte[1] & 0xFC == 0x38), stopping when
 * byte[0] & 0x80 is set (or immediately if a0 is NULL). */
void func_8004CE68(u8 *a0, s32 a1) {
    u8 *v1 = a0;
    u8 v0;

    if (a0 == 0) {
        return;
    }
    do {
        a0 = v1;
        if (a1 != 0) {
            v0 = a0[1];
            v0 |= 2;
        } else {
            v0 = a0[1];
            v0 &= 0xFD;
        }
        a0[1] = v0;
        v0 = *(volatile u8 *)(a0 + 1);
        v0 &= 0xFC;
        if (v0 == 0x38) {
            v1 = a0 + 0x18;
        } else {
            v1 = a0 + 0xC;
        }
    } while ((a0[0] & 0x80) == 0);
}
