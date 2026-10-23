#include "common.h"
#include "shared/record_ptrs.h"

extern s32 D_800189BC[];
extern s32 D_80019548[];
extern void close_dialogue_if_open_hand(s32, s32);

/* Call close_dialogue_if_open_hand, then copy the table entry selected by the current index. */
void dispatch_status_boolean(s32 first_input, s32 second_input)
{
    close_dialogue_if_open_hand(first_input, second_input);
    D_80019548[0] = D_800189BC[*(s32 *)((u8 *)town_scene_root + 8)];
}
