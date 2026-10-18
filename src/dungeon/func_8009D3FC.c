#include "common.h"
#include "shared/dungeon_status.h"


extern s32 is_dungeon_action_enabled(void);

/* Sets or reuses the requested value and calls is_dungeon_action_enabled when state permits. */
s16 try_claim_dungeon_action_slot(s32 requested_value) {
    s32 current_value = ((s32)g_dungeon_status.unk_0C);

    if (current_value != requested_value) {
        if (current_value != 0) {
            return 1;
        }
        if (((s32)g_dungeon_status.unk_10) != 0) {
            return 1;
        }
        if (g_dungeon_status.unk_0A != 0) {
            return 1;
        }
        if (g_dungeon_status.flags & 8) {
            return 1;
        }
        g_dungeon_status.unk_0C = requested_value;
    }
    return is_dungeon_action_enabled();
}
