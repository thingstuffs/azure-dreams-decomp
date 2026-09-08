#include "common.h"

extern void func_800AD4D0(void *arg);

/* Updates the record and clamps the byte at 0x28 to the limit at 0x29. */
void func_800AA754(s32 unused_0, s32 unused_1, s32 unused_2, u8 *record) {
    u8 limit;

    (void)unused_0;
    (void)unused_1;
    (void)unused_2;
    func_800AD4D0(record);
    limit = record[0x29];
    if (limit < record[0x28]) {
        record[0x28] = limit;
    }
}
