#include "common.h"
#include "shared/game_work.h"

extern short SD_Call(int a0);
extern void destroy_animated_selection_menu_owner(void *a0);

/* If global flag 0x20 is set, dispatches 0x515 and forwards the payload. */
void handle_animated_selection_menu_cancel(void *payload)
{
    if (((int)g_game_work.unk_010) & 0x20) {
        SD_Call(0x515);
        destroy_animated_selection_menu_owner(payload);
    }
}
