#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"

typedef struct S_80016BD4_2 {
    u8 pad_00[0x4];
    M2C_UNK (*unk_04)(void *, u8, s32);
} S_80016BD4_2;


typedef struct S_80016BD4_1 {
    u8 unk_00;
    u8 pad_01[0xF];
    s32 unk_10;
} S_80016BD4_1;


extern s32 D_80016E40;

/* Dispatch the selected state callback with the current context value. */
void dispatch_flag_test_state(void) {
    u8 state_index;
    S_80016BD4_1 *state;

    state = (D_80016000->unk_14 * 0x1C) + D_80016E40;
    state_index = state->unk_00;
    ((S_80016BD4_2 *)(((state_index * 0x10) + state->unk_10)))->unk_04(state, state_index, ((s32)D_80016000->unk_00));
}
