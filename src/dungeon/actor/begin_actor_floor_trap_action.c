#include "shared/dungeon_status.h"
#include "common.h"
#include "m2c_compat.h"


typedef struct S_800AAA28_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_800AAA28_0;   /* arg1 in begin_actor_floor_trap_action */

/* Sets the object's state to 0x15, clears its auxiliary fields, and increments the global counter. */
void begin_actor_floor_trap_action(void *unused, S_800AAA28_0 *object) {
    object->unk_9A = 0x15;
    object->unk_9B = 0;
    object->unk_8C = 0;
    g_dungeon_status.trap_counts.parts.pending_trap_count = (u16) g_dungeon_status.trap_counts.parts.pending_trap_count + 1;
}
