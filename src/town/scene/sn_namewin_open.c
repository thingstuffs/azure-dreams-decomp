#include "common.h"
#include "slus.h"
#include "town/scene.h"
#include "town/menu/window.h"

/* sn_namewin_open: Open the name window and store its handle. */
s32 sn_namewin_open(void) {
    active_item_view = create_item_view_without_event(0, (unsigned int)0x8001020C);
    return 0;
}
