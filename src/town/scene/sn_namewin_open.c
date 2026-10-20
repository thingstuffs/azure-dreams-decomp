#include "common.h"
int create_item_view_without_event(int, int);              /* extern */
extern s32 D_80100AF0[];

/* sn_namewin_open: Open the name window and store its handle. */
s32 sn_namewin_open(void) {
    D_80100AF0[0] = create_item_view_without_event(0, (unsigned int)0x8001020C);
    return 0;
}
