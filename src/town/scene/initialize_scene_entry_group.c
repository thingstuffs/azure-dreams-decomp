#include "common.h"
#include "shared/object_index_slots.h"

extern void initialize_object_entries(void *, s8 *, s32 *);
extern void run_record_countdown_follow_up(void *, s32, s32);
extern s32 D_800D58CC[];

void initialize_scene_entry_group_5(void *object, s32 unused, void *output)
{
    initialize_object_entries(object, output, D_800D58CC);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = run_record_countdown_follow_up;
    *(s16 *)((u8 *)object + 0x6C) = 5;
}
