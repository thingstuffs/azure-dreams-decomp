#include "common.h"

extern s32 D_80083E98[][32];

/* Copies 128 bytes from the source's offset 0x200 into a table entry and marks it active. */
void func_80021DF4(s32 entry_index, void *source) {
    s32 *base;
    s32 *entry;
    s32 *final_base;
    s32 *final_entry;
    s32 initial_offset;
    s32 final_offset;

    base = (s32 *)&D_80083E98;
    initial_offset = entry_index << 7;
    entry = (s32 *)(initial_offset + (s32)base);
    memcpy(entry, (u8 *)source + 0x200, 0x80);
    final_offset = entry_index << 7;
    final_base = (s32 *)&D_80083E98;
    final_entry = (s32 *)((u8 *)final_base + final_offset);
    final_entry[0] = 1;
}
