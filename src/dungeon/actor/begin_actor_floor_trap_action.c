#include "shared/dungeon_status.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/actor.h"


/* Sets the object's state to 0x15, clears its auxiliary fields, and increments the global counter. */
void begin_actor_floor_trap_action(SpriteFrameState *unused, ActorRecord *object) {
    object->action_id = 0x15;
    object->action_phase = 0;
    object->unk_8C.word = 0;
    g_dungeon_status.trap_counts.parts.pending_trap_count = (u16) g_dungeon_status.trap_counts.parts.pending_trap_count + 1;
}
