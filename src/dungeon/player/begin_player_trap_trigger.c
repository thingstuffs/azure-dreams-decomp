#include "dungeon/player.h"
#include "common.h"
#include "shared/dungeon_status.h"

/* Set object state 0x15, clear two fields, and update the shared value and counter. */
void begin_player_trap_trigger(void *object, void *unused_1, void *unused_2, void *shared_value) {
    *((u8 *)object + 0x9A) = 0x15;
    *((u8 *)object + 0x9B) = 0;
    *(s32 *)((u8 *)object + 0x8C) = 0;
    g_dungeon_status.active_actor = shared_value;
    g_dungeon_status.trap_counts.parts.pending_trap_count++;
}
