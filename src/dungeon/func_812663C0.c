/* Relink of matched dungeon/func_809217A4; every changed retail word is a paired relocation. */
#include "common.h"

extern void func_800A56E0(s32);
extern s8 D_800DCF4D;

/* Calls func_800A56E0 with 180 and sets D_800DCF4D to -1. */
void func_80161BC0(void)
{
    func_800A56E0(0xB4);
    D_800DCF4D = -1;
}
