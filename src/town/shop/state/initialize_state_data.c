#include "common.h"
#include "engine/sprite.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "town/shop/state.h"

extern s32 display_vector_defaults[];

typedef struct S_800B44F0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x10];
    s32 unk_5C;
} S_800B44F0_0;   /* arg0 in initialize_state_data */

typedef struct S_800B44F0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800B44F0_1;

/* Initializes state data, applies defaults, and reports initialization success. */
s32 initialize_state_data(void *state_arg, s32 input)
{
    S_800B44F0_0 *state = state_arg;
    s32 *defaults;
    s32 *state_data;
    s32 setup_result;
    s32 init_result;
    s32 success;

    success = 0;
    state_data = state_arg + 0x60;
    setup_result = func_80049004(state_data, input, 0xC);
    state->unk_5C = setup_result;
    if (setup_result != 0) {
        defaults = display_vector_defaults;
        state->unk_40 = display_vector_defaults[0];
        state->unk_44 = ((S_800B44F0_1 *)defaults)->unk_04;
        state->unk_48 = ((S_800B44F0_1 *)defaults)->unk_08;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(state->unk_5C, state_arg + 0x40, 0x21);
        init_result = allocate_and_append_callback_payload(state_data, 0xC);
        success = init_result != 0;
        state->unk_20 = init_result;
    }
    return success;
}
