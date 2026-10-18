#include "common.h"
#include "shared/dungeon_status.h"

/* Return whether any checked global state value or flag is set. */
s32 has_pending_dungeon_activity(void) {
    if (g_dungeon_status.unk_0C != 0 ||
        g_dungeon_status.unk_10 != 0 ||
        *(s32 *)&g_dungeon_status.unk_08 != 0 ||
        (g_dungeon_status.flags & 0x2008) != 0) {
        return 1;
    }
    return 0;
}
