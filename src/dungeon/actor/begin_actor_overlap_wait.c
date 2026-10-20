#include "common.h"
#include "shared/dungeon_status.h"

/* Sets the entity state to 3, clears its progress, and increments the global counter. */
void begin_actor_overlap_wait(void *entity) {
    *(s8 *)((s8 *)entity + 0x9A) = 3;
    *(s8 *)((s8 *)entity + 0x9B) = 0;
    *(s32 *)((s8 *)entity + 0x8C) = 0;
    *(s16 *)((s8 *)entity + 0x96) = 4;
    g_dungeon_status.activity_counts.parts.pending_action_count += 1;
}
