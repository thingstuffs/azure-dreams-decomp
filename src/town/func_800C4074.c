#include "common.h"
s32 func_8004B8BC();              /* extern */
extern s32 D_80100AF0[];

/* sn_namewin_open: Open the name window and store its handle. */
s32 func_800C17D4(void) {
    D_80100AF0[0] = func_8004B8BC(0, (unsigned int)0x8001020C);
    return 0;
}
