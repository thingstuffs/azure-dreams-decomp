/* Relink of matched dungeon/dungeonLoadGlobalEffectTableEntry at file 0x12743F0; imports and data use paired retail relocations. */
#include "common.h"

extern s32 D_8015AFBC[];
extern s32 *D_8015B710;
extern s32 D_8015B714;
extern s16 D_8015B718;

/* Loads the selected table entry and marks the object state with its index. */
void func_8015ABF0(s32 entry_index) {
    s8 *state_data;

    D_8015B718 = 0;
    state_data = (s8 *)D_8015B710 + 0x20;
    D_8015B714 = D_8015AFBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
