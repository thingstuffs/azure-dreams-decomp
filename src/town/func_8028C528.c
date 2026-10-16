/* Relink of matched town/func_8032C18C; every changed retail word is a paired relocation. */
#define D_8001B924 D_8001BA34
#define D_8001B944 D_8001BA54
#include "common.h"

extern void townApplyEntryPosition(void *, void *, s32, s32);
extern s32 D_8001B920;
extern u8 D_8001BA34[];
extern u8 D_8001BA54[];
extern s32 D_8001C354;

// Dispatches a value and code with state-selected data, setting the state for codes other than 0x2D.
void townSelectDialogueWith799Override(s32 value, s32 unused, s32 code) {
    void *selectedData;

    if (D_8001B920 != 0) {
        selectedData = D_8001BA54;
    } else {
        selectedData = D_8001BA34;
    }
    if (code != 0x2D) {
        D_8001B920 = 1;
    }
    townApplyEntryPosition(selectedData, &D_8001C354, value, code);
}
