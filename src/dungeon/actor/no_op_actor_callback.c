#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/actor.h"

// Processes the source object's value, sets global flags, and assigns the destination object's data.
void resume_actor_after_linked_entries(void *destinationObject, void *unused1, void *unused2, void *sourceObject) {
    process_unflagged_linked_entries_alt(*(void **)((u8 *)sourceObject + 0x5C));
    process_unflagged_linked_entries(*(void **)((u8 *)sourceObject + 0x5C));
    g_dungeon_status.flags |= 0x812;
    *(void **)((u8 *)destinationObject + 0x8C) = update_actor_commands_and_facing;
}
