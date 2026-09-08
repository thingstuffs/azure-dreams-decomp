#include "common.h"

typedef s32 M2C_UNK;

extern s32 D_80174AB4;
extern s16 D_80174AB8;
extern M2C_UNK D_80174BEC[];
extern void *D_80174CD8;

/* Select a table entry, reset its counter, and set the object flag. */
void func_80171130(s32 table_index) {
    D_80174AB8 = 0;
    D_80174AB4 = D_80174BEC[table_index];
    *(s16 *)((s8 *)D_80174CD8 + 0xD2) = 1;
}
