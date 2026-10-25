#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"

extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);

// Processes the source object's value, sets global flags, and assigns the destination object's data.
void process_actor_link_callback(void *destinationObject, void *unused1, void *unused2, void *sourceObject) {
    process_unflagged_linked_entries_alt(*(s32 *)((u8 *)sourceObject + 0x5C));
    process_unflagged_linked_entries(*(s32 *)((u8 *)sourceObject + 0x5C));
    g_dungeon_status.flags |= 0x812;
    *(void **)((u8 *)destinationObject + 0x8C) = handle_actor_commands_and_facing;
}
