#include "common.h"

extern s32 D_80100E40;

/* Copies three halfwords from the selected table entry into the destination. */
void func_800AAFE0(void *destination, s32 entry_index) {
    s8 *table_base;
    s8 *entry;

    table_base = (s8 *)&D_80100E40;
    entry = table_base + (entry_index * 8);
    *(u16 *)((s8 *)destination + 2) = *(u16 *)(entry + 0);
    *(u16 *)((s8 *)destination + 6) = *(u16 *)(entry + 2);
    *(u16 *)((s8 *)destination + 10) = *(u16 *)(entry + 4);
}
