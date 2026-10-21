#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"


/* Returns whether the first entry in D_800287CC is nonzero. */
s32 card_boot_has_selected_channel(void) {
    return *card_selected_channel_alias != 0;
}
