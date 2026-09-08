#include "common.h"

extern u32 *D_80129728[28];
extern void func_801237A4();

/* Swaps paired entry values and node halfwords, toggles the state flag, and updates. */
void func_801237E8(u8 *state)
{
    s32 **second_entry;
    s32 **first_entry;
    s32 **entries;
    s32 *first_word;
    s32 saved_word;
    s32 entry_index;
    u16 saved_half;
    void *first_node;

    entry_index = 2;
    entries = (s32 **)D_80129728;
    second_entry = entries + 16;
    first_entry = entries + 2;
    do {
        first_word = *first_entry;
        first_entry++;
        saved_word = *first_word;
        entry_index++;
        *first_word = **second_entry;
        **second_entry = saved_word;
        second_entry++;
    } while (entry_index < 14);

    first_node = *(void **)((u8 *)D_80129728[8] + 4);
    saved_half = *(u16 *)((u8 *)first_node + 8);
    *(u16 *)((u8 *)first_node + 8) =
        *(u16 *)((u8 *)*(void **)((u8 *)D_80129728[22] + 4) + 8);
    *(u16 *)((u8 *)*(void **)((u8 *)D_80129728[22] + 4) + 8) = saved_half;

    state[0x16] ^= 1;
    func_801237A4(state, saved_half, first_entry, entry_index);
}
