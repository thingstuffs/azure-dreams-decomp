/* Relink of matched dungeon/func_812543F0; every changed retail word is a paired relocation. */
#define D_80173FBC D_8016DFBC
#define D_80174710 D_8016E710
#define D_80174714 D_8016E714
#define D_80174718 D_8016E718
#include "common.h"

extern s32 D_8016DFBC[];
extern s32 *D_8016E710;
extern s32 D_8016E714;
extern s16 D_8016E718;

/* Loads the selected table entry and marks the object state with its index. */
void func_8016DBF0(s32 entry_index) {
    s8 *state_data;

    D_8016E718 = 0;
    state_data = (s8 *)D_8016E710 + 0x20;
    D_8016E714 = D_8016DFBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
