/* Relink of matched dungeon/func_812543F0; every changed retail word is a paired relocation. */
#define D_80173FBC D_80167FBC
#define D_80174710 D_80168710
#define D_80174714 D_80168714
#define D_80174718 D_80168718
#include "common.h"

extern s32 D_80167FBC[];
extern s32 *D_80168710;
extern s32 D_80168714;
extern s16 D_80168718;

/* Loads the selected table entry and marks the object state with its index. */
void func_80167BF0(s32 entry_index) {
    s8 *state_data;

    D_80168718 = 0;
    state_data = (s8 *)D_80168710 + 0x20;
    D_80168714 = D_80167FBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
