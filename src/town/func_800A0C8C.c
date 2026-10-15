#include "modules/town_town_windows.h"

/* kewn_namewin_open: Open the name window and store its handle. */
s32 kewn_namewin_open(void) {
    D_80100AF0 = func_8004B854(0, (void *)0x80010AB4,
                                  *(u8 *)0x80010980);
    return 0;
}
