#include "common.h"
#include "shared/game_work.h"

extern void move_view_record(void *dst, void *src);

/* Moves the selected dispatch table slot to its destination slot. */
void queue_view_slot(int slot_selector)
{
    char *dispatch_table = (char *)(&g_game_work.view);

    if (slot_selector == 0) {
        move_view_record(dispatch_table + 0xF8, dispatch_table + 0xB4);
    } else {
        move_view_record(dispatch_table + 0x180, dispatch_table + 0x13C);
    }
}
