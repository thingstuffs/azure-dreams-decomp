#include "common.h"

extern s32 func_8004B854();
extern s32 D_80100AF0[];

/* kewn_namewin_open: Open the name window and store its handle. */
s32 func_8009E3EC(void) {
    D_80100AF0[0] = func_8004B854(0, (void *)0x80010AB4,
                                   *(u8 *)0x80010980);
    return 0;
}
