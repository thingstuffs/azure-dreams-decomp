#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/ghosh.h"

extern void *ghosh_scripted_actor[];
extern void * detach_record_and_update_slot_state(void *record);

// Processes and clears slot zero's entry, setting entry and global status flags.
void release_secondary_overlay_object(void) {
    void *entryData;

    entryData = ghosh_scripted_actor[0];
    if (entryData != 0) {
        entryData = (u8 *)entryData + 0x20;
        detach_record_and_update_slot_state(entryData);
        *(u16 *)((u8 *)entryData - 2) |= 0x8000;
        ghosh_scripted_actor[0] = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
