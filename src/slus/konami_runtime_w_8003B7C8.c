#include "common.h"

extern s32 func_800B28A0(void);
extern s32 D_800D0728[];

/* Clears the first byte of each 0x54-byte entry using the selected entry count. */
void func_8003B7C8(void) {
    s32 table_index = func_800B28A0();
    s32 entry_count = D_800D0728[table_index];
    s32 entry_index;

    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        s32 offset = entry_index * 0x54;
        *(u8 *)(offset + 0x80010AC4) = 0;
    }
}
