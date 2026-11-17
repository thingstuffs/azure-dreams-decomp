#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/ghosh.h"
#include "dungeon/player/object.h"

// Processes and clears slot zero's entry, setting entry and global status flags.
void release_scripted_ghosh_actor(void) {
    void *entryData;

    entryData = ghosh_scripted_actor;
    if (entryData != 0) {
        entryData = NODE_BODY(entryData);
        detach_record_and_update_slot_state(entryData);
        NODE_HEADER(entryData)->flags |= 0x8000;
        ghosh_scripted_actor = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
