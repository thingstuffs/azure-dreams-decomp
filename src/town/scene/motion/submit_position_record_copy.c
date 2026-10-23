#include "common.h"
#include "shared/town_pointees.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef struct S_806F18F8_4 {
    u8 pad_00[0x208];
    s32 (*unk_208)(s32);
} S_806F18F8_4;   /* ((S_806F18F8_1 *)state)->unk_20 in submit_position_record_copy */


/* Builds a record from the current state and submits it after calling the first state callback. */
void submit_position_record_copy(void) {
    s32 record[6];
    Rec_D_80016000 *state;

    state = town_scene_root;
    record[0] = ((TownPositionState *)(state->position))->x;
    record[1] = ((TownPositionState *)(state->position))->x;
    record[2] = 0;
    ((S_806F18F8_4 *)(state->services))->unk_208(0);
    ((s32 (*) (s32 *))town_scene_root->services->callback_228)(record);
}
