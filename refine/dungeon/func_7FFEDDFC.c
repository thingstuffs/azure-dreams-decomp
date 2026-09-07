#include "common.h"

extern u32 D_80081458[];
extern s32 D_800CF838[218];
extern s32 D_800CF874[203];

extern void func_80067014(s32 arg0);
extern s32 func_80047E78(s32 arg0);

/* Updates the stored result from the selected entry and advances the active state toward zero. */
void func_8008B55C(void)
{
    s32 entry_result;
    s32 *entry_table;

    if (D_800CF874[0] != 0) {
        func_80067014(0);
        entry_table = &D_800CF838[15];
        entry_result = func_80047E78(entry_table[D_800CF874[0]]);
        D_80081458[0] = entry_result;
        if (D_800CF874[0] == 1) {
            D_800CF874[0] = 0;
            return;
        }
        D_800CF874[0] = 1;
    }
}
