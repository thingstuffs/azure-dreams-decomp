#include "common.h"

typedef struct {
    s32 words[4];
} PackedWord;

extern PackedWord D_80016024;
extern s32 townGetScriptFlagMask(s32);
extern s32 townReadScriptFlagRange(s32, s32);
extern void townWriteScriptFlagRange(s32, s32, s32);

/* Returns the selected table value, cycling the selection when the 0xDB0 check fails. */
s32 townCycleD6ESelectionIfAllowed(void)
{
    PackedWord table;
    s32 selection;

    table = D_80016024;
    selection = townReadScriptFlagRange(0xD6E, 2);
    if (townGetScriptFlagMask(0xDB0) == 0) {
        selection++;
        if (selection == 4) {
            selection = 0;
        }
        townWriteScriptFlagRange(0xD6E, selection, 2);
    }
    return table.words[selection];
}
