/* Relink of matched dungeon/load_global_effect_table_entry at file 0x12743F0; imports and data use paired retail relocations. */
#include "common.h"

extern s32 D_80166FBC[];
extern s32 *D_80167710;
extern s32 D_80167714;
extern s16 D_80167718;

/* Loads the selected table entry and marks the object state with its index. */
void func_80166BF0(s32 entry_index) {
    s8 *state_data;

    D_80167718 = 0;
    state_data = (s8 *)D_80167710 + 0x20;
    D_80167714 = D_80166FBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
