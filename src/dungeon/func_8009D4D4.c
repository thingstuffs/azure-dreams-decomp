#include "common.h"
#include "shared/dungeon_status.h"


/* Returns whether any of the state fields at offsets 0x0A, 0x0C, and 0x10 is nonzero. */
s32 has_pending_actor_or_turn_action(void) {

    if (((u32)g_dungeon_status.unk_0C) != 0 || ((u32)g_dungeon_status.unk_10) != 0 || g_dungeon_status.unk_0A != 0) {
        return 1;
    }
    return 0;
}
