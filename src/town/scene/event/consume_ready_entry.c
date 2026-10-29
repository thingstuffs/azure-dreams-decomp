#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/event.h"

extern void func_80017BA0(s32, s32);

/* Call func_80017BA0 when the current entry byte is at least two, then clear it and return success. */
s32 consume_ready_entry(s32 first_input, s32 second_input)
{
    Rec_D_80016000 *state_before;
    Rec_D_80016000 *state_after;

    state_before = town_scene_root;
    if (((u8 *)state_before->event_data)[state_before->entry_index * 8] < 2U) {
        return 0;
    }
    func_80017BA0(first_input, second_input);
    state_after = town_scene_root;
    ((u8 *)state_after->event_data)[state_after->entry_index * 8] = 0;
    return 1;
}
