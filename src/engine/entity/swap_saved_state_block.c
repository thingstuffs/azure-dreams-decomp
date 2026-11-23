#include "common.h"
#include "shared/game_state.h"
#include "engine/entity.h"
#include "slus/data.h"
#include "slus/runtime_saved_state_data.h"

/* Restores saved state when requested; otherwise saves the current state. */
void swap_saved_state_block(void)
{
    if (runtime_state_restore_requested != 0) {
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        state_word = runtime_saved_state_word;
        state_byte_4 = runtime_saved_state_byte_04_alias;
        state_byte_6 = runtime_saved_state_byte_06;
        runtime_state_restore_requested = 0;
        GAME_STATE->options.option_color = state_word;
        GAME_STATE->options.unk_3184 = state_byte_4;
        GAME_STATE->options.unk_3186 = state_byte_6;
    } else {
        u32 state_word;
        u8 state_byte_4;
        u8 state_byte_6;
        state_word = GAME_STATE->options.option_color;
        state_byte_4 = GAME_STATE->options.unk_3184;
        state_byte_6 = GAME_STATE->options.unk_3186;
        runtime_saved_state_word = state_word;
        runtime_saved_state_byte_04_alias = state_byte_4;
        runtime_saved_state_byte_06 = state_byte_6;
    }
}
