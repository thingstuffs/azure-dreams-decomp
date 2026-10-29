#include "common.h"
#include "shared/game_work.h"
#include "engine/camera.h"

/* Moves the selected 0x44-byte dispatch record back to its callback slot and clears the source callback. */
void restore_view_slot(s32 record_selector)
{
    char *dispatch_table = (char *)(&g_game_work.view);
    void *dst;
    void *src;

    if (record_selector == 0) {
        dst = dispatch_table + 0xB4;
        src = dispatch_table + 0xF8;
    } else {
        dst = dispatch_table + 0x13C;
        src = dispatch_table + 0x180;
    }
    move_view_record(dst, src);
}
