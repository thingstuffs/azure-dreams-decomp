#include "common.h"

/* Reads a script byte and fills sixteen words in the target state with its value. */
void func_80039F4C(void *vm) {
    u32 script_ptr = *(u32 *)((u8 *)vm + 0x1C);
    u32 entry_ptr = *(u32 *)((u8 *)vm + 0x80);
    u32 fill_value = *(u8 *)script_ptr;
    s32 entry_index;

    script_ptr++;
    entry_ptr += 0x3C;
    *(u32 *)((u8 *)vm + 0x1C) = script_ptr;

    entry_index = 15;
    do {
        *(u32 *)(entry_ptr + 0x48) = fill_value;
        entry_index--;
        entry_ptr -= 4;
    } while (entry_index >= 0);
}
