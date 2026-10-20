#include "town/menu/window.h"

/* kewn_namewin_open: Open the name window and store its handle. */
s32 kewn_namewin_open(void) {
    D_80100AF0 = create_item_view_for_entry(0, (void *)0x80010AB4,
                                  *(u8 *)0x80010980);
    return 0;
}
