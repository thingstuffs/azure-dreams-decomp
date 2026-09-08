#include "common.h"

/* Removes an entry by shifting subsequent entries down and clearing the final slot. */
void func_800A86DC(s32 entry_index) {
    u8 *ptr = (u8 *)0x80010000;

    if (entry_index < 19) {
        ptr += entry_index * 4;
        do {
            ASM_KEEP(ptr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            entry_index++;
            *(s32 *)(ptr + 0x29C) = *(s32 *)(ptr + 0x2A0);
            ptr += 4;
        } while (entry_index < 19);
    }
    {
        u8 *page = (u8 *)0x80010000;
        s32 entry_offset;

        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        entry_offset = entry_index * 4;
        *(s32 *)(entry_offset + (u32)page + 0x29C) = 0;
    }
}
