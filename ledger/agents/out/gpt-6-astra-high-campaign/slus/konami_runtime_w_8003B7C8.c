#include "common.h"

extern s32 func_800B28A0(void);
extern s32 D_800D0728[];
extern u8 D_80010AC4[];

/* Clears the first byte of each 0x54-byte entry using the selected entry count. */
void func_8003B7C8(void) {
    s32 table_index = func_800B28A0();
    volatile s32 *entry_counts = D_800D0728;
    s32 entry_count = entry_counts[table_index];

    if (entry_count > 0) {
        u8 *entry = D_80010AC4;
        s32 entry_index = 0;

        do {
            *entry = 0;
            entry_index++;
            entry += 0x54;
        } while (entry_index < entry_count);
    }
}
