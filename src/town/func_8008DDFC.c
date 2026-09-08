#include "common.h"

extern u32 D_80081458[];
/* D_800CF838 through the next catalog object, D_800CFBA0: 0x368 bytes. */
extern s32 D_800CF838[218];
extern s32 D_800CF874[203];

extern void func_80067014(s32 arg0);
extern s32 func_80047E78(s32 arg0);

void func_8008B55C(void)
{
    s32 value;
    s32 *items;

    if (D_800CF874[0] != 0) {
        func_80067014(0);
        items = &D_800CF838[15];
        value = func_80047E78(items[D_800CF874[0]]);
        D_80081458[0] = value;
        if (D_800CF874[0] == 1) {
            D_800CF874[0] = 0;
            return;
        }
        D_800CF874[0] = 1;
    }
}
