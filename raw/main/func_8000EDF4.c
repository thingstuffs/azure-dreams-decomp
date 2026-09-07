#include "common.h"

extern s32 D_80083E98[][32];

void func_80021DF4(s32 arg0, void *arg1) {
    s32 *base;
    s32 *entry;
    s32 *final_base;
    s32 *final_entry;
    s32 initial_offset;
    s32 final_offset;

    base = (s32 *)&D_80083E98;
    ASM_KEEP(base);
    initial_offset = arg0 << 7;
    entry = (s32 *)(initial_offset + (s32)base);
    memcpy(entry, (u8 *)arg1 + 0x200, 0x80);
    final_offset = arg0 << 7;
    final_base = (s32 *)&D_80083E98;
    final_entry = (s32 *)((u8 *)final_base + final_offset);
    ASM_KEEP(final_entry);
    final_entry[0] = 1;
}
