/* Relink of matched dungeon/func_812543F0; every changed retail word is a paired relocation. */
#define D_80173FBC D_80155FBC
#define D_80174710 D_80156710
#define D_80174714 D_80156714
#define D_80174718 D_80156718
#include "common.h"

extern s32 D_80155FBC[];
extern s32 *D_80156710;
extern s32 D_80156714;
extern s16 D_80156718;

/* Loads the selected table entry and marks the object state with its index. */
void func_80155BF0(s32 entry_index) {
    s8 *state_data;

    D_80156718 = 0;
    state_data = (s8 *)D_80156710 + 0x20;
    D_80156714 = D_80155FBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
