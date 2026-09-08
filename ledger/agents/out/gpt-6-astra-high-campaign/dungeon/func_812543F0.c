#include "common.h"

extern s32 D_80173FBC[];
extern s32 *D_80174710;
extern s32 D_80174714;
extern s16 D_80174718;

/* Loads the selected table entry and marks the object state with its index. */
void func_812543F0(s32 entry_index) {
    s8 *state_data;

    D_80174718 = 0;
    state_data = (s8 *)D_80174710 + 0x20;
    D_80174714 = D_80173FBC[entry_index];
    state_data[0xBA] = 1;
    *(s16 *)(state_data + 0xB8) = entry_index;
}
