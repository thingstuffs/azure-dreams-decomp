#include "common.h"
#include "slus.h"
#include "town/scene.h"
extern s32 active_item_view[];

/* sn_namewin_open: Open the name window and store its handle. */
s32 sn_namewin_open(void) {
    active_item_view[0] = create_item_view_without_event(0, (unsigned int)0x8001020C);
    return 0;
}
