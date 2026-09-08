#include "common.h"

typedef struct {
    s32 words[4];
} PackedWord;

extern PackedWord D_80016024;
extern s32 func_8001ADE0(s32);
extern s32 func_8001B0E8(s32, s32);
extern void func_8001B168(s32, s32, s32);

/* Returns the selected table value, cycling the selection when the 0xDB0 check fails. */
s32 func_8001755C(void)
{
    PackedWord table;
    s32 selection;

    table = D_80016024;
    selection = func_8001B0E8(0xD6E, 2);
    if (func_8001ADE0(0xDB0) == 0) {
        selection++;
        if (selection == 4) {
            selection = 0;
        }
        func_8001B168(0xD6E, selection, 2);
    }
    return table.words[selection];
}
