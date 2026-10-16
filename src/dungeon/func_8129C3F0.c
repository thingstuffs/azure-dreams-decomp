/* Relink of matched dungeon/dungeonLoadGlobalEffectTableEntry at file 0x12743F0; imports and data use paired retail relocations. */
#include "common.h"

extern s32 D_80154FBC[];
extern s32 *D_80155710;
extern s32 D_80155714;
extern s16 D_80155718;

/* Loads the selected table entry and marks the object state with its index. */
void func_80154BF0(s32 entry_index) {
    s8 *state_data;

    D_80155718 = 0;
    state_data = (s8 *)D_80155710 + 0x20;
    D_80155714 = D_80154FBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
