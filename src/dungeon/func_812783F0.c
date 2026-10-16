/* Relink of matched dungeon/func_812543F0; every changed retail word is a paired relocation. */
#define D_80173FBC D_8014FFBC
#define D_80174710 D_80150710
#define D_80174714 D_80150714
#define D_80174718 D_80150718
#include "common.h"

extern s32 D_8014FFBC[];
extern s32 *D_80150710;
extern s32 D_80150714;
extern s16 D_80150718;

/* Loads the selected table entry and marks the object state with its index. */
void func_8014FBF0(s32 entry_index) {
    s8 *state_data;

    D_80150718 = 0;
    state_data = (s8 *)D_80150710 + 0x20;
    D_80150714 = D_8014FFBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
