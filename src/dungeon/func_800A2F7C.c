#include "common.h"

/* Removes an entry by shifting subsequent entries down and clearing the final slot. */
void func_800A86DC(s32 entry_index) {
    u8 *ptr = (u8 *)0x80010000;

    if (entry_index < 19) {
        ptr += entry_index * 4;
        loop_0: {
            entry_index++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        } if (entry_index < 19) goto loop_0;
    }
    {
        u8 *page = (u8 *)0x80010000;
        s32 entry_offset;

        entry_offset = entry_index * 4;
        *(s32 *)(entry_offset + (u32)page + 0x29C) = 0;
    }
}
