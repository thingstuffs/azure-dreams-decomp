#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/flags.h"

typedef struct S_80016BD4_2 {
    u8 pad_00[0x4];
    s32 (*unk_04)(void *, u8, s32);
    u8 pad_08[0x8];
} S_80016BD4_2;


typedef struct S_80016BD4_1 {
    u8 unk_00;
    u8 pad_01[0xF];
    S_80016BD4_2 *unk_10;
    u8 pad_14[0x8];
} S_80016BD4_1;


extern s32 *installed_object_sets;

/* Dispatch the selected state callback with the current context value. */
void dispatch_flag_test_state(void) {
    u8 state_index;
    S_80016BD4_1 *state;

    /* BYTES: the record address is summed as an integer; indexing the table as records schedules its load first. */
    state = (S_80016BD4_1 *)((town_scene_root->unk_14 * 0x1C) + (unsigned long)installed_object_sets);
    state_index = state->unk_00;
    state->unk_10[state_index].unk_04(state, state_index, ((s32)town_scene_root->unk_00));
}
