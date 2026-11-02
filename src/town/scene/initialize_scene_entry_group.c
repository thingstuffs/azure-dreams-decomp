#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_index_slots.h"
#include "town/scene.h"

extern void run_record_countdown_follow_up(void *, s32, s32);
extern s32 D_800D58CC[];

/*
 * Initializes entries from D_800D58CC, clears the indexed object slot, and installs
 * run_record_countdown_follow_up with count 5.
 */
void initialize_scene_entry_group_5(TownObjectRecord *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D58CC);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = run_record_countdown_follow_up;
    object->timer.as_s16 = 5;
}
